#include "View.h"
#include <Windows.h>

View::View()
{
}

void View::draw()
{
}

void View::clean()
{
	system("cls");
	HWND hwnd = GetConsoleWindow();
	RECT thisRect;
	GetWindowRect(hwnd, &thisRect);
	RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
}
