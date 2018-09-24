#pragma once

#include <conio.h>
#include "ConsoleProperties.h"

using namespace std;

Printer headline(Color::YELLOW, Color::BLUE);
Printer menuPassive(Color::YELLOW, Color::BROWN);
Printer menuActive(Color::YELLOW, Color::RED);
Printer techData(Color::BLACK, Color::WHITE);
Printer stats(Color::WHITE, Color::LIGHT_BLUE);

HWND hwnd = GetConsoleWindow();
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HDC hdc = GetDC(hwnd);
RECT rect;
COORD cursor;

const int FONT_WIDTH = 11;
const int FONT_HEIGHT = 18;
const int CONSOLE_WIDTH = 80;
const int CONSOLE_HEIGHT = 35;

Options options;

MenuItem::MenuItem(string _text, int _x, int _y) :
	text(_text),
	chosen(false),
	x(_x),
	y(_y)

{
}

void setConsoleProperties()
{
	scrollOff(CONSOLE_WIDTH, CONSOLE_HEIGHT);

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// setting text font
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = 18;
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(hConsole, NULL, &info);

	// making cursor invisible
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);

	// making edges immutable
	HMENU hm = GetSystemMenu(GetConsoleWindow(), FALSE);
	RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
	RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
	DrawMenuBar(GetConsoleWindow());

	// configuring buffer and window
	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Right = CONSOLE_WIDTH - 1;
	r.Bottom = CONSOLE_HEIGHT - 1;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &r);

	COORD c;
	c.X = CONSOLE_WIDTH;
	c.Y = CONSOLE_HEIGHT;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void scrollOff(int width, int height)
{
	string cols = to_string(width);
	string lines = to_string(height);
	string str = "mode con cols=" + cols + " lines=" + lines;
	const char* sch = str.c_str();
	system(sch);
}

void setCursorAt(int x, int y)
{
	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}

void printAtCenter(string st, const Printer& p)
{
	int size = st.size();
	int x_pos = (CONSOLE_WIDTH - size) / 2 + (CONSOLE_WIDTH - size) % 2;
	setCursorAt(x_pos, cursor.Y);
	p.print(st);
}

string getUserTextInput(int len)  // uses _getch() to get user's string input
{
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_RED); // sets font of user's inut

	bool properlyInserted = false;
	int numOfFilled = 0;
	string name;
	char c;
	int startCursorX = cursor.X;

	for (size_t i = 0; i < len; ++i) // draws the line of length len to be filled by user
	{
		cout << " ";
	}

	cursor.X = startCursorX;
	setCursorAt(cursor.X, cursor.Y);

	while (!properlyInserted)
	{
		c = _getch();

		if (c == ' ')
		{
			if (name != "" && numOfFilled < len) // you can enter ' ' only when the name is already not empty
			{
				name += ' ';
				cout << " ";
				cursor.X++;
				numOfFilled++;
			}
		}
		else if (c == VK_RETURN) // you can't finish entering name if it is still empty
		{
			if (name != "")
			{
				cursor.X = startCursorX;
				setCursorAt(cursor.X, cursor.Y);

				for (size_t i = 0; i < len; ++i) // draws empty row when the name has already been inputted
				{
					cout << " ";
				}

				properlyInserted = true; // finish the loop
			}
		}
		else if (c == VK_BACK) // deletes one character if backspace has been pressed
		{
			if (name != "")
			{
				name.erase(name.size() - 1, 1);
				numOfFilled--;
				cursor.X--;

				int beforeErase = cursor.X; // remembers cursor's current position 
				setCursorAt(cursor.X, cursor.Y);

				for (size_t i = numOfFilled; i < len; ++i) // draws empty symbols till the end of the row
															   // to avoid possible collisions
				{
					cout << " ";
				}

				cursor.X = beforeErase; // returns cursor to its former position
				setCursorAt(cursor.X, cursor.Y);
			}
		}
		else
		{
			if (numOfFilled < len) // adds one symbol to name
			{
				numOfFilled++;
				cursor.X++;
				name += c;
				cout << c;
			}
		}
	}

	cursor.X = startCursorX; // retuns cursor to its start position after the input was achieved
	setCursorAt(cursor.X, cursor.Y);

	return name;
}