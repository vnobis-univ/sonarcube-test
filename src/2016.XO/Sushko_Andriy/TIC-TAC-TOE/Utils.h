#pragma once
#include "view.h"

//edge is the top left edge of the field
extern enum { edgeX = 340, edgeY = 50, cellSize = 80 };
extern enum { consoleWidth = 115 };

extern enum class difficulty { normal, expert };

extern HANDLE hConsole;
extern HDC hdc;

extern Printer purpleOnBlue;
extern Printer aquaOnBlue;
extern Printer whiteOnBlue;
extern Printer blue;
extern Printer white;
extern Printer lightRed;
extern Printer redOnBlue;
extern HPEN bluePen;
extern HPEN redPen;
extern HPEN whitePen;

void moveCursorTo(int x, int y);

void showCursor(bool showFlag);

void systemPauseInLine(int x, int y);

void clean();