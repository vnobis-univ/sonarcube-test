#include "ResultView.h"

Printer _pan(ConsoleColor::Black, ConsoleColor::LightGreen);
Printer _selectedPan(ConsoleColor::Black, ConsoleColor::White); 

ResultView::ResultView(Lokalization l, Complexity c, bool ia, short s): language(l), complexity(c), isAchieve(ia), score(s){}

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
			if (language == Lokalization::En)
			{
				setCursor(consoleWidth / 5 + 16 + counter, 8);
				cout << " ";
				setCursor(consoleWidth / 5 + 16 + counter, 8);
			}
			else
			{
				setCursor(consoleWidth / 5 + 18 + counter, 8);
				cout << " ";
				setCursor(consoleWidth / 5 + 18 + counter, 8);
			}
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

View * ResultView::handle()
{
	View* nextview = this;
	Result result[10];
	ifstream in("Highscore.txt");
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
				nextview = new HighscoresView(language, complexity);
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
		if (name.size() >= 12)
		{
			bool exit = false;
			language == Lokalization::En ? printTextOnTheCenter(consoleHeight - 3, "|> Continue <|", _selectedPan) : 
				printTextOnTheCenter(consoleHeight - 3, "|> Далі <|", _selectedPan);
			while (!exit)
			{

				switch (_getch())
				{
				case 13://Enter
					nextview = new HighscoresView(language, complexity);
					exit = true;
					break;
				}
			}
		}
		Result newResult;
		newResult.name = name;
		newResult.score = score;
		newResult.level = codeComplexityToStr(complexity);
		putInTable(newResult, result, out);
	}
	nextview = new HighscoresView(language, complexity);
	return nextview;
}

string ResultView::codeComplexityToStr(Complexity c)
{
	if (c == Complexity::Easy)
	{
		return "Easy";
	}
	else if (c == Complexity::Medium)
	{
		return "Medium";
	}
	else
	{
		return "Hard";
	}
}

void ResultView::draw()
{
	system("cls");
	if (language == Lokalization::En)
	{
		if (isAchieve)
		{
			printTextOnTheCenter(2, "Congratulations!!!", _pan);
			printTextOnTheCenter(4, "Your final score is " + to_string(score), _pan);
			printTextOnTheCenter(8, "Your name deserves to be in Records table!", _pan);
			setCursor(consoleWidth / 5, 6);
			cout << "Enter your name: ";
			drawHangedMan(true);
		}
		else
		{
			printTextOnTheCenter(6, "Your final score is " + to_string(score), _pan);
			printTextOnTheCenter(8, "It is not a big result:(", _pan);
			printTextOnTheCenter(consoleHeight - 3, "Press Enter to continue", _pan);
			drawHangedMan(false);
		}
	}
	else
	{
		if (isAchieve)
		{
			printTextOnTheCenter(4, "Вітаннячка!!!", _pan);
			printTextOnTheCenter(6, "Ваш фінальний рахунок: " + to_string(score), _pan);
			printTextOnTheCenter(10, "Ви заслуговуєте на повагу!", _pan);
			setCursor(consoleWidth / 5, 8);
			cout << "Введіть ваше ім'я: ";
		}
		else
		{
			printTextOnTheCenter(6, "Ваш фінальний рахунок: " + to_string(score), _pan);
			printTextOnTheCenter(8, "На жаль це невеликий результат:(", _pan);
			printTextOnTheCenter(consoleHeight - 3, "Натисніть Enter для продовження", _pan);
		}
	}
	Complexity compl = complexity;
}
