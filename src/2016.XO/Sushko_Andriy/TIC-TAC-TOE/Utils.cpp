#include "Utils.h"
#include "View.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HDC hdc = GetDC(GetConsoleWindow());

Printer whiteOnBlue(Color::light_white, Color::blue);
Printer purpleOnBlue(Color::light_purple, Color::blue);
Printer blue(Color::light_blue);
Printer white(Color::light_white);
Printer aquaOnBlue(Color::light_aqua, Color::blue);
Printer lightRed(Color::light_red);
Printer redOnBlue(Color::light_red, Color::blue);
HPEN bluePen(CreatePen(PS_SOLID, 2, RGB(5, 5, 180)));
HPEN redPen(CreatePen(PS_SOLID, 2, RGB(255, 0, 0)));
HPEN whitePen(CreatePen(PS_SOLID, 2, RGB(215, 200, 255)));

void moveCursorTo(int x, int y)
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

void clean()
{
	system("cls");
}


void systemPauseInLine(int x, int y)
{
	moveCursorTo(x, y);
	system("PAUSE");
}

