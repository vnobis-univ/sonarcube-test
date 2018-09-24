#include "Functions.h"

//Щоб гарно друкувати
void SetColor(int text, int background)
{
	HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConOut, background * 16 + text);
}

//Щоб друкувати там де хочеш
void setCursoreAtPosition(int x, int y)
{
	HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD pos = { x, y };
	SetConsoleCursorPosition(hConOut, pos);
}

//Так щоб по середині писати
void printAtCenterOfLine(int line, string text, Printer p, int consoleWidth)
{
	HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = consoleWidth / 2 - text.length() / 2;
	position.Y = line;
	SetConsoleCursorPosition(hConOut, position);
	p.print(text);
}

//Щоб не блимало весь час в кінці рядка...
void showConsoleCursor(bool showFlag)
{
	HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConOut, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(hConOut, &cursorInfo);
}

//ОБЕРЕЖНО! РУЧНА РОБОТА! 
void PrintUkr()
{
	Printer sel(LIGHT_YELLOW, BLACK);
	Printer sel2(LIGHT_BLUE, BLACK);
	printAtCenterOfLine(0, " _   _   _   _      _   ______   _____   _    _   _      _   _    _    _____", sel2, 80);
	printAtCenterOfLine(1, "|_| |_| |_| |_|  //|_| | |____| |  __ | |_|  |_| |_|  //|_| |_|  |_|  |  __ |", sel2, 80);
	printAtCenterOfLine(2, "|_| |_| |_| |_| // |_| | |____  |  ___| |_|__|_| |_| // |_| |_|  |_|  |_____|", sel2, 80);
	printAtCenterOfLine(3, "|_|_|_|_|_| |_|//  |_| |  __  | | |___  |_|  |_| |_|//  |_| |_|__|_|   // |_|", sel, 80);
	printAtCenterOfLine(4, "|_________| |_//   |_| |______| |_____| |_|  |_| |_//   |_| |______|_ //  |_|", sel, 80);
}

//ОБЕРЕЖНО! РУЧНА РОБОТА! 
//З тим намучився(надіюсь не марно)
void PrintEng()
{
	Printer sel(LIGHT_RED, BLACK);
	Printer sel2(WHITE, BLACK);
	Printer sel3(BLUE, BLACK);
	printAtCenterOfLine(0, "   _    _      __      _     _   ______   _        _      __      _     _ ", sel3, 75);
	printAtCenterOfLine(1, " |_|  |_|    /  \\    |_\\   |_| |_ ____| |_\\      /_|    /  \\    |_\\   |_|", sel3, 75);
	printAtCenterOfLine(2, " |_|__|_|   / __ \\   |_|\\  |_| |_|   _  |_|\\    /|_|   / __ \\   |_|\\  |_|", sel2, 75);
	printAtCenterOfLine(3, " |_|  |_|  / ____ \\  |_| \\ |_| |_|__| | |_| \\  / |_|  / ____ \\  |_| \\ |_|", sel, 75);
	printAtCenterOfLine(4, "  |_|  |_| /_/    \\_\\ |_|  \\|_| |______| |_|  \\/  |_| /_/    \\_\\ |_|  \\|_|", sel, 75);
}