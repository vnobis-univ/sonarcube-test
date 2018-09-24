#include <iostream>
using namespace std;
#include "OpenWindow.h"
int main()
{
	system("color 40");
	setConsoleSize();
	showConsoleCursor(false);
	setlocale(LC_ALL, "Ukrainian");

	OpenWindow menu;
	menu.draw();

	return 0;
}