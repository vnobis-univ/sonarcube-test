#include "View.h"

View::View()
{}
void View::clean()
{
	system("cls");
	HWND hwnd = GetConsoleWindow();
	RECT thisRect;
	GetWindowRect(hwnd, &thisRect);
	RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
}

void View::draw()
{}

View * View::handle()
{
	return nullptr;
}
