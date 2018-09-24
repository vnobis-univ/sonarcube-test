#include "ResultView.h"

Printer nonSelected(Color::Black, Color::LightGray);
Printer selected(Color::Black, Color::White);

ResultView::ResultView(bool ia, short s) : isAchieve(ia), score(s){}

string ResultView::getName()
{
	string name;
	char symbol = 0;
	short counter = 0;
	while (counter < 12 && symbol != 13)
	{
		symbol = _getch();
		if (symbol == 8 && counter > 0)//Backspace
		{
			name.pop_back();
			
				setCursor(consoleWidth / 5 + 16 + counter, 8);
				cout << " ";
				setCursor(consoleWidth / 5 + 16 + counter, 8);
			
			if (counter != 0)
			{
				--counter;
			}
		}
		if (symbol == 13 && name.size() == 0)
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

View * ResultView::handle()
{
	View* nextview = this;
	Result result[10];
	ifstream in("Highscores.txt");
	for (int i = 0; i < 10; ++i)
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
				nextview = new HighscoresView();
				return nextview;
			}
		}
	}
	else
	{
		ofstream out("Highscores.txt");
		showCursor(true);
		string name = getName();
		showCursor(false);
		if (name.size() >= 12)
		{
			bool exit = false;
			printInCenter(14, "|> Continue <|", selected);
			while (!exit)
			{

				switch (_getch())
				{
				case 13://Enter
					nextview = new HighscoresView();
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
	nextview = new HighscoresView();
	return nextview;
}



void ResultView::draw()
{
	system("cls");

	if (isAchieve)
	{
		printInCenter(4, "Good job", nonSelected);
		printInCenter(6, "Your final score is " + to_string(score), nonSelected);
		printInCenter(10, "Your name deserves to be in Records table!", nonSelected);
		setCursor(consoleWidth / 5, 8);
		cout << "Enter your name: ";
	}
	else
	{
		printInCenter(6, "Your final score is " + to_string(score), nonSelected);
		printInCenter(8, "It is not a big result:(", nonSelected);
		printInCenter(consoleHeight - 3, "Press Enter to continue", nonSelected);
	}


}