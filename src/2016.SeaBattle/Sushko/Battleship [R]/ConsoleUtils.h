#pragma once
#include <Windows.h>
#include <string>

void setConsoleSize(int width, int height);

void setConsoleFont();

void enableUkrainian();

void removeScrollbar();

void disableResizing();

void moveTo(int x, int y);

void showCursor(bool showFlag);

void drawLine(COORD from, COORD to);

bool confirmExit(std::string msg);

std::string consoleInput(COORD coord, int maxLength, char firstValid = -128, char lastValid = 255);