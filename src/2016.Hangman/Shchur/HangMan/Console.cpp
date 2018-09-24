#include "Console.h"

int consoleWidth;
int consoleHeight;

HWND handlew = FindWindow("ConsoleWindowClass", NULL);
HDC dc = GetDC(handlew);

HPEN greenPan = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
HBRUSH PanBlack = CreateSolidBrush(RGB(0, 0, 0));

void drawFrame(HPEN pen1, HBRUSH pen2, int x1, int y1, int x2, int y2)
{
	SelectObject(dc, pen1);
	SelectObject(dc, pen2);
	Rectangle(dc, x1, y1, x2, y2);
}

void drawHangedMan(bool victory)
{
	short start = consoleWidth * 15 / 3;
	SelectObject(dc, greenPan);
	SelectObject(dc, PanBlack); 
	MoveToEx(dc, start, 630, NULL);
	LineTo(dc, start, 240);
	MoveToEx(dc, start - 50, 630, NULL);
	LineTo(dc, start + 50, 630);
	MoveToEx(dc, start, 240, NULL);
	LineTo(dc, start + 230, 240);
	LineTo(dc, start + 230, 300);
	Ellipse(dc, start + 200, 300, start + 260, 360);
	MoveToEx(dc, start + 230, 360, NULL);
	LineTo(dc, start + 230, 460);
	MoveToEx(dc, start + 230, 400, NULL);
	LineTo(dc, start + 170, 440);
	MoveToEx(dc, start + 230, 400, NULL);
	LineTo(dc, start + 290, 440);
	MoveToEx(dc, start + 230, 460, NULL);
	LineTo(dc, start + 190, 570);
	MoveToEx(dc, start + 230, 460, NULL);
	LineTo(dc, start + 270, 570);
	//UnhappyDeadMan
	if (!victory)
	{
		MoveToEx(dc, start + 215, 315, NULL);
		LineTo(dc, start + 225, 325);
		MoveToEx(dc, start + 215, 325, NULL);
		LineTo(dc, start + 225, 315);
		MoveToEx(dc, start + 235, 315, NULL);
		LineTo(dc, start + 245, 325);
		MoveToEx(dc, start + 235, 325, NULL);
		LineTo(dc, start + 245, 315);
		MoveToEx(dc, start + 215, 345, NULL);
		LineTo(dc, start + 245, 345);

	}
	//HappyDeadMan
	else
	{
		Ellipse(dc, start + 217, 317, start + 223, 323);
		Ellipse(dc, start + 237, 317, start + 243, 323);
		//Smile
		MoveToEx(dc, start + 215, 345, NULL);
		LineTo(dc, start + 245, 345);
		MoveToEx(dc, start + 215, 345, NULL);
		LineTo(dc, start + 212, 344);
		LineTo(dc, start + 210, 343);
		LineTo(dc, start + 211, 342);
		LineTo(dc, start + 210, 340);
		LineTo(dc, start + 209, 338);
		MoveToEx(dc, start + 245, 345, NULL);
		LineTo(dc, start + 248, 344);
		LineTo(dc, start + 250, 343);
		LineTo(dc, start + 251, 342);
		LineTo(dc, start + 252, 340);
		LineTo(dc, start + 252, 338);
	}
}
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

void dontAllowToChangeSize()
{
	HMENU hm;
	HWND handle = FindWindow("ConsoleWindowClass", NULL);
	hm = GetSystemMenu(handle, FALSE);
	RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
	RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
	DrawMenuBar(handle);
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

void enableUkrainianLang()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}
