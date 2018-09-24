#include "HighScoreView.h"
#include "Printer.h"
#include "Console.h"
#include "StartView.h"
#include <conio.h>
#include "Language.h"
#include <iostream>

Result::Result() :name("-"), score(0){}
HighscoreView::HighscoreView()
{
	ifstream file("Highscore.txt");
	for (int i = 0; i < 10; ++i)
	{
		file >> result[i];
	}
}

void HighscoreView::setOptions()
{
	if (language == Language::ENGLISH)
	{
		setLangToEng();
		options[0] = "NAME";
		options[1] = "SCORE";
		options[2] = "Back";
		options[3] = "HIGH SCORES";
	}
	if (language == Language::UKRAINIAN)
	{
		setLangToUkr();
		options[0] = "Iм*я";
		options[1] = "Рахунок";
		options[2] = "Назад";
		options[3] = "Найкращi результати";
	}
}
void HighscoreView::draw()
{

	View::draw();
	setOptions();
	Printer Exithighscore(Color::LIGHT_RED, Color::BLACK);
	printAtCenterOfLine(2, options[3], defaultPrinter);

	setCursoreAtPosition(consoleWidth / 8 + 8, 4);
	defaultPrinter << options[0];
	setCursoreAtPosition((consoleWidth / 8) * 5 + 8, 4);
	defaultPrinter << options[1];

	int k = 5;
	for (int i = 0; i < 10; ++i)
	{
		k++;
		setCursoreAtPosition(consoleWidth / 8 + 8, i + k);
		defaultPrinter << result[i].name;
		setCursoreAtPosition((consoleWidth / 8) * 5 + 8, i + k);
		defaultPrinter << to_string(result[i].score);
	}
	setlocale(LC_ALL, "Ukrainian");
	printAtCenterOfLine(consoleHeight - 10, options[2], Exithighscore);
}
View * HighscoreView::handle()
{
	View* nextView = this;
	char ch = _getch();

	while (ch != 13 && ch != 27)
	{
		ch = _getch();
	}

	return new StartView;
}

bool isInTable(int numb)
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
void putInTable(Result r, Result result[], ofstream& out)
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
ostream& operator<<(ostream& out, const Result& r)
{
	return out << r.name << " " << r.score << endl;
}
istream& operator>>(istream& in, Result& r)
{
	return in >> r.name >> r.score;
}
