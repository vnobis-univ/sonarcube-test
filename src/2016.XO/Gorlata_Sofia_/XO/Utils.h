#pragma once
#include <windows.h>
#include "Printer.h"

extern enum { consoleWidth = 80 };
extern enum { topLeftX = 30, topLeftY = 3, cellSize = 5 };

extern HANDLE hConsole;

extern Printer whiteOnBlue;
extern Printer darkBlueOnBlue;
extern Printer purOnBlue;
extern Printer redOnBlue;
extern Printer whiteOnBlack;
extern Printer blueOnBlue;

void setConsoleSize(int x, int y);
void showConsoleCursor(bool showFlag);
void moveCursorTo(int x, int y);

