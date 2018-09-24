#pragma once 

#include "View.h"
#include "FieldView.h"
#include "HighScoreView.h"
#include "ResultView.h"
#include "StartView.h"

// View classes
extern FieldView fieldView;
extern StartView startView;
extern ResultView resultView;
extern HighScoreView scoresView;

// Console utilities
extern HWND hwnd;
extern HDC hdc;
extern RECT rect;
extern POINT op;
extern COORD cursor;
extern HANDLE hConsole;

// Printers
extern Printer headline;
extern Printer finish;
extern Printer stats;

