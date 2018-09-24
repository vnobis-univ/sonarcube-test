#pragma once

#include <sstream>
#include <string>
#include "Printer.h"
#include "Options.h"

using namespace std;

struct MenuItem
{
	string text;
	bool chosen;
	int x;
	int y;

	MenuItem(string = "", int = 0, int = 0);
};

void setConsoleProperties();

void setCursorAt(int, int);

void printAtCenter(string st, const Printer& p);

string getUserTextInput(int);

template<class T>
string toString(const T& t)
{
	ostringstream oStream;
	oStream << t;
	return oStream.str();
}

void scrollOff(int width, int height);

extern Printer headline;
extern Printer menuActive;
extern Printer menuPassive;
extern Printer finish;
extern Printer techData;
extern Printer stats;
extern Printer letterPrint;
extern Printer rightLetterPrint;
extern Printer wrongLetterPrint;

extern HWND hwnd;
extern HANDLE hConsole;
extern HDC hdc;
extern RECT rect;
extern COORD cursor;
extern POINT op;

extern const int FONT_WIDTH;
extern const int FONT_HEIGHT;
extern const int CONSOLE_WIDTH;
extern const int CONSOLE_HEIGHT;

extern Options options;