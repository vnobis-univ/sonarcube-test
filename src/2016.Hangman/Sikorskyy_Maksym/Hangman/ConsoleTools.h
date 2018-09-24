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
extern HPEN penPink;

extern HBRUSH brushBlack;
extern HBRUSH brushOrange;
extern HBRUSH brushBlue;
extern HBRUSH brushGray;
extern HBRUSH brushPink;

using namespace std;

void drawFrame();
void setCursor(int x, int y);
void showConsoleCursor(bool showFlag);
void wait();
void printAtCenter(string text, int y, Printer p, int beginning = 0);
void printerRect(int x1, int y1, int x2, int y2, Printer& p);
void setConsoleVisability(bool visible);
string inputName(int sz, int x, int y);
void setConsole(int w, int h);
int getHP();
int getBonusses();
int getFines();