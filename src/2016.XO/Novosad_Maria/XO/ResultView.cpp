#include "ResultView.h"
#include <iostream>
#include <string>
#include <conio.h>
#include "HighScoresView.h"
#include "StartView.h"
#include "Player.h"
#include <fstream>
#include "Globals.h"
#include "ConsoleFunctions.h"
using namespace std;
ResultView::ResultView()
{
}

ResultView::ResultView(int score) : score(score)
{
}

int ResultView:: getScore()
{
	return score;
}

void ResultView::draw()
{
	printAtCenterOfLine(4, "Your score: " + to_string(score), yellowSymbolsGreenBackground);
	printAtCenterOfLine(5, "---------------", lightGreenSymbolsGreenBackground);
	printAtCenterOfLine(10, "--------------------------", lightGreenSymbolsGreenBackground);
	printAtCenterOfLine(18, "--------------------------", lightGreenSymbolsGreenBackground);

	for (int i = 0; i < 7; i++)
	{
		setCursoreAtPosition(11, 11 + i);
		lightGreenSymbolsGreenBackground.print("|");
	}

	for (int i = 0; i < 7; i++)
	{
		setCursoreAtPosition(38, 11 + i);
		lightGreenSymbolsGreenBackground.print("|");
	}

	if (hasAchievedHighscore())
	{
		printAtCenterOfLine(12, "You've achieved highscore!", yellowSymbolsGreenBackground);
		printAtCenterOfLine(13, "Congratulations!", yellowSymbolsGreenBackground);
		printAtCenterOfLine(14, "Please, enter your name", yellowSymbolsGreenBackground);
		printAtCenterOfLine(15, "(Not more than 7 symbols)", yellowSymbolsGreenBackground);
	}
	else
	{
		printAtCenterOfLine(13, "Sorry, you've lost :(", yellowSymbolsGreenBackground);
		printAtCenterOfLine(15, "Please, try again", yellowSymbolsGreenBackground);
	}
}

void swap(Player& a, Player& b)
{
	Player c(a);
	a = b; 
	b = c;
}

void returnNewHighscoresList(Player& player)
{
	ofstream out("Text.txt");
	global_players[5] = player;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (global_players[j].getScore() < global_players[j + 1].getScore())
			{
				swap(global_players[j], global_players[j + 1]);
			}
		}
	}
	for (int i = 0; i < 6; i++)
	{
		out << global_players[i];
	}
}

bool ResultView::hasAchievedHighscore()
{
	for (int i = 0; i < 6; i++)
	{
		if (score > global_players[i].getScore())
		{
			return true;
		}
	}
	return false;
}

View* ResultView::handle()
{
	View* newView = this;
	if (hasAchievedHighscore())
	{
		setCursoreAtPosition(21, 16);
		std::string name;
		std::cin >> name;
		Player winner(name, score);
		returnNewHighscoresList(winner);
		newView = new HighScoresView();
	}
	else
	{
		int key = _getch();
		if (key == KEY_ENTER)
		{
			newView = new StartView();
		}
	}
	return newView;
}
