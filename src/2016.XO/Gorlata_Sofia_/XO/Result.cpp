#include <iostream>
#include <fstream>
#include "MenuView.h"
#include "Result.h"
#include "Utils.h"
#include "HighScore.h"
#include "Field.h"
#include "View.h"
#include <windows.h>

using namespace std;

Result::Result(int playerScore) :
	currentScore(playerScore)
{};


void Result::draw()
{
	system("cls");

	system("color 90");
	redOnBlue.printOnCenter(12, "The game is over! Your scores: ");
	moveCursorTo(37, 13);
	redOnBlue.print(currentScore);
}


View * Result::handle()
{

	View* nextView = this;

	HighScore* highscore = new HighScore;
	string enterName;
	if (currentScore > highscore->getLow())
	{
		redOnBlue.printOnCenter(15, " You achived table scores. Enter your name: ");
		moveCursorTo(30, 16);
		showConsoleCursor(true);
		system("color 94");
		cin >> enterName;

		ofstream fout("Text.txt", std::ios::app);
		hScore res;
		res.player = enterName;
		res.score = currentScore;
		fout << res;

		nextView = new HighScore;
	}
	else
	{
		redOnBlue.printOnCenter(15, "You didn't achive table scores. Press ENTER in order to go to MENU.");
		bool pressedEnter = false;
		while (!pressedEnter)
		{
			switch (_getwch())
			{
			case 13:
				nextView = new MenuView;
				pressedEnter = true;
			}
		}
	}

	return nextView;
};
