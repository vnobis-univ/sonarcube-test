#include "Field.h"
#include "ConsoleUtils.h"
#include <iostream>

Field::Field()
{
	for (size_t i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			field[i][j] = StateOfFieldCell::Empty;
		}
	}
}

StateOfFieldCell Field::getStateOfCell(int i, int j)
{
	return field[i][j];
}

void Field::setStateOfCell(int i, int j, StateOfFieldCell state)
{
	field[i][j] = state;
}

void Field::drawEmptyField(int x, int y)
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HPEN bluePen = CreatePen(PS_SOLID, 2, RGB(14,11,40));
	HGDIOBJ currentPen = SelectObject(hdc, bluePen);
	for (int i = 0; i < 11; i++)
	{
		MoveToEx(hdc, x * 10 + 2 * i * 10, y * 16, NULL);
		LineTo(hdc, x * 10 + 2 * i * 10, y * 16 + 10 * 16);
	}
	for (int i = 0; i < 11; i++)
	{
		MoveToEx(hdc, x * 10, y * 16 + i * 16, NULL);
		LineTo(hdc, x * 10 + 20 * 10, y * 16 + i * 16);
	}
	DeleteObject(bluePen);
	DeleteObject(currentPen);
	ReleaseDC(hwnd, hdc);
}
void Field::draw(int x, int y)
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HPEN bluePen = CreatePen(PS_SOLID, 3, RGB(210, 255, 250));
	HGDIOBJ currentPen = SelectObject(hdc, bluePen);
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			if (field[i][j] == StateOfFieldCell::NotEmpty)
			{
				MoveToEx(hdc, x * 10 + 2 * j * 10 + 9, y * 16 + i * 16 + 7, NULL);
				LineTo(hdc, x * 10 + 2 * j * 10 + 11, y * 16 + i * 16 + 7);
				LineTo(hdc, x * 10 + 2 * j * 10 + 11, y * 16 + i * 16 + 9);
				LineTo(hdc, x * 10 + 2 * j * 10 + 9, y * 16 + i * 16 + 9);
				LineTo(hdc, x * 10 + 2 * j * 10 + 9, y * 16 + i * 16 + 7);
			}
		}
	}
	DeleteObject(bluePen);
	DeleteObject(currentPen);
	ReleaseDC(hwnd, hdc);
}

