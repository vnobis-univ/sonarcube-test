#pragma once
#include <windows.h>

class RenderHelper
{
	int cell_width_;
	int cell_height_;
	HWND hwnd_;
	HDC hdc_;
public:
	RenderHelper(int cell_width, int cell_height);
	~RenderHelper();
	void drawMissedCellState(int x, int y, COLORREF color_rgb);
	void drawHitCellState(int x, int y, COLORREF color_rgb);
	void drawLine(int x1, int y1, int x2, int y2, COLORREF color_rgb);
	void drawRectangle(int x, int y, int width, int height, COLORREF color_rgb);
};
