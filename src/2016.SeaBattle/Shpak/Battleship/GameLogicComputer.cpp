#include "GameLogicComputer.h" 
#include "GameField.h"
#include "ConsoleManipulators.h"
#include "LanguageManipulator.h"
#include "GameMessages.h"
#include <time.h>

GameLogicComputer::Difficulty GameLogicComputer::gameDifficulty = Difficulty::hard;

GameLogicComputer::GameLogicComputer(COORD coord):
	GameLogic(coord),
	score(0)
{
	oponentField.randomShipPlacement();
}

bool GameLogicComputer::handlePlayerChoice(int index_i, int index_j, bool& isEndOfCurrentGame, bool& isBadChoiceInput)
{
	if (oponentField.getIfShipOnCell(index_i, index_j))
	{
		score += 20;

		int sunkShipSize = oponentField.placeHit(index_i, index_j);

		if (sunkShipSize > 0)
		{
			score += 200 - sunkShipSize * 40;
		}

		if (oponentField.getNumberOfShipsLeft() == 0)
		{
			score += 400;

			redrawScore(getScore());

			GameMessages().drawWin();

			oponentField.renewField();

			oponentField.randomShipPlacement();

			oponentField.drawField();

			isEndOfCurrentGame = true;
		}

		redrawScore(getScore());

		return true;
	}
	else if (oponentField.getIfEmptyCell(index_i, index_j))
	{
		oponentField.placeMiss(index_i, index_j);
	}
	else
	{
		isBadChoiceInput = true;
	}

	return false;
} 

bool GameLogicComputer::handleOponentChoice(GameField& playerField, bool& isLose)
{
	srand(time(NULL));

	bool isPossibleChoice = false;

	switch (gameDifficulty)
	{
		case GameLogicComputer::Difficulty::easy:
		{
			// just random choice

			std::vector<std::pair<int, int>> vecOfPossible;

			for (size_t i = 0; i < 10; ++i)
			{
				for (size_t j = 0; j < 10; ++j)
				{
					if (!playerField.getIfMiss(i, j) && !playerField.getIfHitShipOnCell(i, j))
					{
						vecOfPossible.push_back(std::make_pair(i, j));
					}
				}
			}

			std::pair<int, int> toCheck = vecOfPossible[rand() % vecOfPossible.size()];

			if (playerField.getIfShipOnCell(toCheck.first, toCheck.second))
			{
				playerField.placeHit(toCheck.first, toCheck.second);

				isPossibleChoice = true;

				return true;
			}
			else if ((playerField.getIfEmptyCell(toCheck.first, toCheck.second)))
			{
				playerField.placeMiss(toCheck.first, toCheck.second);

				isPossibleChoice = true;
			}
		}
		break;

		case GameLogicComputer::Difficulty::hard:
		{
			// random choice but priority on shootin around hit ship 

			std::pair<int, int> toCheck = std::make_pair(-1, -1);
			std::vector<std::pair<int, int>> vecOfPossible;

			for (size_t i = 0; i < 10; ++i)
			{
				for (size_t j = 0; j < 10; ++j)
				{
					if (playerField.getIfHitShipOnCell(i, j))
					{
						// here some sweet logic

						searchForPossibleAround(playerField, toCheck, i, j); //recursive function

						if (toCheck.first != -1) // if some variant around hit found 
						{
							break;
						}
					}
					else if (!playerField.getIfMiss(i, j))
					{
						vecOfPossible.push_back(std::make_pair(i, j));
					}
				}

				if (toCheck.first != -1) // if some variant around hit found
				{
					break;
				}
			}

			if ((toCheck.first == -1)) 
			{
				// if nothing nice found than just random

				toCheck = vecOfPossible[rand() % vecOfPossible.size()];
			}
				

			if (playerField.getIfShipOnCell(toCheck.first, toCheck.second))
			{
				playerField.placeHit(toCheck.first, toCheck.second);

				isPossibleChoice = true;

				isLose = playerField.getNumberOfShipsLeft() == 0;

				return true;
			}
			else if ((playerField.getIfEmptyCell(toCheck.first, toCheck.second)))
			{
				playerField.placeMiss(toCheck.first, toCheck.second);

				isPossibleChoice = true;
			}
		}
		break;
	}

	return false;
}

bool GameLogicComputer::searchForPossibleAround(GameField& playerField, std::pair<int, int>& toCheck, int index_i, int index_j, int from_i, int from_j)
{
	// recursive function for hard level logic

	srand(time(NULL));

	std::vector<std::pair<int, int>> somePossible;
	
	for (int i = -1; i <= 1; ++i)
	{
		if (index_i + i < 0 || index_i + i >= 10) //check for edge of field
			continue;

		for (int j = -1; j <= 1; ++j)
		{

			if (index_j + j < 0 || index_j + j >= 10) // check for edge of field
				continue;

			if (index_i + i == from_i && index_j + j == from_j) // in order not to cause infinite recursive call
				continue;

			if ((j == -1 && i == -1) || (j == -1 && i == 1) || (j == 1 && i == -1) || (j == 1 && i == 1) || (j == 0 && i == 0))
			{
				// exclude pairs (-1, -1), (-1, 1), (1, -1), (1, 1) and (0, 0)
				continue;
			}

			// check for hit ship
			if (playerField.getIfHitShipOnCell(index_i + i, index_j + j))
			{
				if (searchForPossibleAround(playerField, toCheck, index_i + i, index_j + j, index_i, index_j)) // recursive call
					return true;
			}
			else if (!playerField.getIfMiss(index_i + i, index_j + j))
			{
				somePossible.push_back(std::make_pair(index_i + i, index_j + j));
			}
		}
	}

	if (somePossible.size() != 0)
	{
		toCheck = somePossible[rand() % somePossible.size()];

		return true;
	}

	return false;
}

void setGameDifficulty(GameLogicComputer::Difficulty newDifficulty)
{
	GameLogicComputer::gameDifficulty = newDifficulty;
}

int getGameDifficulty()
{
	return int(GameLogicComputer::gameDifficulty);
}

int GameLogicComputer::getScore()
{
	return GameLogicComputer::score;
}

bool GameLogicComputer::isOnlineJoinedGame() const
{
	return false;
}

void redrawScore(int score)
{
	setCursoreAtPosition(0, 14);

	Printer(Color::gray, Color::black).printAtCenter(LanguageManipulator().getHowToDrawScore() + std::to_string(score));
}