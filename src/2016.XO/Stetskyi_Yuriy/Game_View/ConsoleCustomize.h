#pragma once

#include <Windows.h>
#include <string>
#include "Printer.h"
#include "SysUtils.h"

using namespace std;

const int FONT_WIDTH = 8;
const int FONT_HEIGHT = 12;
const int CONSOLE_WIDTH = 60;
const int CONSOLE_HEIGHT = 35;

void setConsoleProperties();
void printAtCenter(string st, const Printer& p);
void setCursorAt(int x = cursor.X, int y = cursor.Y);

template <class T>
extern string toString(const T& t);