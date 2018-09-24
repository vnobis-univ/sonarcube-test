#pragma once
#include <Windows.h>

class HangmanPicture
{
	static COORD whereFrameStarts;

	static int frameWidth;
	static int frameHeight;

public:
	void drawFrame();

	void drawScoreAndHP(unsigned, unsigned);

	int getWhereFrameEnds();

	int getFrameWidth();

	void drawHangman(int, bool = false);
	
private:
	void renewPicture();

	void drawElementsOfHangman(int);
};

