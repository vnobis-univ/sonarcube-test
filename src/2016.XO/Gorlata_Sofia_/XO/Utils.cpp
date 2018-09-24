#include "Utils.h"
#include "Printer.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Printer whiteOnBlue(Color::LightWhite, Color::LightBlue);
Printer darkBlueOnBlue(Color::Blue, Color::LightBlue);
Printer purOnBlue(Color::LightPurple, Color::LightBlue);
Printer redOnBlue(Color::Red, Color::LightBlue);
Printer whiteOnBlack(Color::LightWhite, Color::Black);
Printer blueOnBlue(Color::Blue, Color::Blue);


void setConsoleSize(int x, int y)
{
	HWND hwnd = GetConsoleWindow();
	MoveWindow(hwnd, 500, 50, x, y, TRUE);
}

void moveCursorTo(int x, int y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(hConsole, position);
}
void showConsoleCursor(bool showFlag)
{
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}
