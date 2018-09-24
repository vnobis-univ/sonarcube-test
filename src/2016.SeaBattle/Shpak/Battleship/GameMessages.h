#pragma once
#include <Windows.h>
#include "Printer.h"

class GameMessages
{
	static COORD whereFrameStarts;
	static int frameWidth;
	static int frameHeight;

	static Printer hintPrinter;

public:
	GameMessages();

	void clearHints();

	void drawShipPlacementHint();

	void drawWin();

	void drawLose();

	void drawWaitUntilJoin(int);

	void drawWaintUntilMakeMove();

	int getIdForGame();

private:
	int getId(COORD);
};

