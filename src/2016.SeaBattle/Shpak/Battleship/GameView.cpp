#include "GameView.h"
#include "ConsoleManipulators.h"
#include "LanguageManipulator.h"
#include "ResultView.h"
#include "GameMessages.h"
#include "MenuView.h"
#include "GameLogic.h"
#include "GameLogicComputer.h"
#include "GameLogicOnline.h"
#include "Navigation.h"
#include "Printer.h"
#include "GameField.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>

GameView::GameView(bool isOfflineGame, bool isHostOnlineGame):
	playerField({ 2, 17 }, GameField::FieldType::playerField)
{
	clean();

	if (isOfflineGame)
	{
		gameLogic = new GameLogicComputer({(short)(getConsoleWidth() / 2 + 4), 17});

		redrawScore(gameLogic->getScore());
	}
	else
	{
		playerField = GameField({ 2, 15 }, GameField::FieldType::playerField);

		gameLogic = new GameLogicOnline({ (short)(getConsoleWidth() / 2 + 4), 15 }, isHostOnlineGame);
	}
}

GameView::~GameView()
{
	delete gameLogic;
}

void GameView::draw()
{
	playerField.drawField();
}

View* GameView::handle()
{
	while (true)
	{
		if (!handleShipPlacement())
		{
			break; // need to exit when placing ships
		}

		if (!gameLogic->connectToGame())
		{
			// here if can't connect to game(online)
		}

		if (handleGame())
		{
			playerField.renewField();
			playerField.drawField();
		}
		else
		{
			break;
		}
	}

	if (gameLogic->getScore() != -1)
	{
		// if offline game

		return new ResultView(gameLogic->getScore());
	}
	else
	{
		// if online game

		return new MenuView();
	}
}

bool GameView::handleShipPlacement()
{
	GameMessages().drawShipPlacementHint();

	for (size_t i = 4; i >= 1; --i) // ship size
	{
		for (size_t j = 1; j <= 5 - i; ++j) // number of ships
		{
			if (!handleOneShip(i))
				return false;		
		}
	}

	GameMessages().clearHints();

	return true;
}

bool GameView::handleOneShip(int size)
{
	bool isNewPosition = true;

	int start_iOld = 0;
	int start_jOld = 0;

	int start_i = 0;
	int start_j = 0;
	GameField::Direction direction = GameField::Direction::horizontal;
	GameField::Direction oldDirection = direction;

	while (true)
	{
		Button button;
		
		// drawing new positioned ship
		if (isNewPosition)
		{
			showNewShipPosition(start_i, start_j, start_iOld, start_jOld, size, direction, oldDirection);

			start_iOld = start_i;
			start_jOld = start_j;

			oldDirection = direction;

			isNewPosition = false;
		}
		

		// until one of possible buttons is not presed continue loop
		while (!getWhichButton(button))
		{
		}

		switch (button)
		{
		case Button::UP: //key up
			if (isOkayToMakeMove(start_i - 1, start_j, size, direction))
			{
				start_iOld = start_i;
				--start_i;
				isNewPosition = true;
			}
				
			break;

		case Button::DOWN: //key down
			if (isOkayToMakeMove(start_i + 1, start_j, size, direction))
			{
				start_iOld = start_i;
				++start_i;
				isNewPosition = true;
			}
			break;

		case Button::LEFT: //key left
			if (isOkayToMakeMove(start_i, start_j - 1, size, direction))
			{
				start_jOld = start_j;
				--start_j;
				isNewPosition = true;
			}
			break;

		case Button::RIGHT: //key right
			if (isOkayToMakeMove(start_i, start_j + 1, size, direction))
			{
				start_jOld = start_j;
				++start_j;
				isNewPosition = true;
			}
			break;

		case Button::ENTER: // key enter
			if (playerField.isOkayToPlaceShip(start_i, start_j, size, direction))
			{
				playerField.placeShip(start_i, start_j, size, direction);
				return true;
			}
			break;

		case Button::QButton: // key enter
			oldDirection = direction;

			if (direction == GameField::Direction::horizontal)
			{
				direction = GameField::Direction::vertical;
			}
			else
			{
				direction = GameField::Direction::horizontal;
			}

			if (isOkayToMakeMove(start_i, start_j, size, direction))
			{
				isNewPosition = true;
			}
			else
			{
				direction = oldDirection;
			}

			break;

		case Button::ESC:
			return false;
			break;

		default:
			continue;
		}
	}

	return true;
}

bool GameView::isOkayToMakeMove(int index_i, int index_j)
{
	if (index_i < 0 || index_i > 9 || index_j < 0 || index_j > 9)
		return false;

	return true;
}

bool GameView::isOkayToMakeMove(int index_i, int index_j, int size, GameField::Direction shipDirection)
{
	if (shipDirection == GameField::Direction::horizontal)
	{
		for (size_t k = 0; k < size; ++k)
		{
			if (!isOkayToMakeMove(index_i, index_j + k))
				return false;
		}
	}
	else
	{
		for (size_t k = 0; k < size; ++k)
		{
			if (!isOkayToMakeMove(index_i + k, index_j))
				return false;
		}
	}

	return true;
}

void GameView::showNewShipPosition(int start_i, 
									int start_j, 
									int start_iOld, 
									int start_jOld, 
									int size, 
									GameField::Direction direction, 
									GameField::Direction oldDirection)
{
	// firstly remove old position of ship
	for (size_t k = 0; k < size; ++k)
	{
		if (oldDirection == GameField::Direction::horizontal)
			playerField.drawEmptyCell(start_iOld, start_jOld + k);
		else
			playerField.drawEmptyCell(start_iOld + k, start_jOld);
	}

	// redrawing ships that may have been removed
	playerField.drawAllShips();


	// and draw new positioned ship
	playerField.drawShip(start_i, start_j, size, direction);

	for (size_t k = 0; k < size; ++k)
	{
		if (direction == GameField::Direction::horizontal)
		{
			if (!playerField.isOkayToPlaceShip(start_i, start_j + k))
			{
				playerField.drawBadtoPutShip(start_i, start_j + k);
			}
		}
		else
		{
			if (!playerField.isOkayToPlaceShip(start_i + k, start_j))
			{
				playerField.drawBadtoPutShip(start_i + k, start_j);
			}
		}
	}
}

bool GameView::handleGame()
{
	bool isLose = false;

	if (gameLogic->isOnlineJoinedGame())
	{
		// if joined game need to wait


		while (gameLogic->handleOponentChoice(playerField, isLose) && !isLose)
		{/* empty block */}


		if (isLose)
		{
			GameMessages().drawLose();

			return false; // end of all games
		}
	}


	int current_iOld = 0;
	int current_jOld = 0;

	int current_i = 0;
	int current_j = 0;


	while (true)
	{
		gameLogic->handleMove(current_iOld, current_jOld, false); 

		gameLogic->handleMove(current_i, current_j, true);

		current_iOld = current_i;
		current_jOld = current_j;

		Button button;

		// until one of possible buttons is not presed continue loop
		while (!getWhichButton(button))
		{
		}

		switch (button)
		{
		case Button::UP: //key up
			if (isOkayToMakeMove(current_i - 1, current_j))
			{
				--current_i;
			}
			break;

		case Button::DOWN: //key down
			if (isOkayToMakeMove(current_i + 1, current_j))
			{
				++current_i;
			}
		
			break;

		case Button::LEFT: //key left
			if (isOkayToMakeMove(current_i, current_j - 1))
			{
				--current_j;
			}
			break;

		case Button::RIGHT: //key right
			if (isOkayToMakeMove(current_i, current_j + 1))
			{
				++current_j;
			}
			break;

		case Button::ESC:
			return false;
			break;

		case Button::ENTER: // key enter
			if (handlePlayerChoice(current_i, current_j, isLose))
			{
				if (gameLogic->getScore() == -1)
				{
					// if it is online game
					return false; // need to end game
				}
				else
				{
					return true; // need to start new game
				}
				
			}
			else if (isLose)
			{
				GameMessages().drawLose();

				return false; // end of all games
			}
			break;

		default:
			continue;
		}
	}
}

bool GameView::handlePlayerChoice(int index_i, int index_j, bool& isLose)
{
	bool isEndOfCurrentGame = false;
	bool isBadChoiceInput = false;

	if(gameLogic->handlePlayerChoice(index_i, index_j, isEndOfCurrentGame, isBadChoiceInput) || isBadChoiceInput)
	{
		if (isEndOfCurrentGame)
		{
			return true; // if win the game
		}

		return false; // if hit in order to choose again
	}

	while(gameLogic->handleOponentChoice(playerField, isLose) && !isLose)
	{/* empty block */}


	return false;
}