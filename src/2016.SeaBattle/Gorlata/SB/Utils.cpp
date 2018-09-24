#include "Utils.h"
#include "windows.h"
#include "Printer.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int consoleWidth = 80;

extern Printer blueOnBlack(Color::Blue, Color::Black);
extern Printer lightBlueOnBlack(Color::LightBlue, Color::Black);
extern Printer lightAquaOnBlack(Color::LightAqua, Color::Black);
extern Printer greenOnBlack(Color::LightGreen, Color::Black);
extern Printer lightPurpleOnBlack(Color::LightPurple, Color::Black);
extern Printer purleOnBlack(Color::Purple);


extern HDC hdc = GetDC(GetConsoleWindow());
extern HPEN redPen(CreatePen(PS_SOLID, 1, RGB(242, 134, 109)));
extern HPEN bluePen(CreatePen(PS_SOLID, 1, RGB(87, 198, 235)));
extern HPEN brightRed(CreatePen(PS_SOLID, 1, RGB(255, 0, 60)));
extern HPEN blackPen(CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
extern HPEN greenPen(CreatePen(PS_SOLID, 1, RGB(32, 240, 2)));
extern HPEN testPen(CreatePen(PS_SOLID, 1, RGB(219,9, 43)));

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
