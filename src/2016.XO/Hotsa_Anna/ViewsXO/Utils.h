#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include "Printer.h"
#include "Player.h"
using namespace std;

extern int consoleWidth;
extern int consoleHeight;
extern HANDLE hConsole;

void setConsoleSize(int width, int height);
void moveCursorTo(int x, int y);
void showCursor(bool showFlag);
void printAtCenter(int lineNumber, string text, Printer p);