#include "HighscoresView.h"

View * HighscoresView::handle()
{
	View* nextView = this;
	switch (_getch())
	{
	case ESCAPE:
		nextView = new StartView();
	case Enter:
		nextView = new StartView();
	}
	return nextView;
}
istream & operator >> (istream &in, Result &r)
{
	return in >> r.name >> r.score;
}

ostream & operator<<(ostream &out, const Result &r)
{
	return out << r.name << " " << r.score << endl;
}


bool isInTable(short numb)
{
	ifstream file("Highscore.txt");
	bool isAchieved = false;
	Result inresult[10];
	for (int i = 0; i < 10; ++i)
	{
		file >> inresult[i];
	}
	for (int i = 0; i < 10; ++i)
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

void putInTable(Result r, Result result[], ofstream &out)
{
	for (int i = 0; i < 10; ++i)
	{
		if (r.score > result[i].score)
		{
			for (int j = 9; j > i; --j)
			{
				result[j].name = result[j - 1].name;
				result[j].score = result[j - 1].score;
			}
			result[i].name = r.name;
			result[i].score = r.score;
			break;
		}
	}
	for (int i = 0; i < 10; ++i)
	{
		out << result[i];
	}
}

HighscoresView::HighscoresView()
{
	ifstream file("Highscore.txt");
	for (int i = 0; i < 10; ++i)
	{
		file >> result[i];
	}
}

void HighscoresView::draw()
{
	system("cls");
	Printer header(ConsoleColor::White, ConsoleColor::LightGray);
	Printer highscore(ConsoleColor::White, ConsoleColor::DarkGray);
	Printer Exithighscore(ConsoleColor::White, ConsoleColor::LightBlue);
	
	Printer WhiteHole(ConsoleColor::White, ConsoleColor::White);
	for (int i = 7; i < consoleHeight - 8; ++i)
	{
		setCursor(0, i);
		for (int j = 0; j < consoleWidth; ++j)
		{
		WhiteHole << " ";
		}
	}
	printInCenter(2, "Your highscores", header);
		
	printInCenter(consoleHeight - 5, "*Back*", Exithighscore);
	
	setCursor(consoleWidth / 4 + 3, 7);
	header << "Name: ";
	setCursor((consoleWidth / 3) * 2, 7);
	header << "Score: ";
	for (int i = 0; i < 10; ++i)
	{
		setCursor(consoleWidth / 4 + 3, i + 8);
		highscore << result[i].name;
		setCursor((consoleWidth / 3) * 2, i + 8);
		highscore << result[i].score;
	}
}

