#pragma once
#include <Windows.h>
#include "Colors.h"
#include <string>

using namespace std;

extern HWND handlew;
extern HDC dc;
extern HPEN bluePen;
extern HPEN bluePenSmaller;
extern HPEN redPen;
extern HPEN redPenSmaller;
extern HPEN brownPen;
extern HPEN blackPen;

extern HBRUSH PenWhite;
extern HBRUSH PenBlue;
extern HBRUSH PenLightBlue;
extern HBRUSH PenDarkerWhite;
extern HBRUSH PenBlack;

extern int lines;
extern int consoleH;
extern int consoleW;

void drawNet(int x1, int y1);
void drawCross(bool isSel, int x, int y);
void drawPoint(bool isSel, int x, int y);
void setCursor(int x, int y);
void SetColor(int text, int background);
void printInTheCentre(string, int, int);
void drawRectangle(HPEN pen, HBRUSH brush, int x, int y);
void setConsoleSize(int width, int height);
void showConsoleCursor(bool showFlag);
