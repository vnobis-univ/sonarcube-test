#include <sstream>
#include <iostream>
#include <conio.h>
#include <fstream>
#include "ResultView.h"
#include "View.h"
#include "Console.h"
#include "Printer.h"
#include "HighScoreView.h"

ResultView::ResultView(bool i, int l, bool s) :isAchieve(i), score(l), isWin(s)  {}

string ResultView::getName()
{
	string name;
	char symbol = 0;
	short counter = 0;
	if (language == Language::ENGLISH)
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
	else if (language == Language::UKRAINIAN)
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
	if (language == Language::ENGLISH)
	{
		if (isAchieve && isWin)
		{
			printAtCenterOfLine(3, "You won!!!", defaultPrinter);
			printAtCenterOfLine(5, "Congratulations!!!", defaultPrinter);
			printAtCenterOfLine(7, "Your final score is " + to_string(score), defaultPrinter);
			printAtCenterOfLine(9, "You achived a high score", defaultPrinter);
			setCursoreAtPosition(40, 11);
			defaultPrinter << "Enter your name: ";
		}
		else if (isWin && !isAchieve)
		{
			printAtCenterOfLine(3, "You won!!!", defaultPrinter);
			printAtCenterOfLine(5, "Congratulations!!!", defaultPrinter);
			printAtCenterOfLine(7, "Your final score is " + to_string(score), defaultPrinter);
			printAtCenterOfLine(9, "It is not a big result:(", defaultPrinter);
			printAtCenterOfLine(11, "Press Enter to continue", defaultPrinter);
		}
		else
		{
			printAtCenterOfLine(3, "Computer won!", defaultPrinter);
			printAtCenterOfLine(5, "You can not be in high score table", defaultPrinter);
			printAtCenterOfLine(7, "Press Enter to continue", defaultPrinter);
		}
	}
	if (language == Language::UKRAINIAN)
	{
		if (isAchieve && isWin)
		{
			printAtCenterOfLine(2, "Ви перемогли!!!", defaultPrinter);
			printAtCenterOfLine(4, "Вiтання!!!", defaultPrinter);
			printAtCenterOfLine(6, "Ваш остаточний результат: " + to_string(score), defaultPrinter);
			printAtCenterOfLine(8, "Ви досягли високого результату", defaultPrinter);
			defaultPrinter << "\n";
			setCursoreAtPosition(10, 7);
			defaultPrinter << "Введiть ваше iм*я: ";
		}
		else if (isWin && !isAchieve)
		{
			printAtCenterOfLine(3, "Ви перемогли!!!", defaultPrinter);
			printAtCenterOfLine(5, "Ваш результат: " + to_string(score), defaultPrinter);
			printAtCenterOfLine(7, "Вiн надто малий. Спробуйте ще раз:(", defaultPrinter);
			printAtCenterOfLine(9, "Натиснiть ENTER щоб продовжити", defaultPrinter);
		}
		else
		{
			printAtCenterOfLine(5, "Ви програли!", defaultPrinter);
			printAtCenterOfLine(7, "Ви не можете бути в таблиці переможців", defaultPrinter);
			printAtCenterOfLine(9, "Натиснiть ENTER щоб продовжити", defaultPrinter);
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
	if (!isAchieve || !isWin)
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
		putInTable(newResult, result, out);
	}
	nextview = new HighscoreView;
	return nextview;
}
