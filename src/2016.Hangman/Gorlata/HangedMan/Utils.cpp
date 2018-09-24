#include "Utils.h"
#include "Printer.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


extern Printer lightAquaOnBlack(Color::LightAqua, Color::Black);
extern Printer greenOnBlack(Color::LightGreen, Color::Black);
extern Printer lightPurpleOnBlack(Color::LightPurple, Color:: Black);
extern Printer purleOnBlack(Color:: Purple);



void setConsoleSize(int x, int y)
{
	HWND hwnd = GetConsoleWindow();
	MoveWindow(hwnd, 500, 50, x, y, TRUE);
}

void showConsoleCursor(bool showFlag)
{
	CONSOLE_CURSOR_INFO   cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void moveCursorTo(int x, int y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(hConsole, position);
}
