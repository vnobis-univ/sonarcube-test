#pragma once
#include <windows.h>
#include "Printer.h"

extern const int consoleWidth;

extern HANDLE hConsole;

extern Printer blueOnBlack;
extern Printer lightBlueOnBlack;
extern Printer lightAquaOnBlack;
extern Printer greenOnBlack;
extern Printer lightPurpleOnBlack;
extern Printer purleOnBlack;

extern HDC hdc;
extern HPEN redPen;
extern HPEN bluePen;
extern HPEN brightRed;
extern HPEN blackPen;
extern HPEN greenPen;
extern HPEN testPen;

void setConsoleSize(int x, int y);
void showConsoleCursor(bool showFlag);
void moveCursorTo(int x, int y);



