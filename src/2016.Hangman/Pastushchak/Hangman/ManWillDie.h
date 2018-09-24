#pragma once
#include <iostream>
#include <Windows.h>
#include <wingdi.h>
#include "Color.h"
#include <ctime>
using namespace std;

void drawMan(size_t step, int minHealthPoints)
{
	POINT op;
	HWND hWnd = GetConsoleWindow();
	HDC hDC = GetDC(hWnd);
	HPEN hPenBLUE = CreatePen(PS_SOLID, 0, RGB(0, 0, 255));
	HPEN hPenBLACK = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
	HPEN hPenBLOND = CreatePen(PS_SOLID, 0, RGB(250, 240, 190));
	HPEN hPenBROWN = CreatePen(PS_SOLID, 0, RGB(150, 75, 0));

	for (size_t i = 0; i < step; ++i)
	{
		if (i == 0)
		{
			SelectObject(hDC, hPenBLUE);
			MoveToEx(hDC, 100, 100, &op);
			LineTo(hDC, 100, 400);
		}

		if (i == 1)
		{
			SelectObject(hDC, hPenBLUE);
			MoveToEx(hDC, 100, 100, &op);
			LineTo(hDC, 300, 100);
		}

		if (i == 2)
		{
			SelectObject(hDC, hPenBLUE);
			MoveToEx(hDC, 100, 150, &op);
			LineTo(hDC, 150, 100);
		}

		if (i == 3)
		{
			SelectObject(hDC, hPenBLUE);
			MoveToEx(hDC, 300, 100, &op);
			LineTo(hDC, 300, 150);
		}

		if (minHealthPoints > 2)
		{

			if (i == 4)
			{
				SelectObject(hDC, hPenBROWN);
				MoveToEx(hDC, 287, 300, &op);
				LineTo(hDC, 337, 300);
				MoveToEx(hDC, 262, 350, &op);
				LineTo(hDC, 312, 350);
				MoveToEx(hDC, 287, 300, &op);
				LineTo(hDC, 262, 350);
				MoveToEx(hDC, 337, 300, &op);
				LineTo(hDC, 312, 350);

				MoveToEx(hDC, 262, 350, &op);
				LineTo(hDC, 262, 400);

				MoveToEx(hDC, 312, 350, &op);
				LineTo(hDC, 312, 400);

				MoveToEx(hDC, 337, 300, &op);
				LineTo(hDC, 337, 350);
			}

			if (i == 5)
			{
				SelectObject(hDC, hPenBLOND);
				MoveToEx(hDC, 285, 325, &op);
				LineTo(hDC, 300, 250);
			}

			if (i == 6)
			{
				MoveToEx(hDC, 315, 325, &op);
				LineTo(hDC, 300, 250);
			}

			if (i == 7)
			{
				MoveToEx(hDC, 300, 250, &op);
				LineTo(hDC, 300, 200);
			}

			if (i == 8)
			{
				MoveToEx(hDC, 300, 200, &op);
				LineTo(hDC, 265, 235);
			}

			if (i == 9)
			{
				MoveToEx(hDC, 300, 200, &op);
				LineTo(hDC, 335, 235);
			}

			if (i == 10)
			{
				MoveToEx(hDC, 300, 200, &op);
				LineTo(hDC, 300, 190);
			}

			if (i == 11)
			{
				HBRUSH hNewBrush;
				HBRUSH hOldBrush;
				hNewBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
				hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
				Ellipse(hDC, 280, 150, 320, 190);
			}

			if (i == 12)
			{
				HBRUSH hNewBrush;
				HBRUSH hOldBrush;
				hNewBrush = CreateSolidBrush(0x214365);
				hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
				Ellipse(hDC, 288, 167, 298, 157);
			}

			if (i == 13)
			{
				HBRUSH hNewBrush;
				HBRUSH hOldBrush;
				hNewBrush = CreateSolidBrush(0x214365);
				hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
				Ellipse(hDC, 302, 167, 312, 157);
			}

			if (i == 14)
			{
				MoveToEx(hDC, 300, 173, &op);
				LineTo(hDC, 300, 165);
			}

			if (i == 15)
			{
				MoveToEx(hDC, 290, 180, &op);
				LineTo(hDC, 310, 180);
			}

			if (i == 16)
			{
				SelectObject(hDC, hPenBLUE);
				HBRUSH hNewBrush;
				HBRUSH hOldBrush;
				hNewBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
				hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
				Ellipse(hDC, 295, 190, 305, 210);
			}
		}

		if (i == 17)
		{
			SelectObject(hDC, hPenBLACK);
			HBRUSH hNewBrush;
			HBRUSH hOldBrush;
			hNewBrush = CreateSolidBrush(0x000000);
			hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
			Ellipse(hDC, 101, 150, 501, 410);

			SelectObject(hDC, hPenBLOND);
			MoveToEx(hDC, 285, 335, &op);
			LineTo(hDC, 300, 260);

			MoveToEx(hDC, 315, 335, &op);
			LineTo(hDC, 300, 260);

			MoveToEx(hDC, 300, 260, &op);
			LineTo(hDC, 300, 210);

			MoveToEx(hDC, 300, 210, &op);
			LineTo(hDC, 265, 245);

			MoveToEx(hDC, 300, 210, &op);
			LineTo(hDC, 335, 245);

			MoveToEx(hDC, 300, 210, &op);
			LineTo(hDC, 300, 200);

			hNewBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
			Ellipse(hDC, 280, 160, 320, 200);

			hNewBrush = CreateSolidBrush(0x214365);
			hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
			Ellipse(hDC, 288, 177, 298, 167);
			Ellipse(hDC, 302, 177, 312, 167);


			SelectObject(hDC, hPenBLOND);
			MoveToEx(hDC, 300, 183, &op);
			LineTo(hDC, 300, 175);

			MoveToEx(hDC, 290, 190, &op);
			LineTo(hDC, 310, 190);

			hNewBrush = CreateSolidBrush(0xFF0000);
			hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

			Ellipse(hDC, 295, 200, 305, 210);

			SelectObject(hDC, hPenBLUE);
			MoveToEx(hDC, 300, 150, &op);
			LineTo(hDC, 300, 160);
		}

		if (i == 18)
		{
			SelectObject(hDC, hPenBLACK);
			HBRUSH hNewBrush;
			HBRUSH hOldBrush;
			hNewBrush = CreateSolidBrush(0x000000);
			hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
			Ellipse(hDC, 288, 177, 298, 167);

			SelectObject(hDC, hPenBLOND);

			MoveToEx(hDC, 288, 167, &op);
			LineTo(hDC, 298, 177);

			MoveToEx(hDC, 288, 177, &op);
			LineTo(hDC, 298, 167);
		}

		if (i == 19)
		{
			SelectObject(hDC, hPenBLACK);
			HBRUSH hNewBrush;
			HBRUSH hOldBrush;
			hNewBrush = CreateSolidBrush(0x000000);
			hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
			Ellipse(hDC, 302, 177, 312, 167);

			SelectObject(hDC, hPenBLOND);

			MoveToEx(hDC, 302, 167, &op);
			LineTo(hDC, 312, 177);

			MoveToEx(hDC, 302, 177, &op);
			LineTo(hDC, 312, 167);

			Sleep(1000);
		}
	}
}