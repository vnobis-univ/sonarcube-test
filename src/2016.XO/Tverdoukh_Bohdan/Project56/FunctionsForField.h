#pragma once
#include "View.h"
#include "FieldView.h"
#include "FunctionsForText.h"

void drawX(COORD cursor)
{
	int x = cursor.X - 2;
	int y = cursor.Y - 2;
	setCursorPosition(x, y);
	SetColor(15, 0);
	cout << "*    *";
	setCursorPosition(x, y + 1);
	SetColor(15, 0);
	cout << " *  * ";
	setCursorPosition(x, y + 2);
	SetColor(15, 0);
	cout << "  **  ";
	setCursorPosition(x, y + 3);
	SetColor(15, 0);
	cout << " *  * ";
	setCursorPosition(x, y + 4);
	SetColor(15, 0);
	cout << "*    *";
	setCursorPosition(x, y + 5);
	SetColor(15, 0);
	cout << "     ";
	setCursorPosition(x + 2, y - 2);
}
void drawO(COORD cursor)
{
	int x = cursor.X - 2;
	int y = cursor.Y - 2;
	setCursorPosition(x, y);
	SetColor(11, 0);
	cout << " **** ";
	setCursorPosition(x, y + 1);
	SetColor(11, 0);
	cout << "*    *";
	setCursorPosition(x, y + 2);
	SetColor(11, 0);
	cout << "*    *";
	setCursorPosition(x, y + 3);
	SetColor(11, 0);
	cout << "*    *";
	setCursorPosition(x, y + 4);
	SetColor(11, 0);
	cout << "*    *";
	setCursorPosition(x, y + 5);
	SetColor(11, 0);
	cout << " **** ";
	setCursorPosition(x + 2, y - 2);
}
void drawField()
{
	SetColor(8, 0);
	printInTheCentre("**********************", 3, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 4, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 5, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 6, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 7, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 8, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 9, 80);
	SetColor(8, 0);
	printInTheCentre("**********************", 10, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 11, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 12, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 13, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 14, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 15, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 16, 80);
	SetColor(8, 0);
	printInTheCentre("**********************", 17, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 18, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 19, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 20, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 21, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 22, 80);
	SetColor(8, 0);
	printInTheCentre("*      *      *      *", 23, 80);
	SetColor(8, 0);
	printInTheCentre("**********************", 24, 80);

}