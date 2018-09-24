#pragma once
#include "Printer.h"

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

extern int landslide;

void drawFrame(HPEN, HBRUSH, int, int, int, int);
void drawNet(int, int);
void drawCross(bool, int, int);
void drawPoint(bool, int, int);
void drawRectangle(HPEN, HBRUSH, int, int);
void drawNumbers(int, int);
void setConsoleSize(int, int);
void dontAllowToChangeSize();
void setCursor(short, short);
void printTextOnTheCenter(int, string, Printer);
void showCursor(bool);
void enableUkrainianLang();