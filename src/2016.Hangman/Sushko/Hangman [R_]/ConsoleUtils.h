#pragma once
#include <afxinet.h>
#include <string>
#include "Printer.h"

extern const int consoleWidth;

extern enum class Lang { ENG, UKR };
extern enum class Difficulty { Easy, Normal, Hard };

extern HANDLE hConsole;
extern HDC hdc;

extern Printer white;
extern Printer yellow;
extern Printer purple;
extern Printer lPurpleOnPurple;
extern Printer red;
extern Printer lightRed;
extern HPEN whitePen;
extern HPEN purplePen;

void setConsoleSize(int width, int height);
void restrictResize();
void showCursor(bool showFlag);
void enableUkrainian();
void systemPauseAt(int x, int y, std::string message);
bool confirmExit(string msg);

void moveTo(int x, int y);