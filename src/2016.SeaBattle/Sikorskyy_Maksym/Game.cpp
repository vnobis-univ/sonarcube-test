#include "Game.h"
void drawCell(int startX, Coordinate coord, FrameState frame, CellState cell)
{
	int x = startX + 30 * coord.x;
	int y = 70 + 30 * coord.y;

	switch ((int)frame)
	{
	case 0:
	{
			  SelectObject(dc, penGray);
			  SelectObject(dc, brushGray);
	}
		break;
	case 1:
	{
			  SelectObject(dc, penBlue);
			  SelectObject(dc, brushBlue);
	}
		break;
	case 2:
	{
			  SelectObject(dc, penRed);
			  SelectObject(dc, brushRed);
	}
		break;

	}
	Rectangle(dc, x, y, x + 30, y + 30);

	SelectObject(dc, brushBlack);
	Rectangle(dc, x + 2, y + 2, x + 30 - 2, y + 30 - 2);
	SelectObject(dc, penBlack);
	switch ((int)cell)
	{
	case 0:
	{
			  SelectObject(dc, brushBlack);
	}
		break;
	case 1:
	{
			  SelectObject(dc, brushGray);
	}
		break;
	case 2:
	{
			  SelectObject(dc, brushRed);
	}
		break;
	case 3:
	{
			  SelectObject(dc, brushGreen);
	}
		break;

	}
	Ellipse(dc, x + 3, y + 3, x + 30 - 3, y + 30 - 3);
}