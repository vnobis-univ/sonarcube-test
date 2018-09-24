#include "HighScoresView.h"

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
	ifstream file("Highscores.txt");
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

HighscoresView::HighscoresView()
{
	ifstream file("Highscores.txt");
	for (int i = 0; i < 10; ++i)
	{
		file >> result[i];
	}
}

void HighscoresView::draw()
{
	system("cls");
	Printer highscore(Color::Black, Color::LightGray);
	Printer Exithighscore(Color::Black, Color::White);
	setCursor(consoleWidth / 4 - 5, 4);
	highscore << "Name";
	setCursor(consoleWidth / 4 * 2 - 4, 4);
	setCursor((consoleWidth / 4) * 3, 4);
	highscore << "Score";
	for (int i = 0; i < 10; ++i)
	{
		setCursor(consoleWidth / 4 - 5, i + 5);
		cout << result[i].name;
		setCursor(consoleWidth / 4 * 2 - 4, i + 5);
		cout << result[i].level;
		setCursor((consoleWidth / 4) * 3, i + 5);
		cout << result[i].score;
	}
	printInCenter(consoleHeight - 5, "   | > Back < |   ", Exithighscore);
}

View * HighscoresView::handle()
{
	View* nextView = this;
	switch (_getch())
	{
	case 8://Backspace
		nextView = new StartView();
	case 13://Enter
		nextView = new StartView();
	case 27://Esc
		nextView = new StartView();
	}
	return nextView;
}