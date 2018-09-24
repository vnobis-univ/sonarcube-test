#include "GameLogicOnline.h"
#include "GameMessages.h"
#include <conio.h>
#include <string>
#include <time.h>

GameLogicOnline::GameLogicOnline(COORD coord, bool isHostGame) :
	GameLogic(coord),
	lastChoiceState("  ")
{
	if (isHostGame)
	{
		connectionType = ConnectionType::hostGame;
	}
	else
	{
		connectionType = ConnectionType::joinGame;
	}
}

bool GameLogicOnline::handlePlayerChoice(int index_i, int index_j, bool& isEndOfCurrentGame, bool& isBadChoiceInput)
{
	if (oponentField.getIfMiss(index_i, index_j) || oponentField.getIfHitShipOnCell(index_i, index_j))
	{
		isBadChoiceInput = true;

		return false;
	}

	std::string toPost = std::to_string(index_i) + std::to_string(index_j);

	serverManipulator.post(toPost);

	std::string newState;

	clock_t begin = clock();

	while (true)
	{
		while (((unsigned long)clock() - begin) / CLOCKS_PER_SEC < 0.5)
		{/*timer*/}

		newState = serverManipulator.get();

		if (newState != toPost)
		{
			while (_kbhit())
			{
				// to remove all clicked buttons while looping

				if (_getch() == 224)
				{
					_getch();
				}
			}

			break;
		}
	}

	if (newState == "hit")
	{

		oponentField.placeHit(index_i, index_j, false);

		isEndOfCurrentGame = oponentField.getNumberOfShipsLeft() == 0;
	}
	else if (newState == "sunk")
	{
		oponentField.placeHit(index_i, index_j, true);

		isEndOfCurrentGame = oponentField.getNumberOfShipsLeft() == 0;
	}
	else if (newState == "miss")
	{
		oponentField.placeMiss(index_i, index_j);

		return false;
	}

	if (isEndOfCurrentGame)
	{
		GameMessages().drawWin();
	}
	
	return true;
}

bool GameLogicOnline::handleOponentChoice(GameField& playerField, bool& isLose)
{
	std::string state;

	clock_t begin = clock();

	GameMessages().drawWaintUntilMakeMove();

	while (true)
	{
		while (((unsigned long)clock() - begin) / CLOCKS_PER_SEC < 0.5)
		{/*timer*/}

		state = serverManipulator.get();

		if (state.length() == 2 && state != lastChoiceState) // length == 2 only when 2 digits
		{
			while (_kbhit())
			{
				// to remove all clicked buttons while looping

				if (_getch() == 224)
				{
					_getch();
				}
			}

			lastChoiceState = state;
			break;
		}
	}
	GameMessages().clearHints();

	int index_i = int(state[0] - '0');
	int index_j = int(state[1] - '0');


	if (playerField.getIfShipOnCell(index_i, index_j))
	{
		if (playerField.placeHit(index_i, index_j, true) > 0)
		{
			serverManipulator.post("sunk");
		}
		else
		{
			serverManipulator.post("hit");
		}

		isLose = playerField.getNumberOfShipsLeft() == 0;


		return true;
	}
	else if (playerField.getIfEmptyCell(index_i, index_j))
	{
		playerField.placeMiss(index_i, index_j);

		serverManipulator.post("miss");

		return false;
	}

	return true;
}

bool GameLogicOnline::connectToGame()
{
	switch (connectionType)
	{
	case GameLogicOnline::ConnectionType::hostGame:
	{
		std::wstring id = serverManipulator.getNewRoom();
		serverManipulator.setRoom(id);
		serverManipulator.post("Created");

		GameMessages().drawWaitUntilJoin(stoi(id));

		clock_t begin = clock();

		while (true)
		{
			while (((unsigned long)clock() - begin) / CLOCKS_PER_SEC < 0.5)
			{/*timer*/}

			if (serverManipulator.get() == "Joined")
			{
				while (_kbhit())
				{
					// to remove all clicked buttons while looping

					if (_getch() == 224)
					{
						_getch();
					}
				}

				break;
			}
		}

		GameMessages().clearHints();
	}
	break;

	case GameLogicOnline::ConnectionType::joinGame:
	{
		bool isJoined = false;

		while (!isJoined)
		{
			try
			{
				serverManipulator.setRoom(GameMessages().getIdForGame());

				if (serverManipulator.get() == "Created")
				{
					serverManipulator.post("Joined");

					serverManipulator.get() == "Joined";

					isJoined = true;
				}
			}
			catch (...)
			{

			}	

			GameMessages().clearHints();
		}
	}

	break;
	}

	return true;
}

bool GameLogicOnline::isOnlineJoinedGame() const
{
	return connectionType == ConnectionType::joinGame;
}