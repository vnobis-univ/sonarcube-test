#include "ResultView.h"

string getName();

Printer pen(Color::LightGray, Color::Blue);

ResultView::ResultView(bool is,short sc):isHere(is),score(sc){}

string getName()
{
	string name;
	char num = 0;
	short counter = 0;
	while (counter < 15 && num != 13)
	{
		num = _getch();
		if (num == 8 && counter>0)
		{
			name.pop_back();
			setCursor(26 + counter, 7);
			cout << " ";
			setCursor(26 + counter, 7);
			--counter;
		}
		else if (num == 13 && name.size() == 0)
		{
			name = "Unknown";
		}
		else if (num != 13)
		{
			name += num;
			cout << num;
			++counter;
		}
	}
	return name;
}

void ResultView::draw()
{
	system("cls");
	if (isHere)
	{
		printInCenter(4, "You made a new highscore!", pen);
		setCursor(10, 6);
		cout << "Please, enter your name: ";
	}
	else
	{
		printInCenter(5, "You scored " + to_string(score), pen);
		printInCenter(6, "Press Enter to continue", pen);
	}
}

View *ResultView::handle()
{
	View *nextView = this;
	Result result[10];
	ifstream in("Highscores.txt");

	for (size_t i = 0; i < 10; ++i)
	{
		in >> result[i];
	}

	if (!isHere)
	{
		bool exit = false;
		while (!exit)
		{
			switch (_getch())
			{
			case 13:
				nextView = new HighScoresView;
				return nextView;
			}
		}
	}
	else
	{
		ofstream out("Highscores.txt");
		showCursor(true);
		string name = getName();
		showCursor(false);
		if (name.size() >= 10)
		{
			bool exit = false;
			while (!exit)
			{
				switch (_getch())
				{
				case 13:
					nextView = new HighScoresView;
					exit = true;
					break;
				}
			}
		}
		Result newResult;
		newResult.name = name;
		newResult.score = score;
		writeIn(newResult, result, out);
	}
	nextView = new HighScoresView;
	return nextView;
}