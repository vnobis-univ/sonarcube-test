#pragma once
#include <string>
#include <windows.h>
#include "Printer.h"

static const int delta = 100;

extern int width;
extern int height;

extern COORD cursor;

extern HANDLE hConsole;

extern CONSOLE_FONT_INFOEX font;

extern HWND handle;
extern HDC dc;
extern RECT r;

extern HPEN penOrange;
extern HPEN penBlue;
extern HPEN penBlack;

extern HBRUSH brushBlack;
extern HBRUSH brushOrange;
extern HBRUSH brushBlue;
extern HBRUSH brushGray;

using namespace std;

void setCursor(int x, int y);
void showConsoleCursor(bool showFlag);
void wait();
void scrollOff(int width, int height);
void printAtMiddle(string text, int y, Printer p);
void printerRect(int x1, int y1, int x2, int y2, Printer& p);
void setConsoleVisability(bool visible);
string inputName();
void setConsole(int w, int h);
HPEN getPen(int r, int g, int b);
HBRUSH getBrush(int r, int g, int b);
void drawFrame();