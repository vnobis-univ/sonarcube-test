#include "HighScores.h"
#include "Printer.h"
#include "Console.h"
#include "StartView.h"
#include <conio.h>

HighScoresView::HighScoresView()
{
	ifstream is("Highscores.txt");
	for (size_t i = 0; i < 10; ++i)
	{
		is >> result[i];
	}
}

void HighScoresView::draw()
{
	system("cls");
	Printer higscore(Color::LightGray, Color::Blue);
	setCursor(consoleWidth / 4, 4);
	higscore << "Name";
	setCursor((consoleWidth / 4) * 3, 4);
	higscore << "Score";

	for (size_t i = 0; i < 10; ++i)
	{
		setCursor(consoleWidth / 4, 6 + i);
		cout << result[i].name;
		setCursor((consoleWidth / 4) * 3, 6 + i);
		cout << result[i].score;
	}

	printInCenter(consoleHeight - 12, "* Press Esc to exit *", higscore);
}

View* HighScoresView::handle()
{
	View *nextView = this;
	switch (_getch())
	{
	case 27:
		nextView = new StartView;
	}
	return nextView;
}

bool inTable(short num)
{
	ifstream is("Highscores.txt");
	bool toPut = false;
	Result isresult[10];

	for (size_t i = 0; i < 10; ++i)
	{
		is >> isresult[i];
	}

	for (size_t i = 0; i < 10; ++i)
	{
		if (num>isresult[i].score)
		{
			toPut = true;
			break;
		}
	}
	is.clear();
	is.seekg(0);
	return toPut;
}

void writeIn(Result res, Result result[], ofstream& out)
{
	for (size_t i = 0; i < 10; ++i)
	{
		if (res.score>result[i].score)
		{
			for (size_t j = 9; j > i; --j)
			{
				result[j].name = result[j - 1].name;
				result[j].score = result[j - 1].score;
			}
			result[i].name = res.name;
			result[i].score = res.score;
			break;
		}
	}

	Result temp;
	for (size_t i = 0,max; i < 9; i++)
	{
		max = i;
		for (size_t j = i + 1; j < 10; ++j)
		{
			if (result[j].score > result[max].score)
			{
				max = j;
				temp = result[j];
				result[j] = result[i];
				result[i] = temp;
			}
		}
		
	}
	for (size_t i = 0; i < 10; i++)
	{
		out << result[i];
	}
}

ostream& operator<<(ostream& out, const Result& res)
{
	return out << res.name << " " << res.score << endl;
}

istream& operator>>(istream& in, Result& res)
{
	return in >> res.name >> res.score;
}