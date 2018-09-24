#include "ResultView.h"
#include "StartView.h"
#include "Player.h"
#include "HighScoreView.h"
#include "Utils.h"
#include <fstream>
#include <conio.h>
#include "ExternVar.h"

ResultView::ResultView() {}
ResultView::ResultView(int score1) : score(score1) {}
void typeName();
void ResultView::draw()
{
	system("cls");
	typeName();
	Printer prInfo(Color::BLUE, Color::LIGHT_WHITE);
	printAtCenter(9, "YOUR SCORE IS : " + to_string(score), prInfo);
	if (hasAchievedHighscore())
	{
		printAtCenter(10, "CONGRATULATIONS !!!", prInfo);
		printAtCenter(11, "YOU ACHIEVED HIGHSCORE;)", prInfo);
		printAtCenter(12, "ENTER YOUR NAME, PLEASE", prInfo);
		printAtCenter(13, "(only 7 letters are possible)", prInfo);
	}
	else
	{
		printAtCenter(10, "YOU DIDN'T ACHIEVE HIGHSCORE;(", prInfo);
		printAtCenter(11, "BUT YOU CAN TRY AGAIN, DON'T GIVE UP", prInfo);
		printAtCenter(15, "[ PRESS ENTER TO BACK TO MENU ]", prInfo);
	}
}

void listWithNew(Player& gamer1)
{
	ofstream out("ScoresList.txt");
	playersList[4] = gamer1;
	for (int i = 1; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (playersList[j].getScore() < playersList[j + 1].getScore())
			{
				Player swapPlayer = playersList[j];
				playersList[j] = playersList[j + 1];
				playersList[j + 1] = swapPlayer;
			}
		}
	}
	for (int i = 0; i < 5; i++)
	{
		out << playersList[i].getName() << " " << playersList[i].getScore() << endl;
	}
}

bool ResultView::hasAchievedHighscore()
{
	readPlayersList();
	if (score > playersList[4].getScore())
	{
		return true;
	}
	else 
		return false;
}

View* ResultView ::handle ()
{
	View* nextView = this;
	if (hasAchievedHighscore())
	{
		string name;
		char plName[7];
		moveCursorTo(24, 16);
		Printer prInfo(Color::BLUE, Color::LIGHT_WHITE);
		prInfo >> plName;
		for (int i = 0; i < 7; i++)
		{
			name += plName[i];
		}
		Player plN(name, score);
		listWithNew(plN);
		nextView = new HighScoreView;
		return nextView;
	}
	else
	{
		int button;
		while (true)
		{
			button = _getwch();
			switch (button)
			{
				case 13:
				{
					nextView = new StartView;
					return nextView;
				}	
				break;
				default:
				{
					nextView = this;
					return nextView;
				}
			}
		}
	}
}
