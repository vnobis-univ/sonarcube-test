#pragma once

#include <conio.h>
#include <cctype>
#include <ctime>
#include <cstdlib>

#include "FieldView.h"
#include "Options.h"
#include "ResultView.h"
#include "StartView.h"


using namespace std;

FieldView::FieldView()
	: playerInfo(SideBar()),
	enemyInfo(SideBar(0, 500)),
	successfulLogIn(false),
	gameStatus("")
{
	markUpText.push_back("Choose your multiplayer mode:");
	markUpText.push_back("Enter ID: ");
	markUpText.push_back("Your ID: ");
	markUpText.push_back("Connection complete");
	markUpText.push_back("Something went wrong");
	markUpText.push_back("Press any key to continue...");
	markUpText.push_back("YOU");
	markUpText.push_back("ENEMY");
	markUpText.push_back("Game status: ");
	markUpText.push_back("Prepare to game...");
	markUpText.push_back("Your turn");
	markUpText.push_back("Waiting for enemy action...");
	markUpText.push_back("missed");
	markUpText.push_back("hit");
	markUpText.push_back("killed");
	markUpText.push_back("Glorious victory!");
	markUpText.push_back("Defeat");
	markUpText.push_back("Enemy turn");

	windowLanguage = Language::ENGLISH;

	player = new Player();
	enemy = new Enemy();

	player->setEnemyField(enemy->getField());
	enemy->setEnemyField(player->getField());

	menuItems.push_back(MenuItem("JOIN",CONSOLE_WIDTH / 3, CONSOLE_HEIGHT / 2));
	menuItems.push_back(MenuItem("CREATE", 2 * CONSOLE_WIDTH / 3, CONSOLE_HEIGHT / 2));
	menuItems[0].chosen = true;
}

void FieldView::drawMenu()
{
	for (size_t i = 0; i < menuItems.size(); ++i)
	{
		setCursorAt(menuItems[i].x, menuItems[i].y);

		if (menuItems[i].chosen)
		{
			menuActive.print(menuItems[i].text);
		}
		else
		{
			menuPassive.print(menuItems[i].text);
		}
	}

}

void FieldView::setStatus(const string& s)
{
	drawBackground(0, (7 * CONSOLE_HEIGHT / 8 + 3)*FONT_HEIGHT,
		CONSOLE_WIDTH*FONT_WIDTH, (7 * CONSOLE_HEIGHT / 8 + 4)*FONT_HEIGHT, RGB(0, 100, 200));

	setCursorAt(0, 7 * CONSOLE_HEIGHT / 8 + 3);
	printAtCenter(s, techData);
}

void FieldView::draw()
{
	clear();
	configure(); // defined in View to translate window text

	if (options.gameMode == Mode::MULTIPLAYER) // if multiplayer
	{
		
		setCursorAt(0, CONSOLE_HEIGHT/2 - 2);
		printAtCenter(markUpText[0], techData); // choosing mulriplayerMode

		drawMenu();

		bool finished = false;

		int currentItem = 0;

		while (!finished)
		{
			switch (_getch())
			{
			case 224: // one of the arrows was pressed
				switch (_getch())
				{
				case 75: // left
					if (currentItem > 0)
					{
						menuItems[currentItem].chosen = false;
						--currentItem;
						menuItems[currentItem].chosen = true;

						drawMenu();
					}
					break;
				case 77: // right
					if (currentItem < 1)
					{
						menuItems[currentItem].chosen = false;
						++currentItem;
						menuItems[currentItem].chosen = true;

						drawMenu();
					}
					break;
				}

				break;
		
			case VK_RETURN: // Enter
				options.multiplayerType = (MultiplayerType)currentItem;
				finished = true;
				break;
			}
		}

		clear();
		
		if (options.multiplayerType == MultiplayerType::CREATE) // if CREATE, tells you id and waits for pressing any button
		{
			options.connection.setId();

			setCursorAt(0, CONSOLE_HEIGHT / 2 - 2);
			printAtCenter(markUpText[2] + options.connection.stringId(), headline);

			setCursorAt(0, CONSOLE_HEIGHT / 2);
			printAtCenter(markUpText[5], techData);

			successfulLogIn = true;

			_getch();
		}
		else // if JOIN, gets user's id input and if it's right, asks to press any button
			 // if id is wrong, asks to press any button and redirects to the start menu
		{
		
			setCursorAt(CONSOLE_WIDTH / 3, CONSOLE_HEIGHT / 2);
			techData.print(markUpText[1]);

			options.connection.readIdFromUser(successfulLogIn);
			setCursorAt(0, CONSOLE_HEIGHT / 2 + 2);

			if (successfulLogIn)
			{
				printAtCenter(markUpText[3], techData);
			}
			else
			{
				printAtCenter(markUpText[4], techData);
			}

			setCursorAt(0, CONSOLE_HEIGHT / 2 + 4);
			printAtCenter(markUpText[5], techData);

			_getch();
		}
	}

	clear();

	playerInfo.draw();
	enemyInfo.draw();

	if (options.gameMode == Mode::MULTIPLAYER) // if MULTIPLAYER, sets game status "Preparing to game...";
	{
		setCursorAt(0, 7 * CONSOLE_HEIGHT / 8 + 1);
		printAtCenter(markUpText[8], headline);
		setStatus(markUpText[9]);
	}
}

void FieldView::workOutPlayerInput(const string& playerName, const string& enemyName, 
								   bool& finishGame, bool& creatorTurn, Result& gameResult)
{

	int row = 0;
	int col = 0;
	bool quitGame = false;

	setStatus(markUpText[10]);

	string cell = enemy->enemyShot(row, col); // here you make your turn and the coords of chosen cell are returned

	// send information of cell
	options.connection.setServerData(cell);

	// waiting for enemy reply
	setStatus(markUpText[11]);

	Direction dir;
	bool isUnary;

	bool answerAchieved = false;
	string getResponse = cell;

	while (getResponse == cell)
	{
		Sleep(2500);
		getResponse = options.connection.getServerData();
	}

	if (getResponse == playerName) // if answer is that you won
	{
		setStatus(markUpText[15]);

		playerInfo.score = 10;
		playerInfo.numOfCells = 0;

		playerInfo.draw();

		gameResult = Result::VICTORY;
		finishGame = true;
		Sleep(2000);
	}
	else if (getResponse == enemyName) // else if you defeated
	{
		setStatus(markUpText[16]);
		gameResult = Result::DEFEAT;
		finishGame = true;
		Sleep(2000);
	}
	else
	{
		if (getResponse == "hit" || getResponse == "kill") // if cell was not empty
		{
			player->fillEnemyCell(row, col);

			Direction dir;
			bool isUnary;

			if (getResponse == "kill" && enemy->answer(cell, dir, isUnary) == "kill")
			{
				setStatus(cell[0] + toString(row + 1)  + " : " + markUpText[14]); // cell : killed
				++playerInfo.score;
				customizeSideBar(enemy->getField(), row, col, dir, isUnary);
				Sleep(2000); // stop game to let the player see the gameStatus
			}
			else
			{
				setStatus(cell[0] + toString(row + 1) + " : " + markUpText[13]); // cell : hit
				++playerInfo.numOfCells;
				Sleep(2000);
			}

			playerInfo.draw();
		}
		else if (getResponse == "miss")
		{
			setStatus(cell[0] + toString(row + 1) + " : " + markUpText[12]); // cell : miss
			creatorTurn = (creatorTurn == true ? false : true);
			Sleep(2000);
			setStatus(markUpText[17]); // enemy turn
		}

		enemy->getField()[row][col].mark();
	}
}

void FieldView::respondToRequest(const string& playerName, const string& enemyName, bool& finishGame, 
	                             bool& creatorTurn, Result& gameResult)
{
	// when it's not the player's turn, tells whether enemy hit, killed, or missed
	bool cellExtracted = false;
	string str = "";

	while (!cellExtracted)
	{
		Sleep(2500);

		str = options.connection.getServerData();

		if (str.size() == 2) // it is a cell coordinate, like "A1"
		{
			cellExtracted = true;
		}
	}

	int playerRow = static_cast<int>(str[1]) - 48;
	int playerCol = str[0] - 'A';

	string returnRequest = "";

	if (str[0] == 'X')
	{
		options.connection.setServerData(playerName);
		gameResult = Result::VICTORY;
		playerInfo.score = 10;
		playerInfo.numOfCells = 0;
		finishGame = true;
	}
	else
	{
		if (!(player->getField()[playerRow][playerCol].isEmpty())) // if the cell is not empty
		{
			Direction dir;
			bool isUnary;

			if (player->answer(str, dir, isUnary) == "kill") // if enemy killed player's ship
			{
				++enemyInfo.score;
				customizeSideBar(player->getField(), playerRow, playerCol, dir, isUnary);
				returnRequest = "kill";
			}
			else // if enemy hit player's ship
			{
				++enemyInfo.numOfCells;
				returnRequest = "hit";
			}

			enemyInfo.draw();
		}
		else // if enemy missed
		{
			returnRequest = "miss";
			creatorTurn = (creatorTurn == true ? false : true);
		}


		player->getField()[playerRow][playerCol].mark();

		if (enemyWon())
		{
			gameResult = Result::DEFEAT;
			options.connection.setServerData(enemyName);
			finishGame = true; // game loop stops
		}
		else
		{
			options.connection.setServerData(returnRequest);
			if (returnRequest == "miss")
			{
				Sleep(5000); // sleep when enemy missed to avoid asynchronous server requests
			}
		}
	}
}

void FieldView::playWithComputer(Result& gameResult)
{
	bool playerTurn = true;
	int row = 0;
	int col = 0;
	Direction dir; // tells if ship is HORIZONTAL or VERTICAL
	bool isUnary; // tells if ship consists of one cell (true) or more(false)
	string cell; // coords of cells (e.g. "A1")

	if (player->join() && enemy->join()) // both placed their ships
	{
		bool finish = false;

		while (!finish)
		{

			while (playerTurn) // playerTurn
			{

				col = 0;
				row = 0;

				cell = enemy->enemyShot(row, col); // player shoot

				if (enemy->answer(cell, dir, isUnary) == "kill") // if killed
				{
					++playerInfo.score;
					customizeSideBar(enemy->getField(), row, col, dir, isUnary);

					playerInfo.draw();
				}
				else if (enemy->answer(cell, dir, isUnary) == "hit") // if hit
				{
					++playerInfo.numOfCells;

					playerInfo.draw();
				}
				else if(enemy->answer(cell, dir, isUnary) == "miss")
				{
					playerTurn = false;
				}
				else
				{
					finish = true;
					break;
				}

				enemy->getField()[row][col].mark(); // mark the cell

				if (playerWon()) // if player won
				{
					gameResult = Result::VICTORY;
					finish = true;
					break;
				}
			}
			
			while (!playerTurn) // enemy turn
			{
				cell = player->enemyShot(row, col); // enemy shoot

				if (player->answer(cell, dir, isUnary) == "kill") // if killed
				{
					++enemyInfo.score;
					customizeSideBar(player->getField(), row, col, dir, isUnary);

					enemyInfo.draw();
				}
				else if (player->answer(cell, dir, isUnary) == "hit") // if hit
				{
					++enemyInfo.numOfCells;

					enemyInfo.draw();
				}
				else // if missed
				{
					playerTurn = true;
				}

				player->getField()[row][col].mark(); // mark cell

				if (enemyWon()) // enemy won
				{
					gameResult = Result::DEFEAT;
					finish = true;
					break;
				}
			}
		}
	}
}

View* FieldView::handle()
{
	View* toReturn = nullptr;

	if (options.gameMode == Mode::COMPUTER)
	{
		Result gameResult = Result::VICTORY;

		playWithComputer(gameResult);

		PlayerData data = PlayerData(playerInfo.score, playerInfo.numOfCells, options.gameMode, "");
		toReturn = new ResultView(data);
	}
	else
	{
		if (!successfulLogIn) // if players didn't connect to server, redirect to start menu of game
		{
			toReturn = new StartView();
		}
		else
		{

			Result gameResult = Result::VICTORY;
			bool creatorTurn = true; // tells if it's time for room creator to make the turn
			bool finishGame = false;


				if (player->join()) //if player joined the room
				{

					while (!finishGame)
					{
						if (options.multiplayerType == MultiplayerType::CREATE) // if player created the room
						{

							if (creatorTurn)
							{
								workOutPlayerInput("creatorWon", "joinerWon", finishGame, creatorTurn, gameResult);
							}
							else
							{
								respondToRequest("creatorWon", "joinerWon", finishGame, creatorTurn, gameResult);
							}
						}
						else // if player joined the room
						{
							if (!creatorTurn)
							{
								workOutPlayerInput("joinerWon", "creatorWon", finishGame, creatorTurn, gameResult);
							}
							else
							{
								respondToRequest("joinerWon", "creatorWon", finishGame, creatorTurn, gameResult);
							}
						}
					}

					PlayerData data = PlayerData(playerInfo.score, playerInfo.numOfCells, options.gameMode, "");
					toReturn = new ResultView(data);

			}
			else // if player didn't join (time-out error)
			{
				setStatus(markUpText[4] + " " + markUpText[5]);
				toReturn = new StartView();
				_getch();
			}
		}
	}

	return toReturn;
}

FieldView::~FieldView()
{
	delete player;
	delete enemy;
}

void FieldView::customizeSideBar(Cell** field, int row, int col, Direction shipDirection, bool isUnary) // decreases the number of hit cells when the ship is fully killed
{
	
	if (!isUnary)
	{
		int numOfDecrease = 0; // number of cells hit by user until he hit the whole shop

		if (shipDirection == Direction::HORIZONTAL) // if HORIZONTAL:
				                                    // 1) goes left and right
													// 2) sums up the number of cells hit while current cells are not empty and marked
		{
			int cellRight = col + 1;
			int cellLeft = col - 1;

			while (cellRight < 10 && !field[row][cellRight].isEmpty())
			{
				++numOfDecrease;
				++cellRight;
			}

			while (cellLeft >= 0 && !field[row][cellLeft].isEmpty())
			{
				++numOfDecrease;
				--cellLeft;
			}
		}
		else										// if VERTICAL:
				                                    // 1) goes up and down
													// 2) sums up the number of cells hit while current cells are not empty and marked
		{
			int cellTop = row - 1;
			int cellBottom = row + 1;

			while (cellTop >= 0 && !field[cellTop][col].isEmpty())
			{
				++numOfDecrease;
				--cellTop;
			}

			while (cellBottom < 10 && !field[cellBottom][col].isEmpty())
			{
				++numOfDecrease;
				++cellBottom;
			}
		}
		
		if (field == enemy->getField()) // if the field observed belongs to enemy, customizes player's sidebar
		{
			playerInfo.numOfCells -= numOfDecrease;
		}
		else // if the field observed belongs to player, customizes enemy's sidebar
		{
			enemyInfo.numOfCells -= numOfDecrease;
		}
	}
	
}

bool FieldView::playerWon() const
{
	return playerInfo.score == 10;
}

bool FieldView::enemyWon() const
{
	return enemyInfo.score == 10;
}