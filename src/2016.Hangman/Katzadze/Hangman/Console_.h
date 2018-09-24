#pragma once
#include "Printer.h"

void setConsoleSize(int, int);
void dontAllowToChangeSize();
void setCursor(short, short);
void printInCenter(int, string, Printer);
void showCursor(bool);
void enableUkrainianLang();