#pragma once
#include "CellState.h"
#include "RenderHelper.h"
#include <windows.h>
#include <winuser.h>
#include <wingdi.h>
#include <wincon.h>

RenderHelper::RenderHelper(int cell_width, int cell_height) :
	cell_width_(cell_width), cell_height_(cell_height)
{
	hwnd_ = GetConsoleWindow();
	hdc_ = GetDC(hwnd_);
}

RenderHelper::~RenderHelper()
{
	ReleaseDC(hwnd_, hdc_);
}

void RenderHelper::drawMissedCellState(int x, int y, COLORREF color_rgb)
{
	HPEN pen = CreatePen(PS_SOLID, 2, color_rgb);
	HGDIOBJ gdiObj = SelectObject(hdc_, pen);

	MoveToEx(hdc_, x * cell_width_ + cell_width_ / 2 - 1, y * cell_height_ + cell_height_ / 2 - 1, NULL);
	LineTo(hdc_, x * cell_width_ + cell_width_ / 2 + 1, y * cell_height_ + cell_height_ / 2 - 1);
	LineTo(hdc_, x * cell_width_ + cell_width_ / 2 + 1, y * cell_height_ + cell_height_ / 2 + 1);
	LineTo(hdc_, x * cell_width_ + cell_width_ / 2 - 1, y * cell_height_ + cell_height_ / 2 + 1);
	LineTo(hdc_, x * cell_width_ + cell_width_ / 2 - 1, y * cell_height_ + cell_height_ / 2 - 1);

	DeleteObject(pen);
	DeleteObject(gdiObj);
}

void RenderHelper::drawHitCellState(int x, int y, COLORREF color_rgb)
{
	HPEN pen = CreatePen(PS_SOLID, 2, color_rgb);
	HGDIOBJ gdiObj = SelectObject(hdc_, pen);

	MoveToEx(hdc_, x * cell_width_, y * cell_height_, NULL);
	LineTo(hdc_, (x + 1) * cell_width_, (y + 1) * cell_height_);
	MoveToEx(hdc_, x * cell_width_, (y + 1) * cell_height_, NULL);
	LineTo(hdc_, (x + 1) * cell_width_, y * cell_height_);

	DeleteObject(pen);
	DeleteObject(gdiObj);
}

void RenderHelper::drawLine(int x1, int y1, int x2, int y2, COLORREF color_rgb)
{
	HPEN pen = CreatePen(PS_SOLID, 2, color_rgb);
	HGDIOBJ gdiObj = SelectObject(hdc_, pen);

	MoveToEx(hdc_, x1 * cell_width_, y1 * cell_height_, NULL);
	LineTo(hdc_, x2 * cell_width_, y2 * cell_height_);

	DeleteObject(pen);
	DeleteObject(gdiObj);
}

void RenderHelper::drawRectangle(int x, int y, int width, int height, COLORREF color_rgb)
{
	HPEN pen = CreatePen(PS_SOLID, 2, color_rgb);
	HGDIOBJ gdiObj = SelectObject(hdc_, pen);

	MoveToEx(hdc_, x * cell_width_, y * cell_height_, NULL);
	LineTo(hdc_, (x + width) * cell_width_, y * cell_height_);
	LineTo(hdc_, (x + width) * cell_width_, (y + height) * cell_height_);
	LineTo(hdc_, x * cell_width_, (y + height) * cell_height_);
	LineTo(hdc_, x * cell_width_, y * cell_height_);

	DeleteObject(pen);
	DeleteObject(gdiObj);
}