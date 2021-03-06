#pragma once
#include <Windows.h>
#include <string>
#include "Printer.h"

using namespace std;

extern HANDLE hconsole;
extern int consoleWidth;
extern int consoleHeight;

void setConsoleSize(int, int);
void setCursor(short, short);
void printTextOnTheCenter(int, string, Printer);
void showCursor(bool);