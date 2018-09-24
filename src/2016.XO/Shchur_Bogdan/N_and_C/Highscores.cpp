#include "Highscores.h"
#include "Printer.h"
#include "Console.h"
#include "StartView.h"
#include <conio.h>

HighscoresView::HighscoresView()
{
	ifstream file("Highscore.txt");
	for (int i = 0; i < 5; ++i)
	{
		file >> result[i];
	}
}

void HighscoresView::draw()
{
	system("cls");
	Printer highscore(ConsoleColor::LightGray, ConsoleColor::Red);
	Printer Exithighscore(ConsoleColor::LightGray, ConsoleColor::Red);
	setCursor(consoleWidth / 4, 4);
	highscore << "NAME";
	setCursor((consoleWidth / 4) * 3, 4);
	cout << "Score";
	for (int i = 0; i < 5; ++i)
	{
		setCursor(consoleWidth / 4, i + 5);
		cout << result[i].name;
		setCursor((consoleWidth / 4) * 3, i + 5);
		cout << result[i].score;
	}
	printTextOnTheCenter(consoleHeight - 10, "   | > Back < |   ", Exithighscore);
}
View * HighscoresView::handle()
{
	View* nextView = this;
	switch (_getch())
	{
	case 8://Backspace
		nextView = new StartView;
	case 13://Enter
		nextView = new StartView;
	case 27://Esc
		nextView = new StartView;
	}
	return nextView;
}

bool isInTable(short numb)
{
	ifstream file("Highscore.txt");
	bool isAchieved = false;
	Result inresult[5];
	for (int i = 0; i < 5; ++i)
	{
		file >> inresult[i];
	}
	for (int i = 0; i < 5; ++i)
	{
		if (numb > inresult[i].score)
		{
			isAchieved = true;
			break;
		}
	}
	file.clear();
	file.seekg(0);
	return isAchieved;
}
void putInTable(Result r, Result result[], ofstream& out)
{
	for (int i = 0; i < 5; ++i)
	{
		if (r.score > result[i].score)
		{
			for (int j = 4; j > i; --j)
			{
				result[j].name = result[j - 1].name;
				result[j].score = result[j - 1].score;
			}
			result[i].name = r.name;
			result[i].score = r.score;
			break;
		}
	}
	for (int i = 0; i < 5; ++i)
	{
		out << result[i];
	}
}
ostream& operator<<(ostream& out, const Result& r)
{
	return out << r.name << " " << r.score << endl;
}
istream& operator>>(istream& in, Result& r)
{
	return in >> r.name >> r.score;
}
