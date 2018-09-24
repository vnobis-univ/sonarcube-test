#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include "Printer.h"

using namespace std;

void SetColor(int, int);

void setConsoleSize(int, int);

void setCursoreAtPosition(int, int);

void printAtCenterOfLine(int, string, Printer, int);

void showConsoleCursor(bool);

void PrintUkr();
void PrintEng();
