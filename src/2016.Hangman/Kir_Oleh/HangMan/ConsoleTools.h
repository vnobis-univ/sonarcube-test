#pragma once
#include <Windows.h>
#include "Printer.h"
#include "SavingWinners.h"
#include "Buttons.h"
#include "Dictionary.h"
#include "Translating.h"
#include <conio.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

static const int delta = 100;

extern int width;
extern int height;

extern COORD cursor;

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

void setPen(int r, int g, int b);
void setBrush(int r, int g, int b);
void drawFrame();
void setCursor(int x, int y);
void showConsoleCursor(bool showFlag);
void wait();
void printAtMiddle(string text, int y, Printer p, int beginning = 0);
void printerRect(int x1, int y1, int x2, int y2, Printer p);
void setConsoleVisability(bool visible);
string inputName(int sz, int x, int y);
void setConsole(int w, int h);