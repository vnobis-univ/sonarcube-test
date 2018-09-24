#pragma once
#include <conio.h>
#include <string>
#include "View.h"
#include "FieldView.h"
#include "HighscoreView.h"
#include "ForConsole.h"
#include "Printer.h"
#include "Color.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_SPACE 32



enum class Options
{
	START,
	HIGHSCORE,
	EXIT
};
class StartView :public View
{
	View* nextView = this;

	int lineIdentifier(string opt)
	{
		int line = 14;
		if(opt == "START") line = 14;
		else if (opt == "HIGHSCORE") line = 18;
		else if (opt == "EXIT") line = 22;
		return line;
	}
	void cleaner(Printer p)
	{
		Printer frame(Color::LIGHT_GREEN, Color::AQUA);
		setCursorPosition(0, 14);
		string bodyLine = string(consoleWidth - 2, ' ');
		for (unsigned i = 0; i < 10; ++i)
		{
			frame << " ";
			p << bodyLine;
			frame << " ";
		}
	}
	void draw(Options oSelected)
	{
		cleaner(lGreenOnBlue);
		setCursorPosition(0, 0);
		for (unsigned i = 0; i < 3; ++i)
		{
			Options oCurrent = static_cast<Options>(i);
			if (oSelected == oCurrent)
			{
				printAtLineCenter(lineIdentifier(optionToString(oSelected)), "*" + optionToString(oSelected) + "*", lGreenOnBlue);
				/*lGreenOnBlue << "*" + optionToString(oSelected) + "*";
				cout << endl << endl << endl << endl;*/
			}
			else
			{
				printAtLineCenter(lineIdentifier(optionToString(oCurrent)), optionToString(oCurrent), lGreenOnBlue);
				/*lGreenOnBlue << optionToString(oCurrent);
				cout << endl << endl << endl << endl;*/
			}
		}
	}
	string optionToString(Options oObj)
	{
		switch (oObj)
		{
		case Options::START:
			return "START";
		case Options::HIGHSCORE:
			return "HIGHSCORE";
		case Options::EXIT:
			return "EXIT";
		default:
			return "ERROR!";
		}
	}
public:
	StartView(){}
	View* handle()
	{
		clean();
		View::draw();
		View* nextView = this;
		int nEnteredKey = _getch();
		int nSelected = 0; //by default START
		draw(static_cast<Options>(nSelected));
		draw(static_cast<Options>(nSelected));
		while (nEnteredKey != KEY_ENTER)
		{
			nEnteredKey = _getch();
			if (nEnteredKey == KEY_DOWN)
			{
				nSelected = (nSelected + 1) % 3;
				draw(static_cast<Options>(nSelected));
			}
			if (nEnteredKey == KEY_UP)
			{
				nSelected = (nSelected - 1) % 3;
				draw(static_cast<Options>(nSelected));
			}
		}
		if (nSelected == 0)
		{
			nextView = NULL;
			showCursor(true);
			nextView = new Field();
			nextView->handle();
		}
		else if (nSelected == 1)
		{
			nextView = NULL;
			nextView = new HighscoreView();
			nextView->handle();
		}
		else
		{
			printAtLineCenter(26, "You've decided to quit the game, press any key\n", lGreenOnBlue);
			_getch();
		}
		return nextView;
	}


};