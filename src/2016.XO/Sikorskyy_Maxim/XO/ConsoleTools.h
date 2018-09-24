#pragma once
#include <string>
#include <windows.h>
#include "Printer.h"

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
extern HPEN penGray;

extern HBRUSH brushBlack;
extern HBRUSH brushOrange;
extern HBRUSH brushBlue;
extern HBRUSH brushGray;

using namespace std;

void setCursor(int x, int y);
void showConsoleCursor(bool showFlag);
void wait();
void scrollDis(int width, int height);
void printAtMiddle(string text, int y, Printer p);
void printRect(int x1, int y1, int x2, int y2, Printer& p);
void ConsoleVisible(bool visible);
string inputName();
void setConsole(int w, int h);
HPEN getPen(int r, int g, int b);
HBRUSH getBrush(int r, int g, int b);
