#pragma once
#include "Printers.h"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESCAPE 27
#define KEY_SPACE 32

extern int consoleWidth;
extern int consoleHeight;
extern HANDLE hConsole;

void setConsoleSize(int width, int height);
void moveCursorTo(int x, int y);
void showCursor(bool showFlag);
void printAtCenter(int lineNumber, string text, Printer p);
void setConsoleTextType();