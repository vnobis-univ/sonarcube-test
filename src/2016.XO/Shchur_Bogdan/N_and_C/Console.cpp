#include <Windows.h>
#include <string>
#include "Printer.h"
#define _CRT_SECURE_NO_WARNINGS wcsncpy_s

using namespace std;

HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
int consoleWidth;
int consoleHeight;

void setConsoleSize(int width, int height)
{
	consoleWidth = width;
	consoleHeight = height;
	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Bottom = height - 1;
	r.Right = width - 1;
	SetConsoleWindowInfo(hconsole, TRUE, &r);
	COORD c;
	c.X = width;
	c.Y = height;
	SetConsoleScreenBufferSize(hconsole, c);
}
void setCursor(short x, short y)
{
	COORD c = { x , y };
	SetConsoleCursorPosition(hconsole, c);
}
void printTextOnTheCenter(int line, string text, Printer p)
{
	int size = text.size();
	int x = (consoleWidth - size) / 2 + (consoleWidth - size) % 2;
	setCursor(x, line);
	p << text;
}
void showCursor(bool sth)
{
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(hconsole, &info);
	info.bVisible = sth;
	SetConsoleCursorInfo(hconsole, &info);
}
string changeFontSize(string tex, short size)
{
	CONSOLE_FONT_INFOEX info;
	GetCurrentConsoleFontEx(hconsole, TRUE, &info);
	//wcsncpy(L"Arial Cyr", info.FaceName, LF_FACESIZE);
	short temp = info.dwFontSize.X;
	info.dwFontSize.X = size;
	SetCurrentConsoleFontEx(hconsole, TRUE, &info);
	return tex;
}
void dontAllowToChangeSize()
{
	HMENU hm;
	HWND handle = FindWindow("ConsoleWindowClass", NULL);
	hm = GetSystemMenu(handle, FALSE);
	RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
	RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
	DrawMenuBar(handle);
}