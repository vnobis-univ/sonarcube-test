#pragma once
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

void setCursorPosition(int xx, int yy);

void SetColor(int text, int background);

void printInTheCentre(string str, int numberOfLine);

void clean();


string NumberToString(int Number);

void resetColor();

void setConsoleSize();

void showConsoleCursor(bool showFlag);