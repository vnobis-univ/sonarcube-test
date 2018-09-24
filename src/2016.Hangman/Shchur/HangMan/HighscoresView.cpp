#include "HighscoresView.h"

istream & operator>>(istream &in, Result &r)
{
	return in >> r.name >> r.score >> r.level;
}

ostream & operator<<(ostream &out, const Result &r)
{
	return out << r.name << " " << r.score << " " << r.level << endl;
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
				result[j].level = result[j - 1].level;
			}
			result[i].name = r.name;
			result[i].score = r.score;
			result[i].level = r.level;
			break;
		}
	}
	for (int i = 0; i < 10; ++i)
	{
		out << result[i];
	}
}

HighscoresView::HighscoresView(Lokalization lang, Complexity c) : language(lang), complexity(c)
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
	Printer highscore(ConsoleColor::Black, ConsoleColor::LightGreen);
	Printer Exithighscore(ConsoleColor::Black, ConsoleColor::White);
	Printer BlackHole(ConsoleColor::Black, ConsoleColor::Black);

	language == Lokalization::En ? printTextOnTheCenter(consoleHeight - 5, "   | > Back < |   ", Exithighscore)
		: printTextOnTheCenter(consoleHeight - 5, "   | > Õ‡Á‡‰ < |   ", Exithighscore);
	setCursor(consoleWidth / 4 - 5, 4);
	language == Lokalization::En ? highscore << "NAME" : highscore << "≤Ã'ﬂ";
	setCursor(consoleWidth / 4 * 2 - 4, 4);
	language == Lokalization::En ? highscore << "COMPLEXITY" : highscore << "— À¿ƒÕ≤—“‹";
	setCursor((consoleWidth / 4) * 3, 4);
	language == Lokalization::En ? highscore << "SCORE" : highscore << "–¿’”ÕŒ ";
	for (int i = 0; i < 10; ++i)
	{
		setCursor(consoleWidth / 4 - 5, i + 5);
		cout << result[i].name;
		setCursor(consoleWidth / 4 * 2 - 4, i + 5);
		language == Lokalization::En ? cout << result[i].level : cout<<complexityUa(result[i].level);
		setCursor((consoleWidth / 4) * 3, i + 5);
		cout << result[i].score;
	}
	for (int i = 15; i < consoleHeight - 5; ++i)
	{
		setCursor(0, i);
		for (int j = 0; j < consoleWidth; ++j)
		{
			BlackHole << " ";
		}
	}
	setCursor(0, consoleHeight - 4);
	for (int i = 0; i < consoleWidth; ++i)
	{
		BlackHole << " ";
	}
}

View * HighscoresView::handle()
{
	View* nextView = this;
	switch (_getch())
	{
	case 8://Backspace
		nextView = new StartView(language, complexity);
	case 13://Enter
		nextView = new StartView(language, complexity);
	case 27://Esc
		nextView = new StartView(language, complexity);
	}
	return nextView;
}

string complexityUa(string word)
{
	if (word == "Easy")
	{
		return "ÀÂ„Í‡";
	}
	else if (word == "Medium")
	{
		return "—ÂÂ‰Ìˇ";
	}
	else
	{
		return "¬‡ÊÍ‡";
	}
}