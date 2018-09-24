#include "HighScoreView.h"
#include "Printer.h"
#include "Console.h"
#include "StartView.h"
#include <conio.h>
#include "Complexity.h"
#include <iostream>

Result::Result() :name("-"), score(0), life(0), complexity1(parseComplexityToString(Complexity::None)) {}
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
	if (language == "Eng")
	{
		setLangToEng();
		options[0] = "NAME";
		options[1] = "SCORE";
		options[2] = "COMPLEXITY";
		options[3] = "LIFES";
		options[4] = "Back";
		options[5] = "HIGH SCORES";
	}
	if (language == "Ukr")
	{
		setLangToUkr();
		options[0] = "Iм*я";
		options[1] = "Рахунок";
		options[2] = "Складнiсть";
		options[3] = "Життя";
		options[4] = "Назад";
		options[5] = "Найкращi результати";
	}
}
void HighscoreView::draw()
{

	View::draw();
	setOptions();
	Printer Exithighscore(Color::LIGHT_RED, Color::BLACK);
	printAtCenterOfLine(2, options[5], defaultPrinter);
	setCursoreAtPosition(consoleWidth / 8 - 4, 4);
	defaultPrinter << options[0];
	setCursoreAtPosition((consoleWidth / 8) * 3 - 4, 4);
	defaultPrinter << options[1];
	setCursoreAtPosition((consoleWidth / 8) * 5 - 4, 4);
	defaultPrinter << options[3];
	setCursoreAtPosition((consoleWidth / 8) * 7 - 4, 4);
	defaultPrinter << options[2];
	int k = 5;
	for (int i = 0; i < 10; ++i)
	{
		setlocale(LC_ALL, "C");
		k++;
		setCursoreAtPosition(consoleWidth / 8 - 4, i + k);
		defaultPrinter << result[i].name;
		setCursoreAtPosition((consoleWidth / 8) *3 - 4, i + k);
		defaultPrinter << to_string(result[i].score);
		setCursoreAtPosition((consoleWidth / 8) * 5 - 4, i + k);
		defaultPrinter << to_string(result[i].life);
		setCursoreAtPosition((consoleWidth / 8) * 7 - 4, i + k);
		setlocale(LC_ALL, "Ukrainian");
		defaultPrinter << result[i].complexity1;
	}
	setlocale(LC_ALL, "Ukrainian");
	printAtCenterOfLine(consoleHeight - 10, options[4], Exithighscore);
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
				result[j].life = result[j - 1].life;
				result[j].complexity1 = result[j - 1].complexity1;
			}
			result[i].name = r.name;
			result[i].score = r.score;
			result[i].life = r.life;
			result[i].complexity1 = r.complexity1;
			break;
		}
		else if (r.score == result[i].score)
		{
			if (r.life > result[i].life)
			{
				for (int j = 9; j > i; --j)
				{
					result[j].name = result[j - 1].name;
					result[j].score = result[j - 1].score;
					result[j].life = result[j - 1].life;
					result[j].complexity1 = result[j - 1].complexity1;
				}
				result[i].name = r.name;
				result[i].score = r.score;
				result[i].life = r.life;
				result[i].complexity1 = r.complexity1;
				break;
			}
		}
	}
	for (int i = 0; i < 10; ++i)
	{
		out << result[i];
	}
}
ostream& operator<<(ostream& out, const Result& r)
{
	return out << r.name << " " << r.score << "  " << r.life << "  " << r.complexity1 << endl;
}
istream& operator>>(istream& in, Result& r)
{
	return in >> r.name >> r.score >> r.life >> r.complexity1;
}
