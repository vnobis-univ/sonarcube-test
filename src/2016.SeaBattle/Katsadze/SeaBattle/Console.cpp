#include "Console.h"
#include "Printer.h"

Printer printer(ConsoleColor::LightGray, ConsoleColor::White);
Printer rect(ConsoleColor::Green, ConsoleColor::White);

int consoleWidth;
int consoleHeight;

void drawNet()
{
	for (size_t i = 0; i < 10; ++i)
	{
		for (size_t j = 0; j < 10; ++j)
		{
			setCursor(i*4+5, j+9);
			printer << "    ";
			setCursor(i*4 + 5, j*2+10);
			printer << "    ";
		}
	}

	for (size_t i = 0; i < 10; ++i)
	{
		for (size_t j = 0; j < 10; ++j)
		{
			setCursor(i * 4 + 50, j * 2 + 9);
			printer << "    ";
			setCursor(i * 4 + 50, j * 2 + 10);
			printer << "    ";
		}
	}
}


void drawRectangle(int x, int y)
{
	setCursor(x, y);
	rect << "    ";
	setCursor(x, y + 1);
	rect << "    ";
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

void printInCenter(int line, string text, Printer p)
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
