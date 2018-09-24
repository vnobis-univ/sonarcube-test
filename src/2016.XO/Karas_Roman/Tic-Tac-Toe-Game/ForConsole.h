#pragma once
#include <string>
#include <windows.h>
#include "Printer.h"

using namespace std;

extern HANDLE Screen;
extern int consoleWidth;
extern int consoleHeight;

void setConsoleSize();
void setCursorPosition(int x, int y);
void showCursor(bool yes_no);
void printAtLineCenter(int line, string text, Printer p);