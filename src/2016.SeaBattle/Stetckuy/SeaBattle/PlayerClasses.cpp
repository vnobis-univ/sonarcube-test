#pragma once

#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cpprest/http_client.h>

#include "PlayerClasses.h"
#include "ConsoleProperties.h"

using namespace std;
using namespace web::http;
using namespace web::http::client;

Player::Player(Cell** enemy)
	: enemyField(enemy)
{
	// initialize player field
	ownField = new Cell*[10];

	for (size_t i = 0; i < 10; ++i)
	{
		ownField[i] = new Cell[10];
	}
}

Enemy::Enemy(Cell** enemy)
	: enemyField(enemy)
{
	// initialize enemy field
	ownField = new Cell*[10];

	for (size_t i = 0; i < 10; ++i)
	{
		ownField[i] = new Cell[10];
	}
}

void Player::putShips() // puts player ships
{
	srand(time(0));

	int shipCounter = 0;
	int sides[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

	Ship* toPlace;

	while (shipCounter < 10)
	{
		bool canPlace = false;

		while (!canPlace)
		{
			int placeTop = rand() % 10;
			int placeLeft = rand() % 10;

			// if you can place the ship in these coords
			if (canBePlaced(ownField, Direction::HORIZONTAL, placeTop, placeLeft, sides[shipCounter]) == "OK")
			{
				toPlace = new Ship(ownField, placeTop, placeLeft, sides[shipCounter]);
				toPlace->drawOutline();

				canPlace = true;
			}
		}

		// move ships

		bool placed = false;
		while (!placed)
		{

			switch (_getch())
			{
			case 224: // one of the arrows pressed

				switch (_getch())
				{
				case 72: // up
					toPlace->move(-1, 0);
					break;
				case 75: // left
					toPlace->move(0, -1);
					break;
				case 77: //right
					toPlace->move(0, 1);
					break;
				case 80: //down
					toPlace->move(1, 0);
					break;
				}

				break;
			case VK_RETURN:
				if (canBePlaced(ownField, toPlace->getDirection(), toPlace->getTop(), toPlace->getLeft(),
					toPlace->getSize()) == "OK")
				{
					toPlace->draw();

					delete toPlace;

					placed = true;
				}
				break;

			case 32:

				if (toPlace->getDirection() == Direction::HORIZONTAL)
				{
					toPlace->setDirection(Direction::VERTICAL);
				}
				else
				{
					toPlace->setDirection(Direction::HORIZONTAL);
				}

				break;
			}
		}

		++shipCounter;
	}
}

// randomly places computer ships
void Enemy::putShips()
{

	if (options.gameMode == Mode::COMPUTER)
	{

		int shipCounter = 0;

		int sides[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

		Ship* toPlace;

		while (shipCounter < 10)
		{
			bool canPlace = false;

			while (!canPlace)
			{
				int placeTop = rand() % 10;
				int placeLeft = rand() % 10;

				int direction = rand() % 2 + 1;

				if (canBePlaced(ownField, (Direction)direction, placeTop, placeLeft, sides[shipCounter]) == "OK")
				{
					toPlace = new Ship(ownField, placeTop, placeLeft, sides[shipCounter], (Direction)direction);
					toPlace->draw();
					canPlace = true;
					delete toPlace;
				}
			}

			++shipCounter;
		}
	}
}
 
bool Player::join()
{
	bool toReturn = true;

	int playerX = 50;
	int playerY = 175;
	string letters = "ABCDEFGHIJ"; // layout of coordinates

	for (size_t i = 0; i < 10; ++i)
	{

		setCursorAt(playerX / FONT_WIDTH - 2, (playerY + 36 * i + 15) / FONT_HEIGHT);
		techData.print(toString(i + 1));

		for (size_t j = 0; j < 10; ++j)
		{
			if (i == 0)
			{
				setCursorAt((playerX + 22 * j + 10) / FONT_WIDTH, playerY / FONT_HEIGHT - 1);
				techData.print(letters[j]); // paints row coordinates
			}

			ownField[i][j].setX(playerX + 22 * j);
			ownField[i][j].setY(playerY + 36 * i);

			ownField[i][j].setSideX(22);
			ownField[i][j].setSideY(36);

			ownField[i][j].draw();
		}
	}

	if (options.gameMode == Mode::COMPUTER)
	{

	putShips();

	}
	else
	{

		int enemyX = 500;
		int enemyY = 175;

		for (size_t i = 0; i < 10; ++i)
		{
			setCursorAt(enemyX / FONT_WIDTH - 2, (enemyY + 36 * i + 15) / FONT_HEIGHT);
			techData.print(toString(i + 1));

			for (size_t j = 0; j < 10; ++j)
			{
				if (i == 0)
				{
					setCursorAt((enemyX + 22 * j + 10) / FONT_WIDTH, enemyY / FONT_HEIGHT - 1);
					techData.print(letters[j]);
				}

				enemyField[i][j].setX(enemyX + 22 * j);
				enemyField[i][j].setY(enemyY + 36 * i);

				enemyField[i][j].setSideX(22);
				enemyField[i][j].setSideY(36);

				enemyField[i][j].disactivate();
				enemyField[i][j].draw();
			}
		}

		if (options.multiplayerType == MultiplayerType::CREATE) // if you create the room
		{
			putShips();

			string afterPut = options.connection.getServerData();

			if (afterPut != "enemyQuit") // if enemy is present
			{

				options.connection.setServerData("playerShipsPut");

				string currentInfo = "playerShipsPut";

				int milisecondsCounter = 0;
				bool complete = false;

				while (currentInfo != "enemyShipsPut") // wait for enemy ships placement
				{
					Sleep(5000);
					milisecondsCounter += 5000;

					string currentInfo = options.connection.getServerData();

					if (currentInfo == "enemyShipsPut")
					{
						complete = true;
						break;
					}

					if (milisecondsCounter > 60000)
					{
						break;
					}
				}

				if (!complete)
				{
					options.connection.setServerData("playerQuit"); // time-out error
					toReturn = false;
				}
			}
			else
			{
				toReturn = false; // enemy is out of game
			}
		}
		else // if you join the room
		{
			string currentInfo = options.connection.getServerData();

			bool enemyPlaced = false;
			int milisecondsCounter = 0;
			
			if (currentInfo == "playerShipsPut")
			{
				enemyPlaced = true;
			}
			else
			{
				while (currentInfo != "playerShipsPut")
				{
					Sleep(5000);
					milisecondsCounter += 5000;

					string currentInfo = options.connection.getServerData();

					if (currentInfo == "playerShipsPut")
					{
						enemyPlaced = true;
						break;
					}

					if (milisecondsCounter > 60000)
					{
						options.connection.setServerData("enemyQuit"); // if player didn't put his ships in 1 minute
						break;
					}
				}
			}

			if (!enemyPlaced)
			{
				toReturn = false;
			}
			else
			{
				putShips();

				string newInfo = options.connection.getServerData();

				if (newInfo == "playerQuit") // if player is out of game
				{
					toReturn = false;
				}
				else
				{
					options.connection.setServerData("enemyShipsPut"); // else inform that you put your ships
				}
			}
		}
	}

	return toReturn;
}

bool Enemy::join() // used for placing computer ships; always returns true
{

		int playerX = 500;
		int playerY = 175;
		string letters = "ABCDEFGHIJ";

		for (size_t i = 0; i < 10; ++i)
		{
			setCursorAt(playerX / FONT_WIDTH - 2, (playerY + 36 * i + 15) / FONT_HEIGHT);
			techData.print(toString(i + 1));

			for (size_t j = 0; j < 10; ++j)
			{
				if (i == 0)
				{
					setCursorAt((playerX + 22 * j + 10) / FONT_WIDTH, playerY / FONT_HEIGHT - 1);
					techData.print(letters[j]);
				}

				ownField[i][j].setX(playerX + 22 * j);
				ownField[i][j].setY(playerY + 36 * i);

				ownField[i][j].setSideX(22);
				ownField[i][j].setSideY(36);

				ownField[i][j].hide();

				ownField[i][j].draw();
			}
		}

		putShips();
	
		return true;
}

// if killed, returns true, direction of ship (shipDirection) and whether it contains only one cell (isUnary)
bool Player::killed(int row, int col, Direction& shipDirection, bool& isUnary)
{
	bool toReturn = false;

	bool leftOk = true;
	bool rightOk = true;
	bool topOk = true;
	bool bottomOk = true;

	isUnary = true;
	shipDirection = Direction::HORIZONTAL;

	if (row - 1 >= 0)
	{
		if (!ownField[row - 1][col].isEmpty())
		{
			shipDirection = Direction::VERTICAL;
			isUnary = false;
		}

		int i = 1;

		while (row - i >= 0)
		{
			if (ownField[row - i][col].isEmpty())
			{
				break;
			}
			else
			{
				if (!ownField[row - i][col].isMarked())
				{
					topOk = false;
					break;
				}
			}

			++i;
		}

	}

	if (col - 1 >= 0)
	{
		if (!ownField[row][col - 1].isEmpty())
		{
			shipDirection = Direction::HORIZONTAL;
			isUnary = false;
		}

		int i = 1;

		while (col - i >= 0)
		{
			if (ownField[row][col - i].isEmpty())
			{
				break;
			}
			else
			{
				if (!ownField[row][col - i].isMarked())
				{
					leftOk = false;
					break;
				}
			}

			++i;
		}
	}

	if (row + 1 < 10)
	{
		if (!ownField[row + 1][col].isEmpty())
		{
			shipDirection = Direction::VERTICAL;
			isUnary = false;

		}

		int i = 1;

		while (row + i < 10)
		{
			if (ownField[row + i][col].isEmpty())
			{
				break;
			}
			else
			{
				if (!ownField[row + i][col].isMarked())
				{
					bottomOk = false;
					break;
				}
			}

			++i;
		}
	}

	if (col + 1 < 10)
	{
		if (!ownField[row][col + 1].isEmpty())
		{
			shipDirection = Direction::HORIZONTAL;
			isUnary = false;
		}

		int i = 1;

		while (col + i < 10)
		{
			if (ownField[row][col + i].isEmpty())
			{
				break;
			}
			else
			{
				if (!ownField[row][col + i].isMarked())
				{
					rightOk = false;
					break;
				}
			}

			++i;
		}
	}

	if (leftOk && rightOk && topOk && bottomOk)
	{
		toReturn = true;
	}

	return toReturn;
}


// the same thing about enemy ships
bool Enemy::killed(int row, int col, Direction& shipDirection, bool& isUnary)
{
	bool toReturn = false;

	bool leftOk = true;
	bool rightOk = true;
	bool topOk = true;
	bool bottomOk = true;

	isUnary = true;

	shipDirection = Direction::HORIZONTAL;

	if (row - 1 >= 0)
	{
		if (!ownField[row - 1][col].isEmpty())
		{
			shipDirection = Direction::VERTICAL;
			isUnary = false;
		}

		int i = 1;

		while (row - i >= 0)
		{
			if (ownField[row - i][col].isEmpty())
			{
				break;
			}
			else
			{
				if (!ownField[row - i][col].isMarked())
				{
					topOk = false;
					break;
				}
			}

			++i;
		}

	}

	if (col - 1 >= 0)
	{
		if (!ownField[row][col - 1].isEmpty())
		{
			shipDirection = Direction::HORIZONTAL;
			isUnary = false;
		}

		int i = 1;

		while (col - i >= 0)
		{
			if (ownField[row][col - i].isEmpty())
			{
				break;
			}
			else
			{
				if (!ownField[row][col - i].isMarked())
				{
					leftOk = false;
					break;
				}
			}

			++i;
		}
	}

	if (row + 1 < 10)
	{
		if (!ownField[row + 1][col].isEmpty())
		{
			shipDirection = Direction::VERTICAL;
			isUnary = false;

		}

		int i = 1;

		while (row + i < 10)
		{
			if (ownField[row + i][col].isEmpty())
			{
				break;
			}
			else
			{
				if (!ownField[row + i][col].isMarked())
				{
					bottomOk = false;
					break;
				}
			}

			++i;
		}
	}

	if (col + 1 < 10)
	{
		if (!ownField[row][col + 1].isEmpty())
		{
			shipDirection = Direction::HORIZONTAL;
			isUnary = false;
		}

		int i = 1;

		while (col + i < 10)
		{
			if (ownField[row][col + i].isEmpty())
			{
				break;
			}
			else
			{
				if (!ownField[row][col + i].isMarked())
				{
					rightOk = false;
					break;
				}
			}

			++i;
		}
	}

	if (leftOk && rightOk && topOk && bottomOk)
	{
		toReturn = true;
	}

	return toReturn;
}

// returns "kill", "miss" and "hit"
string Player::answer(const string& s, Direction& dir, bool& isUnary)
{
	int col = s[0] - 'A';
	int row = static_cast<int>(s[1]) - 48;
	string toReturn = "miss";

	if (!ownField[row][col].isEmpty())
	{
		if (killed(row, col, dir, isUnary))
		{
			toReturn = "kill";
		}
		else
		{
			toReturn = "hit";
		}
	}

	return toReturn;
}


// gives some logic to bot
void Player::generateEnemyDirection(int botRow, int botCol)
{
	compEnemy.cellRemembered = false;
	compEnemy.moveLeft = false;
	compEnemy.moveTop = false;

	compEnemy.remDirection = Direction::HORIZONTAL;

	if (botCol - 1 >= 0)
	{
		if (!ownField[botRow][botCol - 1].isMarked())
		{
			compEnemy.cellRemembered = true;
			compEnemy.moveLeft = true;
		}
	}


	if (!compEnemy.cellRemembered)
	{
		if (botCol + 1 < 10)
		{
			if (!ownField[botRow][botCol + 1].isMarked())
			{
				compEnemy.cellRemembered = true;
				compEnemy.moveLeft = false;
			}
		}
	}

	if (!compEnemy.cellRemembered)
	{
		compEnemy.remDirection = Direction::VERTICAL;

		if (botRow - 1 >= 0)
		{
			if (!ownField[botRow - 1][botCol].isMarked())
			{
				compEnemy.cellRemembered = true;
				compEnemy.moveTop = true;
			}
		}

		if (!compEnemy.cellRemembered)
		{
			if (botRow + 1 < 10)
			{
				if (!ownField[botRow + 1][botCol].isMarked())
				{
					compEnemy.cellRemembered = true;
					compEnemy.moveTop = false;
				}
			}
		}
	}
}

// moves the bot (if unable to move, generate another direction)
void Player::moveFromRememberedCell(int& botRow, int& botCol)
{
	if (compEnemy.remDirection == Direction::HORIZONTAL)
	{
		if (compEnemy.moveLeft)
		{
			if (compEnemy.shiftCol - 1 >= 0)
			{
				botRow = compEnemy.shiftRow;
				botCol = compEnemy.shiftCol - 1;
				--compEnemy.shiftCol;
			}
			else
			{
				generateEnemyDirection(compEnemy.rememberedRow, compEnemy.rememberedCol);

				if (compEnemy.cellRemembered)
				{
					compEnemy.shiftRow = compEnemy.rememberedRow;
					compEnemy.shiftCol = compEnemy.rememberedCol;
					botRow = compEnemy.rememberedRow;
					botCol = compEnemy.rememberedCol;
				}
			}
		}
		else
		{
			if (compEnemy.shiftCol + 1 < 10)
			{
				botRow = compEnemy.shiftRow;
				botCol = compEnemy.shiftCol + 1;
				++compEnemy.shiftCol;
			}
			else
			{
				generateEnemyDirection(compEnemy.rememberedRow, compEnemy.rememberedCol);

				if (compEnemy.cellRemembered)
				{
					compEnemy.shiftRow = compEnemy.rememberedRow;
					compEnemy.shiftCol = compEnemy.rememberedCol;
					botRow = compEnemy.rememberedRow;
					botCol = compEnemy.rememberedCol;
				}
			}
		}
	}
	else
	{
		if (compEnemy.moveTop)
		{
			if (compEnemy.shiftRow - 1 >= 0)
			{
				botRow = compEnemy.shiftRow - 1;
				botCol = compEnemy.shiftCol;
				--compEnemy.shiftRow;
			}
			else
			{
				generateEnemyDirection(compEnemy.rememberedRow, compEnemy.rememberedCol);

				if (compEnemy.cellRemembered)
				{
					compEnemy.shiftRow = compEnemy.rememberedRow;
					compEnemy.shiftCol = compEnemy.rememberedCol;
					botRow = compEnemy.rememberedRow;
					botCol = compEnemy.rememberedCol;
				}
			}
		}
		else
		{
			if (compEnemy.shiftRow + 1 < 10)
			{
				botRow = compEnemy.shiftRow + 1;
				botCol = compEnemy.shiftCol;
				++compEnemy.shiftRow;
			}
			else
			{
				generateEnemyDirection(compEnemy.rememberedRow, compEnemy.rememberedCol);

				if (compEnemy.cellRemembered)
				{
					compEnemy.shiftRow = compEnemy.rememberedRow;
					compEnemy.shiftCol = compEnemy.rememberedCol;
					botRow = compEnemy.rememberedRow;
					botCol = compEnemy.rememberedCol;
				}
			}
		}
	}
}

// makes the cell non-empty
void Player::fillEnemyCell(int row, int col)
{
	enemyField[row][col].activate();
}


void Enemy::fillEnemyCell(int row, int col)
{
	enemyField[row][col].activate();
}

// returns "kill", "miss", "hit" and "quit" (player pressed ESC)
string Enemy::answer(const string& s, Direction& dir, bool& isUnary)
{
	int col = s[0] - 'A';
	int row = static_cast<int>(s[1]) - 48;
	string toReturn = "miss";

	if (s[0] == 'X')
	{
		toReturn = "quit";
	}
	else
	{ 
		if (!ownField[row][col].isEmpty())
		{
			if (killed(row, col, dir, isUnary))
			{
				toReturn = "kill";
			}
			else
			{
				toReturn = "hit";
			}
		}
	}

	return toReturn;
}

Cell** Player::getField() 
{
	return ownField;
}

Cell** Enemy::getField() 
{
	return ownField;
}

// information that gives some logic to bot
Player::EnemyCharacteristics::EnemyCharacteristics(bool cell, bool left, bool top,
	int remRow, int remCol, int _shiftRow, int _shiftCol,
	Direction dir)
	: cellRemembered(cell), // cell that was hit by bot
	moveLeft(left), // if he can move left
	moveTop(top), // if he can move top
	rememberedRow(remRow), // fixed row, from which bot is moving
	rememberedCol(remCol), // fixed column, from which bot is moving
	shiftRow(_shiftRow), // current row hit by bot
	shiftCol(_shiftCol), // current column hit by bot
	remDirection(dir) // direction of ship
{
}

// enemy of player shot (bot)
string Player::enemyShot(int& botRow, int& botCol)
{
	srand(time(0));

	string toReturn = "";

	string letters = "ABCDEFGHIJ";

	if (options.gameMode == Mode::COMPUTER)
	{

		bool enemyTurnDone = false;

		while (!enemyTurnDone)
		{
			if (compEnemy.cellRemembered) // if bot remembers hit cell
			{
				moveFromRememberedCell(botRow, botCol);
			}
			else // generate another cell
			{
				botRow = rand() % 10;
				botCol = rand() % 10;
			}

			if (!ownField[botRow][botCol].isMarked()) // if it is not marked
			{

				ownField[botRow][botCol].mark();

				if (!ownField[botRow][botCol].isEmpty())
				{

					if (!compEnemy.cellRemembered) // bot can memorize this cell
					{
						generateEnemyDirection(botRow, botCol);

						if (compEnemy.cellRemembered) // if memorized
						{
							compEnemy.rememberedRow = botRow;
							compEnemy.shiftRow = botRow;
							compEnemy.rememberedCol = botCol;
							compEnemy.shiftCol = botCol;
						}
					}
				}
				else // if it is empty
				{
					if (compEnemy.cellRemembered) // if bot remembered this cell
					{
						// try to move in another direction from it
						generateEnemyDirection(compEnemy.rememberedRow, compEnemy.rememberedCol); 

						// if can move in another direction
						if (compEnemy.cellRemembered)
						{
							compEnemy.shiftRow = compEnemy.rememberedRow;
							compEnemy.shiftCol = compEnemy.rememberedCol;
						}
					}
				}

				enemyTurnDone = true;
			}
		}

		toReturn += letters[botCol];
		toReturn += toString(botRow);

	}

	return toReturn;
}

// enemy of enemy (that is, player) shot
string Enemy::enemyShot(int& row, int& col)
{
	srand(time(0));

	string toReturn = "";

	// symbol "X" is used here to tell that player pressed ESC
	string letters = "ABCDEFGHIJX"; // X - player quits

	workoutPlayerTurn(row, col);

	toReturn += letters[col];
	toReturn += toString(row);

	return toReturn;
}

void Enemy::workoutPlayerTurn(int& row, int& col)
{
	bool cellChosen = false;

	ownField[row][col].drawOutline(State::ACTIVE);

	// choose cell
	while (!cellChosen)
	{
		switch (_getch())
		{
		case 224: // arrow pressed
			switch (_getch())
			{
			case 72: // up
				if (row > 0)
				{
					if (!ownField[row][col].isMarked())
					{
						ownField[row][col].draw();
					}
					else
					{
						ownField[row][col].drawOutline(State::PASSIVE);
					}

					--row;
					ownField[row][col].drawOutline(State::ACTIVE);
				}
				break;
			case 75: // left
				if (col > 0)
				{
					if (!ownField[row][col].isMarked())
					{
						ownField[row][col].draw();
					}
					else
					{
						ownField[row][col].drawOutline(State::PASSIVE);
					}

					--col;
					ownField[row][col].drawOutline(State::ACTIVE);
				}
				break;
			case 77: //right
				if (col < 9)
				{
					if (!ownField[row][col].isMarked())
					{
						ownField[row][col].draw();
					}
					else
					{
						ownField[row][col].drawOutline(State::PASSIVE);
					}

					++col;

					ownField[row][col].drawOutline(State::ACTIVE);
				}
				break;
			case 80: //down
				if (row < 9)
				{
					if (!ownField[row][col].isMarked())
					{
						ownField[row][col].draw();
					}
					else
					{
						ownField[row][col].drawOutline(State::PASSIVE);
					}

					++row;
					ownField[row][col].drawOutline(State::ACTIVE);
				}
				break;
			}
			break;
		case VK_RETURN: // Enter
			if (!ownField[row][col].isMarked())
			{
				cellChosen = true;
			}
			break;
		case VK_ESCAPE: // ESC
			row = 0;
			col = 10;
			cellChosen = true;
			break;
		}
	}
}

void Enemy::setEnemyField(Cell** field)
{
	enemyField = field;
}

void Player::setEnemyField(Cell** field)
{
	enemyField = field;
}