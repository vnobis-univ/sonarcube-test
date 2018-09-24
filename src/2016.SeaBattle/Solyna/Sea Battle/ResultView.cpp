#include "ResultView.h"

bool ResultView::achievedTheHighScore()
{
	return currentPlayer > arrayOfPlayers[size- 1];
}

void ResultView::printingPlayersName()
{
	int key = _getch();

	if (lang == Languages::English)
	{
		ifKeyIsAnArrow(key);
		for (int i = 0; i < 13; ++i)
		{
			if (key >= 'A' && key <= 'Z' || key >= 'a' && key <= 'z')
			{
				if (i != 12)
				{
					nameOfPlayer.push_back(char(key));
					draw();
				}
				else
				{
					i--;
				}
			}
			else if (key == 8 && i > 0)
			{
				i = i - 2;
				nameOfPlayer.pop_back();
				draw();
			}
			else if (key == 13 && i > 0)
			{
				return;
			}
			else
			{
				--i;
			}
			key = _getch();

			ifKeyIsAnArrow(key);
		}
	}
	else
	{
		for (int i = 0; i < 13; ++i)
		{
			if (key == 175 ||
				key == 165 ||
				key >= 178 && key <= 180 ||
				key == 170 ||
				key == 186 ||
				key >= 191 && key <= 217 ||              // ascii value of ukrainian letters
				key == 220 ||
				key >= 222 && key <= 249 ||
				key == 252 ||
				key >= 254 && key <= 255)
			{
				if (i != 12)
				{
					nameOfPlayer.push_back(char(key));
					draw();
				}
				else
				{
					i--;
				}
			}
			else if (key == 8 && i > 0)
			{
				i = i - 2;
				nameOfPlayer.pop_back();
				draw();
			}
			else if (key == 13 && i > 0)
			{
				return;
			}
			else
			{
				--i;
			}
			key = _getch();
		}
	}
}
void ResultView::sortArrayOfPlayers()
{
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			if (arrayOfPlayers[j] > arrayOfPlayers[i])
			{
				Player temp = arrayOfPlayers[i];
				arrayOfPlayers[i] = arrayOfPlayers[j];
				arrayOfPlayers[j] = temp;
			}
		}
	}
	
	for (int i = 0; i < size; ++i)
	{
		of << arrayOfPlayers[i] << endl;
	}
}

void ResultView::ifKeyIsAnArrow(int &key)
{
	while (key == 224 || key == 0)
	{
		key = _getch();
		key = _getch();
	}
}

ResultView::ResultView(Languages l, TypeOfGame t):
	View(l, t),
	nameOfPlayer("")
{
	currentPlayer = Player(nameOfPlayer, score);
	in = ifstream("HighScores.txt");
	for (int i = 0; i < size; ++i)
	{
		in >> arrayOfPlayers[i];
	}
	if (achievedTheHighScore())
	{
		of = ofstream("HighScores.txt");
	}
}

void ResultView::draw()
{
	clean();
	Printer mainPrinter(mainTextColor, mainBackgroundColor);
	Printer namePrinter(textColor, mainBackgroundColor);
	if (lang ==Languages:: English)
	{
		if (achievedTheHighScore())
		{
			printAtCenterOfLine(11, "You achieved the high score !!!", mainPrinter, consoleWidth);
			printAtCenterOfLine(12, "Please, enter your name", mainPrinter, consoleWidth);
			printAtCenterOfLine(13, nameOfPlayer, namePrinter, consoleWidth);
		}
		else
		{
			printAtCenterOfLine(12, "You didn't achieve the high score :(", mainPrinter, consoleWidth);
		}
	}
	else
	{
		if (achievedTheHighScore())
		{
			printAtCenterOfLine(11, "Ви побили рекорд !!!", mainPrinter, consoleWidth);
			printAtCenterOfLine(12, "Будь ласка, введіть ваше ім'я", mainPrinter, consoleWidth);
			printAtCenterOfLine(13, nameOfPlayer, namePrinter, consoleWidth);
		}
		else
		{
			printAtCenterOfLine(12, "Ви не побили рекорд :(", mainPrinter, consoleWidth);
		}
	}
}

View * ResultView::handle()
{
	if (achievedTheHighScore())
	{
		printingPlayersName();
		currentPlayer.setName(nameOfPlayer);
		arrayOfPlayers[6] = currentPlayer;
		sortArrayOfPlayers();
		setConsoleSize(100, 25);
		score = 0;
		return new HighScoresView(lang, type);
	}
	draw();
	int key = _getch();
	while (key)
	{
		if (key == 13)
		{
			setConsoleSize(100, 25);
			score = 0;
			return new HighScoresView(lang, type);
		}
		key = _getch();
	}
}

