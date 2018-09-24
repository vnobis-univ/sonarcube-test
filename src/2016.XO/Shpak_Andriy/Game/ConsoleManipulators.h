#pragma once

void setConsoleSize(int width, int height);

void setCursoreAtPosition(int x, int y);

void getCursorPosition(int& x, int& y);

void setCursorState(bool showFlag);

int getConsoleWidth();

int getConsoleHeight();