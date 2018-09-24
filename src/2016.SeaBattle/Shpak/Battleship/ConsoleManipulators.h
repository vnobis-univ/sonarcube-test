#pragma once
#include <Windows.h>

void setConsoleSize(int, int);

void setDefaultFontProperties();

void setFontSize(int, int);

void setCursoreAtPosition(int, int);

void setCursoreAtPosition(COORD);

void moveCursor(short, short);

void getCursorPosition(COORD&);

void setCursorState(bool);

int getConsoleWidth();

int getConsoleHeight();

bool checkIfKeyPressed();

bool checkIfArrowPressed();

void coolConsoleStuff();