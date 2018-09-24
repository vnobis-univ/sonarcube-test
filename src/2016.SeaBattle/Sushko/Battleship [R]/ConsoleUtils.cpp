#include "ConsoleUtils.h"
#include "ExternUtils.h"
#include <conio.h>
#include <iostream>

using std::string;

void setConsoleSize(int width, int height)
{
	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Right = width - 1;
	r.Bottom = height - 1;
	SetConsoleWindowInfo(hConsole, TRUE, &r);

	COORD c;
	c.X = width;
	c.Y = height;
	SetConsoleScreenBufferSize(hConsole, c);
}

void removeScrollbar()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(hConsole, new_size);
}

void disableResizing()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MINIMIZEBOX) & ~(WS_MAXIMIZEBOX);
	SetWindowLong(consoleWindow, GWL_STYLE, style);

	HWND handle = FindWindow("ConsoleWindowClass", NULL);
	HMENU hm = GetSystemMenu(handle, FALSE);
	RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
	RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
	DrawMenuBar(handle);
}

void moveTo(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(hConsole, pos);
}

void showCursor(bool showFlag)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void drawLine(COORD from, COORD to)
{
	MoveToEx(hdc, from.X, from.Y, NULL);
	LineTo(hdc, to.X, to.Y);
}

string consoleInput(COORD coord, int maxLength, char firstValid, char lastValid)
{
	string input("");
	white.setColor();
	moveTo(coord.X, coord.Y);
	
	int count = 0;

	showCursor(true);
	bool entered = false;
	while (!entered) {

		char key = _getch();
		
		if (count < maxLength && int(key) != 8 && int(key) != 13
			&& key >= firstValid && key <= lastValid) {
			input += key;
			count++;
		}

		if ((int)key == 8 && input.length() > 0) {
			input.pop_back();
			moveTo(coord.X, coord.Y), white.print(input + " ");
			count--;
		}

		if (int(key) == 13 && input.length() >0) {
			entered = true;
		}
		
	
		moveTo(coord.X, coord.Y), white.print(input);
	}

	showCursor(false);
	return input;
}

void setConsoleFont()
{
	COORD dwFontSize;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info{ sizeof(CONSOLE_FONT_INFOEX) };
	if (!GetCurrentConsoleFontEx(output, false, &info))
		return;
	dwFontSize.X = 8;
	dwFontSize.Y = 16;
	info.FontFamily = FF_DONTCARE;
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, L"Lucida Console");
	info.dwFontSize = dwFontSize;
	SetCurrentConsoleFontEx(output, false, &info);
}

void enableUkrainian()
{
	setlocale(LC_CTYPE, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

bool confirmExit(string msg) {

	redP.midLinePrint(24, string(msg.length(), ' '));
	redP.midLinePrint(25, msg);
	redP.midLinePrint(26, string(msg.length(), ' '));

	if (_getwch() == 27) {
		return true;
	}
	else {
		aqua.midLinePrint(24, string(msg.length(), ' '));
		aqua.midLinePrint(25, msg);
		aqua.midLinePrint(26, string(msg.length(), ' '));
		return false;
	}
}