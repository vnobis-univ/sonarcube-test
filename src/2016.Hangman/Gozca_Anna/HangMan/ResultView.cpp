#include "ResultView.h"
#include "StartView.h"
#include "HighScoreView.h"
#include "ConsoleUtils.h"
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <iostream>

int numberOfPlayersForLevel = 4;

ResultView::ResultView() {}
ResultView::ResultView(int _score, string _levelName, int _numOfGuessedLet) :
	score(_score), levelName(_levelName), numOfGuessedLet(_numOfGuessedLet), isNameEntered(false), counter(0) {}

void typeName();
void ResultView::draw()
{
	typeName();
	printAtCenter(8, "YOUR SCORE IS : " + to_string(score), blueTextGrayBG);
	if (hasAchievedHighscore())
	{
		printAtCenter(10, "CONGRATULATIONS !!!", blueTextGrayBG);
		printAtCenter(12, "YOU ACHIEVED HIGHSCORE;)", blueTextGrayBG);
		printAtCenter(14, "ENTER YOUR NAME, PLEASE", blueTextGrayBG);
		printAtCenter(16, "(only 7 letters are possible)", blueTextGrayBG);
	}
	else
	{
		printAtCenter(10, "YOU DIDN'T ACHIEVE HIGHSCORE;(", blueTextGrayBG);
		printAtCenter(12, "BUT YOU CAN TRY AGAIN, DON'T GIVE UP", blueTextGrayBG);
		printAtCenter(14, "[ PRESS ENTER TO RETURN TO MENU ]", blueTextGrayBG);
	}

	moveCursorTo(10, 20);
	blueTextGrayBG << playerName;
}

void insertPlayerForLevel(Player & player, int numberToAdd)
{
	playersList	[numberOfPlayersForLevel - 1 + numberToAdd] = player;
	for (size_t i = 1 + numberToAdd; i < numberOfPlayersForLevel + numberToAdd; i++)
	{
		for (size_t j = 0 + numberToAdd; j < numberOfPlayersForLevel + numberToAdd - 1; j++)
		{
			if (playersList[j].getScore() < playersList[j + 1].getScore())
			{
				swap(playersList[j], playersList[j + 1]);
			}
		}
	}
}

void swap(Player & prevPlayer, Player & nextPlayer)
{
	Player swapPlayer = prevPlayer;
	prevPlayer = nextPlayer;
	nextPlayer = swapPlayer;
}

void listWithNew(Player & gamer1)
{
	ofstream out("ScoresList.txt");

	if (gamer1.getLevel() == "HARD")
	{
		insertPlayerForLevel(gamer1, 0);
	}
	if (gamer1.getLevel() == "MEDIUM")
	{
		insertPlayerForLevel(gamer1, numberOfPlayersForLevel);
	}
	if (gamer1.getLevel() == "EASY")
	{
		insertPlayerForLevel(gamer1, numberOfPlayersForLevel *2);
	}
	// print in file list with new player
	for (int i = 0; i < numOfPlayers; i++)
	{
		out << playersList[i].getName() << " "<< playersList[i].getLevel()
			<< " " << playersList[i].getScore() << " " << playersList[i].getGuessedLetters() << endl;
	}
}

bool ResultView::hasAchievedHighscore()
{
	readPlayersList();
	bool isSucceed = false;

	if (levelName == "HARD")
	{
		if (score > playersList[3].getScore())
		{
			isSucceed = true;
		}
	}
	if (levelName == "MEDIUM")
	{
		if (score > playersList[7].getScore())
		{
			isSucceed = true;
		}
	}
	if (levelName == "EASY")
	{
		if (score > playersList[11].getScore())
		{
			isSucceed = true;
		}
	}
	return isSucceed;
}

View * ResultView::handle()
{
	View * nextView = this;
	if (hasAchievedHighscore())
	{
		int key = _getch();
		if( key == 13 && playerName.size() != 0)
		{ 
			isNameEntered = true;
		}
		else if (key == VK_BACK && playerName.size() != 0)
		{
			string temp = "";
			for (size_t i = 0; i < playerName.length() - 1; i++)
			{
				temp += playerName[i];
			}
			playerName = temp;
			--counter;
		}
		else if (counter != 7)
		{
			playerName += (char)key;
			++counter;
		}
		else
		{
			isNameEntered = true;
		}
		if (isNameEntered)
		{
			Player newPlayer(playerName, levelName, score, numOfGuessedLet);
			listWithNew(newPlayer);
			nextView = new HighScoreView;			
		}
	}
	else
	{
		int button;
		switch (_getwch())
		{
		case KEY_ENTER :
		{
			nextView = new StartView;
		}
		break;
		}
	}
	return nextView;
}
