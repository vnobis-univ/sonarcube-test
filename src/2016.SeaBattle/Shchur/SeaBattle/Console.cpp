#include "Console.h"

int consoleWidth;
int consoleHeight;

HWND handlew = FindWindow("ConsoleWindowClass", NULL);
HDC dc = GetDC(handlew);

HPEN redPen = CreatePen(PS_SOLID, 3, RGB(151, 0, 0));
HPEN bluePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 128));
HPEN bluePenSmaller = CreatePen(PS_SOLID, 2, RGB(0, 0, 128));
HPEN brownPen = CreatePen(PS_SOLID, 3, RGB(128, 128, 0));
HPEN redPenSmaller = CreatePen(PS_SOLID, 2, RGB(151, 0, 0));
HPEN blackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

HBRUSH PenWhite = CreateSolidBrush(RGB(255, 255, 255));
HBRUSH PenBlue = CreateSolidBrush(RGB(90, 126, 143));
HBRUSH PenLightBlue = CreateSolidBrush(RGB(152, 188, 205));
HBRUSH PenDarkerWhite = CreateSolidBrush(RGB(243, 243, 243));
HBRUSH PenBlack = CreateSolidBrush(RGB(0, 0, 0));

int landslide = 28;

void drawFrame(HPEN pen1, HBRUSH pen2, int x1, int y1, int x2, int y2)
{
	SelectObject(dc, pen1);
	SelectObject(dc, pen2);
	Rectangle(dc, x1, y1, x2, y2);
}

void drawNet(int x1, int y1)
{
	const int numOfLines = 10;
	SelectObject(dc, bluePen);
	SelectObject(dc, PenWhite);
	for (int i = 0; i <= numOfLines; ++i)
	{
		int position_x = x1 + i * landslide;
		MoveToEx(dc, position_x, y1, NULL);
		LineTo(dc, position_x, y1 + landslide * numOfLines);
	}
	for (int i = 0; i <= numOfLines; ++i)
	{
		int position_y = y1 + i * landslide;
		MoveToEx(dc, x1, position_y, NULL);
		LineTo(dc, x1 + landslide * numOfLines, position_y);
	}
}

void drawCross(bool isSel, int x, int y)
{
	SelectObject(dc, bluePenSmaller);
	isSel ? SelectObject(dc, PenLightBlue) : SelectObject(dc, PenBlue);
	Rectangle(dc, x, y, x + landslide, y + landslide);
	SelectObject(dc, redPen);
	SelectObject(dc, PenBlue);
	MoveToEx(dc, x, y, NULL);
	LineTo(dc, x + landslide, y + landslide);
	MoveToEx(dc, x, y + landslide, NULL);
	LineTo(dc, x + landslide, y);
}

void drawPoint(bool isSel, int x, int y)
{
	SelectObject(dc, bluePenSmaller);
	isSel ? SelectObject(dc, PenLightBlue) : SelectObject(dc, PenWhite);
	Rectangle(dc, x, y, x + landslide, y + landslide); 
	SelectObject(dc, blackPen);
	SelectObject(dc, PenBlack);
	Ellipse(dc, x + landslide / 3 + 1, y + landslide / 3 + 1, x + landslide * 2 / 3, y + landslide * 2 / 3);
}

void drawRectangle(HPEN pen, HBRUSH brush, int x, int y)
{
	SelectObject(dc, pen);
	SelectObject(dc, brush);
	Rectangle(dc, x, y, x + landslide, y + landslide);
}

void drawNumbers(int x, int y)
{
	SelectObject(dc, brownPen);
	SelectObject(dc, PenWhite);
	//1
	MoveToEx(dc, x - 20, y + 6, NULL);
	LineTo(dc, x - 20, y + 21);
	//2
	MoveToEx(dc, x - 23, y + 35, NULL);
	LineTo(dc, x - 23, y + 50);
	MoveToEx(dc, x - 17, y + 35, NULL);
	LineTo(dc, x - 17, y + 50);
	//3
	MoveToEx(dc, x - 20, y + 64, NULL);
	LineTo(dc, x - 20, y + 79);
	MoveToEx(dc, x - 26, y + 64, NULL);
	LineTo(dc, x - 26, y + 79);
	MoveToEx(dc, x - 14, y + 64, NULL);
	LineTo(dc, x - 14, y + 79);
	//4
	MoveToEx(dc, x - 26, y + 92, NULL);
	LineTo(dc, x - 26, y + 107);
	MoveToEx(dc, x - 21, y + 92, NULL);
	LineTo(dc, x - 16, y + 107);
	MoveToEx(dc, x - 16, y + 107, NULL);
	LineTo(dc, x - 11, y + 92);
	//5
	MoveToEx(dc, x - 24, y + 120, NULL);
	LineTo(dc, x - 19, y + 135);
	MoveToEx(dc, x - 19, y + 135, NULL);
	LineTo(dc, x - 14, y + 120);
	//6
	MoveToEx(dc, x - 27, y + 148, NULL);
	LineTo(dc, x - 22, y + 163);
	MoveToEx(dc, x - 22, y + 163, NULL);
	LineTo(dc, x - 17, y + 148);
	MoveToEx(dc, x - 12, y + 148, NULL);
	LineTo(dc, x - 12, y + 163);
	//7
	MoveToEx(dc, x - 31, y + 176, NULL);
	LineTo(dc, x - 26, y + 191);
	MoveToEx(dc, x - 26, y + 191, NULL);
	LineTo(dc, x - 21, y + 176);
	MoveToEx(dc, x - 16, y + 176, NULL);
	LineTo(dc, x - 16, y + 191);
	MoveToEx(dc, x - 10, y + 176, NULL);
	LineTo(dc, x - 10, y + 191);
	//8
	MoveToEx(dc, x - 34, y + 204, NULL);
	LineTo(dc, x - 29, y + 219);
	MoveToEx(dc, x - 29, y + 219, NULL);
	LineTo(dc, x - 24, y + 204);
	MoveToEx(dc, x - 19, y + 204, NULL);
	LineTo(dc, x - 19, y + 219);
	MoveToEx(dc, x - 14, y + 204, NULL);
	LineTo(dc, x - 14, y + 219);
	MoveToEx(dc, x - 9, y + 204, NULL);
	LineTo(dc, x - 9, y + 219);
	//9
	MoveToEx(dc, x - 26, y + 232, NULL);
	LineTo(dc, x - 26, y + 247);
	MoveToEx(dc, x - 21, y + 232, NULL);
	LineTo(dc, x - 13, y + 247);
	MoveToEx(dc, x - 13, y + 232, NULL);
	LineTo(dc, x - 21, y + 247);
	//10
	MoveToEx(dc, x - 24, y + 260, NULL);
	LineTo(dc, x - 16, y + 275);
	MoveToEx(dc, x - 16, y + 260, NULL);
	LineTo(dc, x - 24, y + 275);
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
