#include "ResultView.h"
#include "StartView.h"
#include "HighScoreView.h"
#include <conio.h>

ResultView::ResultView()
{
}

ResultView::ResultView(int _score, Language _language): score(_score), 
	language(_language), isNameEntered(false), counter(0)
{
}

bool ResultView::hasAchievedHighscore()
{
	readPlayersList(language);
	if (score > playersList[4].getScore())
	{
		return true;
	}
	else
		return false;
}

void ResultView::printLogo()
{
	string gameLine;
	if (language == Language::ENGLISH)
	{
		gameLine = "SEA BATTLE";
	}
	else
	{
		gameLine = "Морський бій";
	}
	printAtCenter(0, gameLine, redTextYellowBG);
}

void ResultView::listWithNew(Player& gamer1)
{	
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
	if (language == Language::ENGLISH)
	{
		ofstream out("HighScores.txt");
		for (int i = 0; i < 5; i++)
		{
			out << playersList[i].getName() << " " << playersList[i].getScore() << endl;
		}
	}
	else
	{
		ofstream out("Рекорди.txt");
		for (int i = 0; i < 5; i++)
		{
			out << playersList[i].getName() << " " << playersList[i].getScore() << endl;
		}
	}
}

void ResultView::draw()
{
	if (language == Language::ENGLISH)
	{
		printAtCenter(8, "YOUR SCORE IS : " + to_string(score), redTextWhiteBG);
		if (hasAchievedHighscore())
		{
			printAtCenter(10, "CONGRATULATIONS !!!", redTextWhiteBG);
			printAtCenter(12, "YOU ACHIEVED HIGHSCORE;)", redTextWhiteBG);
			printAtCenter(14, "ENTER YOUR NAME, PLEASE", redTextWhiteBG);
			printAtCenter(16, "(only 7 letters are possible)", redTextWhiteBG);
		}
		else
		{
			printAtCenter(10, "YOU DIDN'T ACHIEVE HIGHSCORE;(", redTextWhiteBG);
			printAtCenter(12, "BUT YOU CAN TRY AGAIN, DON'T GIVE UP", redTextWhiteBG);
			printAtCenter(14, "PRESS ENTER TO RETURN TO MENU", redTextWhiteBG);
		}
		moveCursorTo(10, 20);
		redTextWhiteBG << playerName;
	}
	else
	{
		printAtCenter(8, "Ваш рахунок : " + to_string(score), redTextWhiteBG);
		if (hasAchievedHighscore())
		{
			printAtCenter(10, "Вітаємо !!!", redTextWhiteBG);
			printAtCenter(12, "Ви побили рекорд;)", redTextWhiteBG);
			printAtCenter(14, "Введіть своє ім'я, будь ласка", redTextWhiteBG);
			printAtCenter(16, "(можливо не більше,ніж 7 букв)", redTextWhiteBG);
		}
		else
		{
			printAtCenter(10, "Ви не побили рекорд;(", redTextWhiteBG);
			printAtCenter(12, "Спробуйте ще раз, не здавайтесь!", redTextWhiteBG);
			printAtCenter(14, " Натисність ENTER, щоб повернутися в меню ", redTextWhiteBG);
		}
		moveCursorTo(10, 20);
		redTextWhiteBG << playerName;
	}
}

View * ResultView::handle()
{
	View * nextView = this;
	if (hasAchievedHighscore())
	{
		int key = _getch();
		if (key == 13 && playerName.size() != 0)
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
			Player newPlayer(playerName, score);
			listWithNew(newPlayer);
			nextView = new HighScoreView(language);
		}
	}
	else
	{
		int button;
		switch (_getwch())
		{
		case KEY_ENTER:
		{
			nextView = new StartView(language);
		}
		break;
		}
	}
	return nextView;
}