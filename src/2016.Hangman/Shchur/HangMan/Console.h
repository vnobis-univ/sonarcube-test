#pragma once
#include "Printer.h"

extern HWND handlew;
extern HDC dc;
extern HPEN greenPan;
extern HBRUSH PanBlack;

void drawHangedMan(bool);
void drawFrame(HPEN, HBRUSH, int, int, int, int);
void setConsoleSize(int, int);
void dontAllowToChangeSize();
void setCursor(short, short);
void printTextOnTheCenter(int, string, Printer);
void showCursor(bool);
void enableUkrainianLang();