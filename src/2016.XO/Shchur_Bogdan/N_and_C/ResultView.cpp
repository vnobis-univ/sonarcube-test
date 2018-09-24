#include "ResultView.h"

string getName();

Printer pan(ConsoleColor::LightGray, ConsoleColor::Red);
ResultView::ResultView(bool i, short s):isAchieve(i), score(s){}

string getName()
{
	string name;

	char symbol = 0;
	short counter = 0;
	while (counter < 15 && symbol != 13)
	{
		symbol = _getch();
		if (symbol == 8 && counter > 0)//Backspace
		{
			name.pop_back();
			setCursor(26 + counter, 7);
			cout << " ";
			setCursor(26 + counter, 7);
			if (counter != 0)
			{
				--counter;
			}
		}
		if (symbol == 13 && name.size() == 0)//Enter
		{
			name = "Stranger";
		}
		if (symbol != 13 && symbol != 8)
		{
			name += symbol;
			cout << symbol;
			++counter;
		}
	}
	return name;
}
void ResultView::draw()
{
	system("cls");
	if (isAchieve)
	{
		printTextOnTheCenter(4, "Congratulations!!!", pan);
		printTextOnTheCenter(5, "Your final score is " + to_string(score), pan);
		printTextOnTheCenter(6, "Your name deserves to be in Table of Heroes!", pan);
		setCursor(10, 7);
		cout << "Enter your name: ";
	}
	else
	{
		printTextOnTheCenter(5, "Your final score is " + to_string(score), pan);
		printTextOnTheCenter(6, "It is not a big result:(", pan);
		printTextOnTheCenter(8, "Press Enter to continue", pan);
	}
}
View* ResultView::handle()
{
	View* nextview = this;
	Result result[5];
	ifstream in("Highscore.txt");
	for (int i = 0; i < 5; ++i)
	{
		in >> result[i];
	}
	if (!isAchieve)
	{
		bool exit = false;
		while (!exit)
		{
			switch (_getch())
			{
			case 13://Enter
				nextview = new HighscoresView;
				return nextview;
			}
		}
	}
	else
	{
		ofstream out("Highscore.txt");
		showCursor(true);
		string name = getName();
		showCursor(false);
		if (name.size() >= 15)
		{
			bool exit = false;
			while (!exit)
			{
				switch (_getch())
				{
				case 13://Enter
					nextview = new HighscoresView;
					exit = true;
					break;
				}
			}
		}
		Result newResult;
		newResult.name = name;
		newResult.score = score;
		putInTable(newResult, result, out);
	}
	nextview = new HighscoresView;
	return nextview;
}
