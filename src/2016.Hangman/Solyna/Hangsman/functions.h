#pragma once
#include <windows.h>
#include <iomanip>
#include <string>
#include <iostream>
#include "Printer.h"
using namespace std;

void setConsoleSize(int width, int height);
void setCursoreAtPosition(int x, int y);
void printAtCenterOfLine(int line, string text, Printer p, int consoleWidth);
void showConsoleCursor(bool showFlag);