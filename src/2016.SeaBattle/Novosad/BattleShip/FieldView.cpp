#include "FieldView.h"
#include "ResultView.h"
#include "Globals.h"
#include "StartView.h"
#include "ConsoleFunctions.h"
#include <iostream>
#include <conio.h>
#include <cpprest/http_client.h>
#include "CellState.h"
#include "NetworkField.h"
#include "ComputerField.h"

using namespace web::http;
using namespace client;
using namespace std;

FieldView::FieldView(bool multiplayer, bool start_game, string room_id, int score) :
	service_(language),
	playersCurrentShip_(4, ShipOrientation::Horizontal),
	room_id_(room_id),
	game_message_("Place your ships"),
	enemy_turn_(!start_game),
	playerIsReady_(false),
	start_game_(start_game),
	multiplayer_(multiplayer),
	current_score_(score)
{
	player_field_ = new Field(2, 10, CELL_WIDTH, CELL_HEIGHT);

	if (multiplayer)
	{
		CommunicationManager* communication_manager_ = new CommunicationManager();
		communication_manager_->joinGame(room_id_);
		enemy_field_ = new NetworkField(0, 0, CELL_WIDTH, CELL_HEIGHT, start_game_, communication_manager_);
		communication_manager_->sendMessage("Created");
	}
	else
	{
		enemy_field_ = new ComputerField(0, 0, CELL_WIDTH, CELL_HEIGHT);
	}
	enemy_field_->setLocationX(15);
	enemy_field_->setLocationY(10);
	playersCurrentShipIndex_ = 1;
}

void FieldView::drawFieldDecorations()
{
	setCursoreAtPosition(player_field_->getLocationX() * 2, player_field_->getLocationY() - 1);
	//cout << static_cast<char>('A' + i);
	cout << service_.getWord("letters");

	setCursoreAtPosition(enemy_field_->getLocationX() * 2, enemy_field_->getLocationY() - 1);
	cout << service_.getWord("letters");

	for (int i = 0; i < player_field_->getSize(); i++)
	{
		int offsetX = to_string(i + 1).size() + 1;

		setCursoreAtPosition(player_field_->getLocationX() - offsetX + 2, player_field_->getLocationY() + i);
		cout << i + 1;

		setCursoreAtPosition(enemy_field_->getLocationX() * 2 - offsetX, enemy_field_->getLocationY() + i);
		cout << i + 1;
	}
}

void FieldView::drawInCursorLocation()
{
	int myFieldLocationX = player_field_->getLocationX();
	int myFieldLocationY = player_field_->getLocationY();
	int enemyFieldLocationX = enemy_field_->getLocationX();
	int enemyFieldLocationY = enemy_field_->getLocationY();

	if (playerShipsArePlaced_)
	{
		// highlights cursor cell if all ships are placed
		SetConsoleTextAttribute(hConOut, 2 + 10 * 16);
		setCursoreAtPosition((enemyFieldLocationX + currentX_) * 2, (enemyFieldLocationY + currentY_));
		cout << "  ";
		SetConsoleTextAttribute(hConOut, 14 + 2 * 16);
	}
	else
	{
		// draws the ship the is about to be placed in cursor location
		SetConsoleTextAttribute(hConOut, 2 + 10 * 16);
		setCursoreAtPosition((myFieldLocationX + currentX_) * 2, myFieldLocationY + currentY_);

		for (int i = 0; i < playersCurrentShip_.getSize(); i++)
		{
			cout << "  ";
			if (playersCurrentShip_.getOrientation() == ShipOrientation::Vertical)
			{
				setCursoreAtPosition((myFieldLocationX + currentX_) * 2, myFieldLocationY + currentY_ + i + 1);
			}
		}

		SetConsoleTextAttribute(hConOut, 14 + 2 * 16);
	}
}

void FieldView::draw()
{
	// draw field names and view title
	printAtCenterOfLine(3, service_.getWord("score") + " " + to_string(current_score_), redSymbolsGreenBackground);
	setCursoreAtPosition(10, 22);
	cout << service_.getWord("my_field");
	setCursoreAtPosition(35, 22);
	cout << service_.getWord("enemy_field");
	printAtCenterOfLine(25, service_.getWord(game_message_), redSymbolsGreenBackground);

	drawFieldDecorations();
	player_field_->draw();
	enemy_field_->draw();
	drawInCursorLocation();
}

int FieldView::getNextShipSize()
{
	playersCurrentShipIndex_++;
	if (playersCurrentShipIndex_ <= 1)
	{
		return 4;
	}
	else if (playersCurrentShipIndex_ <= 3)
	{
		return 3;
	}
	else if (playersCurrentShipIndex_ <= 6)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

int FieldView::getPointsForKillingShip(int indexOfShip)
{
	if (indexOfShip == 0)
	{
		return 20;
	}
	if (indexOfShip == 1 || indexOfShip == 2)
	{
		return 30;
	}
	if (indexOfShip >= 3 && indexOfShip <= 5)
	{
		return 40;
	}
	return 50;
}

void FieldView::toggleTurn()
{
	enemy_turn_ = !enemy_turn_;
}

View* FieldView::handle()
{
	View* newView = this;

	if (playerShipsArePlaced_ == false)
	{
		int key = _getch();
		newView = handleShipPlacement(key);
	}
	else if (playerIsReady_ == false)
	{
		if (enemy_field_->isReady())
		{
			playerIsReady_ = true;
		}
		else
		{
			game_message_ = service_.getWord("wait_for_other_player");;
		}
	}
	else if (playerShipsArePlaced_ && playerIsReady_)
	{
		if (enemy_turn_)
		{
			FireDetails network_details;

			if (multiplayer_)
			{
				network_details = enemy_field_->waitForFire();
			}
			else
			{
				network_details = enemy_field_->waitForComputer(player_field_);
			}

			if (network_details.Result != FireResult::AllKilled)
			{
				FireDetails internal_details = player_field_->fireAt(network_details.X, network_details.Y);
				enemy_field_->submitFire(internal_details);

				if (internal_details.Result == FireResult::Miss)
				{
					game_message_ = service_.getWord("your_turn");
					toggleTurn();
				}
			}
			else
			{
				game_message_ = service_.getWord("game_over_press_enter");
				toggleTurn();
				player_field_->finishBattle();
				enemy_field_->finishBattle();
			}
		}
		else
		{
			int key = _getch();
			newView = handleMotionOnField(key);
		}
	}

	return newView;
}

View* FieldView::handleMotionOnField(int key)
{
	View* newView = this;

	bool enemyShipsKilled = enemy_field_->allShipsKilled();
	bool playerShipsKilled = player_field_->allShipsKilled();

	if (multiplayer_ && (enemyShipsKilled || playerShipsKilled))
	{
		player_field_->finishBattle();
		enemy_field_->finishBattle();
		newView = new FieldView(true, start_game_, room_id_, current_score_);
	}
	else if (multiplayer_ == false && playerShipsKilled)
	{
		newView = new ResultView(current_score_);
	}
	else if (multiplayer_ == false && enemyShipsKilled)
	{
		newView = new FieldView(false, start_game_, room_id_, current_score_);
	}
	else
	{
		switch (key)
		{
		case KEY_LEFT:
			if (currentX_ == 0)
			{
				currentX_ = 9;
			}
			else
			{
				currentX_--;
			}
			break;
		case KEY_RIGHT:
			if (currentX_ == 9)
			{
				currentX_ = 0;
			}
			else
			{
				currentX_++;
			}
			break;
		case KEY_UP:
			if (currentY_ == 0)
			{
				currentY_ = 9;
			}
			else
			{
				currentY_--;
			}
			break;
		case KEY_DOWN:
			if (currentY_ == 9)
			{
				currentY_ = 0;
			}
			else
			{
				currentY_++;
			}
			break;
		case KEY_ENTER:
			if (enemy_field_->getCellState(currentX_, currentY_) == CellState::Empty)
			{
				FireDetails details = enemy_field_->fireAt(currentX_, currentY_);

				if (details.Result == FireResult::AllKilled)
				{
					game_message_ = service_.getWord("game_over_press_enter");
					toggleTurn();
					current_score_ += getPointsForKillingShip(details.ShipSize);
					player_field_->finishBattle();
					enemy_field_->finishBattle();
				}
				else if (details.Result == FireResult::Miss)
				{
					game_message_ = service_.getWord("enemy_turn");
					toggleTurn();
				}
				else if (details.Result == FireResult::Hit)
				{
					current_score_ += 10;
				}
				else
				{
					current_score_ += getPointsForKillingShip(details.ShipSize);
				}
			}
			break;
		case KEY_ESCAPE:
			newView = new StartView();
			break;
		}
	}

	return newView;
}

View* FieldView::handleShipPlacement(int key)
{
	View* newView = this;

	switch (key)
	{
	case KEY_RIGHT:
		if (playersCurrentShip_.getOrientation() == ShipOrientation::Horizontal && currentX_ + playersCurrentShip_.getSize() - 1 == 9)
		{
			currentX_ = 0;
		}
		else if (playersCurrentShip_.getOrientation() == ShipOrientation::Vertical && currentX_ == 9)
		{
			currentX_ = 0;
		}
		else
		{
			currentX_++;
		}
		break;
	case KEY_LEFT:
		if (playersCurrentShip_.getOrientation() == ShipOrientation::Horizontal && currentX_ == 0)
		{
			currentX_ = 9 - playersCurrentShip_.getSize() + 1;
		}
		else if (playersCurrentShip_.getOrientation() == ShipOrientation::Vertical && currentX_ == 0)
		{
			currentX_ = 9;
		}
		else
		{
			currentX_--;
		}
		break;
	case KEY_DOWN:
		if (playersCurrentShip_.getOrientation() == ShipOrientation::Horizontal && currentY_ == 9)
		{
			currentY_ = 0;
		}
		else if (playersCurrentShip_.getOrientation() == ShipOrientation::Vertical && currentY_ + playersCurrentShip_.getSize() - 1 == 9)
		{
			currentY_ = 0;
		}
		else
		{
			currentY_++;
		}
		break;
	case KEY_UP:
		if (playersCurrentShip_.getOrientation() == ShipOrientation::Horizontal && currentY_ == 0)
		{
			currentY_ = 9;
		}
		else if (playersCurrentShip_.getOrientation() == ShipOrientation::Vertical && currentY_ == 0)
		{
			currentY_ = 9 - playersCurrentShip_.getSize() + 1;
		}
		else
		{
			currentY_--;
		}
		break;
	case KEY_WHITESPACE:
		if (playersCurrentShip_.getOrientation() == ShipOrientation::Horizontal && currentY_ + playersCurrentShip_.getSize() - 1 <= 9)
		{
			playersCurrentShip_.setOrientation(ShipOrientation::Vertical);
		}
		else
		{
			if (currentX_ + playersCurrentShip_.getSize() - 1 <= 9)
			{
				playersCurrentShip_.setOrientation(ShipOrientation::Horizontal);
			}
		}
		break;
	case KEY_ENTER:
		playersCurrentShip_.setLocationX(currentX_);
		playersCurrentShip_.setLocationY(currentY_);
		if (player_field_->canPlace(playersCurrentShip_))
		{
			player_field_->place(playersCurrentShip_);
			int size = getNextShipSize();
			playersCurrentShip_ = Ship(size, ShipOrientation::Horizontal);
			if (playersCurrentShipIndex_ > 10)
			{
				playerShipsArePlaced_ = true;
			}
		}
		break;
	case KEY_ESCAPE:
		newView = new StartView();
		break;
	}

	return newView;
}
