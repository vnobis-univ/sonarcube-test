#include <sstream>
#include <iostream>
#include <conio.h>
#include <fstream>
#include "ResultView.h"
#include "View.h"
#include "Console.h"
#include "Printer.h"
#include "HighScoreView.h"
#include "Complexity.h"

ResultView::ResultView(bool i, short s, int l) :isAchieve(i), score(s), life(l) {}

string ResultView::getName()
{
	string name;
	char symbol = 0;
	short counter = 0;
	if (language == "Eng")
	{
		while (counter < 15 && symbol != 13)
		{
			symbol = _getch();
			if (symbol == 8 && counter > 0)//Backspace
			{
				name.erase(name.size() - 1, 1);
				setCursoreAtPosition(26 + counter + 1, 7);
				counter--;
				cout << " ";
			}
			else if (symbol == 13 && name.size() == 0)//Enter
			{
				name = "Unknown";
			}
			else if (symbol != 13)
			{
				name += symbol;
				defaultPrinter.print(symbol);
				++counter;
			}
		}
	}
	else if (language == "Ukr")
	{
		setlocale(LC_ALL, "C");
		while (counter < 15 && symbol != 13)
		{
			symbol = _getch();
			if (symbol == 8 && counter > 0)//Backspace
			{
				name.erase(name.size() - 1, 1);
				setCursoreAtPosition(26 + counter + 1, 7);
				counter--;
				cout << " ";
			}
			else if (symbol == 13 && name.size() == 0)//Enter
			{
				setlocale(LC_ALL, "Ukrainian");
				name = "Невiдомий";
			}
			else if (symbol != 13)
			{
				name += symbol;
				defaultPrinter.print(symbol);
				++counter;
			}
		}
	}
	return name;
}
void ResultView::draw()
{
	View::draw();
	if (language == "Eng")
	{
		if (isAchieve)
		{
			printAtCenterOfLine(4, "Congratulations!!!", defaultPrinter);
			printAtCenterOfLine(5, "Your final score is " + to_string(score), defaultPrinter);
			printAtCenterOfLine(6, "Your achived a high score", defaultPrinter);
			setCursoreAtPosition(10, 7);
			defaultPrinter << "Enter your name: ";
		}
		else
		{
			printAtCenterOfLine(5, "Your final score is " + to_string(score), defaultPrinter);
			printAtCenterOfLine(6, "It is not a big result:(", defaultPrinter);
			printAtCenterOfLine(8, "Press Enter to continue", defaultPrinter);
		}
	}
	if (language == "Ukr")
	{
		if (isAchieve)
		{
			printAtCenterOfLine(4, "Вiтання!!!", defaultPrinter);
			printAtCenterOfLine(5, "Ваш остаточний результат: " + to_string(score), defaultPrinter);
			printAtCenterOfLine(6, "Ви досягли високого результату", defaultPrinter);
			defaultPrinter << "\n";
			setCursoreAtPosition(10, 7); 
			defaultPrinter << "Введiть ваше iм*я: ";
		}
		else
		{
			printAtCenterOfLine(5, "Ваш результат: " + to_string(score), defaultPrinter);
			printAtCenterOfLine(6, "Вiн надто малий. Спробуйте ще раз:(", defaultPrinter);
			printAtCenterOfLine(8, "Натиснiть ENTER щоб продовжити", defaultPrinter);
		}
	}
}
View* ResultView::handle()
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
				nextview = new HighscoreView;
				return nextview;
			}
		}
	}
	else
	{
		ofstream out("Highscore.txt");
		showConsoleCursor(true);
		string name = getName();
		showConsoleCursor(false);
		if (name.size() >= 15)
		{
			bool exit = false;
			while (!exit)
			{
				switch (_getch())
				{
				case 13://Enter
					nextview = new HighscoreView;
					exit = true;
					break;
				}
			}
		}
		Result newResult;
		newResult.name = name;
		newResult.score = score;
		newResult.life = life;
		newResult.complexity1 = parseComplexityToString(complexity);
		putInTable(newResult, result, out);
	}
	nextview = new HighscoreView;
	return nextview;
}
