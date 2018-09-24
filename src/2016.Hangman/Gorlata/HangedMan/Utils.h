#pragma once
#include <windows.h>
#include "Printer.h"


extern enum {consoleWidth = 80};

extern HANDLE hConsole;

extern Printer lightAquaOnBlack;
extern Printer greenOnBlack;
extern Printer lightPurpleOnBlack;
extern Printer purleOnBlack;



void setConsoleSize(int x, int y);
void showConsoleCursor(bool showFlag);
void moveCursorTo(int x, int y);


