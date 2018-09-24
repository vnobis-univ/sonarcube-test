#pragma once

#include <string>
#include <windows.h>
#include "Printer.h"

using namespace std;

extern HANDLE hConOut;
extern int consoleWidth;
extern int consoleHeight;

void setConsoleSize(int width, int height);
void setCursoreAtPosition(int x, int y);
void showConsoleCursor(bool showFlag);
void printAtCenterOfLine(int line, string text, Printer p);