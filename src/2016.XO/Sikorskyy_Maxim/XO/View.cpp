#pragma once
#include "Classes.h"

void View::clear()
{
	system("cls");
	SelectObject(dc, penBlack);
	SelectObject(dc, brushBlack);

	Rectangle(dc, 0, 0, 600, 450);
}
