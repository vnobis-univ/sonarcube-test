#include "ConsoleUtils.h"
#include <conio.h>
const int consoleWidth = 115;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HDC hdc = GetDC(GetConsoleWindow());

Printer white(Color::light_white, Color::purple);

Printer yellow(Color::light_yellow, Color::purple);

Printer lPurpleOnPurple(Color::light_purple, Color::purple);

Printer purple(Color::purple, Color::purple);

Printer red(Color::light_red, Color::black);

Printer lightRed(Color::light_purple, Color::purple);

HPEN whitePen(CreatePen(PS_SOLID, 1, RGB(255, 255, 255)));
HPEN purplePen(CreatePen(PS_SOLID, 1, RGB(128, 0, 128)));

void setConsoleSize(int width, int height)
{
	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Right = width - 1;
	r.Bottom = height - 1;
	SetConsoleWindowInfo(hConsole, TRUE, &r);

	COORD c;
	c.X = 0;
	c.Y = 0;
	SetConsoleScreenBufferSize(hConsole, c);
}

void restrictResize()
{
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

void enableUkrainian()
{
	setlocale(LC_CTYPE, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

void systemPauseAt(int x, int y, std::string message)
{
	moveTo(x, y);
	white.Print(message);
	_getch();
}

bool confirmExit(string msg) {

	red.MidLinePrint(9, string(msg.length(), ' '));
	red.MidLinePrint(10, msg);
	red.MidLinePrint(11, string(msg.length(), ' '));

	if (_getwch() == 27) {
		return true;
	}
	else {
		purple.MidLinePrint(9, string(msg.length(), ' '));
		purple.MidLinePrint(10, msg);
		purple.MidLinePrint(11, string(msg.length(), ' '));
		return false;
	}
}