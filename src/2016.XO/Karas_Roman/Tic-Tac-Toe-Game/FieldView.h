#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <sstream> //for stringstream (to convert numbers into string)
#include "View.h"
#include "ForConsole.h"
#include "Printer.h"
#include "Color.h"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_SPACE 32

Printer lGreenOnBlue(Color::LIGHT_GREEN, Color::BLUE);

void printX(COORD cursor)
{
	int x = cursor.X - 2;
	int y = cursor.Y - 2;
	setCursorPosition(x, y);
	
	lGreenOnBlue << "\\    /";
	setCursorPosition(x, y + 1);
	lGreenOnBlue << " \\  / ";
	setCursorPosition(x, y + 2);
	lGreenOnBlue << "  \\/  ";
	setCursorPosition(x, y + 3);
	lGreenOnBlue << "  /\\  ";
	setCursorPosition(x, y + 4);
	lGreenOnBlue << " /  \\ ";
	setCursorPosition(x, y + 5);
	lGreenOnBlue << "/    \\";
	setCursorPosition(x + 2, y + 2);


}

void printO(COORD cursor)
{
	int x = cursor.X - 2;
	int y = cursor.Y - 2;
	setCursorPosition(x, y);
	lGreenOnBlue << "  /\\  ";
	setCursorPosition(x, y + 1);
	lGreenOnBlue << " /  \\ ";
	setCursorPosition(x, y + 2);
	lGreenOnBlue << "/    \\";
	setCursorPosition(x, y + 3);
	lGreenOnBlue << "\\    /";
	setCursorPosition(x, y + 4);
	lGreenOnBlue << " \\  / ";
	setCursorPosition(x, y + 5);
	lGreenOnBlue << "  \\/  ";
	setCursorPosition(x + 2, y + 2);


}

void printEmptyField()
{
	printAtLineCenter(2, "******* ****** *******", lGreenOnBlue);
	printAtLineCenter(3, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(4, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(5, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(6, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(7, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(8, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(9, "******* ****** *******", lGreenOnBlue);
	printAtLineCenter(10, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(11, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(12, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(13, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(14, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(15, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(16, "******* ****** *******", lGreenOnBlue);
	printAtLineCenter(17, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(18, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(19, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(20, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(21, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(22, "*      *      *      *", lGreenOnBlue);
	printAtLineCenter(23, "******* ****** *******", lGreenOnBlue);
}

//to store information, is certain cell filled
struct Cursor
{
	int x;
	int y;
	Cursor(int xx = 0, int yy = 0) :x(xx), y(yy){}
};

template <class T>
string NumberToString(T Number)
{
	stringstream ss;
	ss << Number;
	return ss.str();
}

class Field: public View
{
	int scores = 0;
public:
	
	Field(){}
	bool findWinner(bool isWinner, bool** isFilledX)
	{
		isWinner = false;
		if (isFilledX[0][0] == true && isFilledX[0][1] == true && isFilledX[0][2] == true) isWinner = true;
		else if (isFilledX[1][0] == true && isFilledX[1][1] == true && isFilledX[1][2] == true) isWinner = true;
		else if (isFilledX[2][0] == true && isFilledX[2][1] == true && isFilledX[2][2] == true)isWinner = true;
		else if (isFilledX[0][0] == true && isFilledX[1][1] == true && isFilledX[2][2] == true)isWinner = true;
		else if (isFilledX[0][2] == true && isFilledX[1][1] == true && isFilledX[2][0] == true)isWinner = true;
		else if (isFilledX[0][0] == true && isFilledX[1][0] == true && isFilledX[2][0] == true)isWinner = true;
		else if (isFilledX[0][1] == true && isFilledX[1][1] == true && isFilledX[2][1] == true)isWinner = true;
		else if (isFilledX[0][2] == true && isFilledX[1][2] == true && isFilledX[2][2] == true)isWinner = true;
		return isWinner;
	}
	bool findLoser(bool isLoser, bool** isFilledO)
	{
		isLoser = false;
		if (isFilledO[0][0] == true && isFilledO[0][1] == true && isFilledO[0][2] == true) isLoser = true;
		else if (isFilledO[1][0] == true && isFilledO[1][1] == true && isFilledO[1][2] == true) isLoser = true;
		else if (isFilledO[2][0] == true && isFilledO[2][1] == true && isFilledO[2][2] == true)isLoser = true;
		else if (isFilledO[0][0] == true && isFilledO[1][1] == true && isFilledO[2][2] == true)isLoser = true;
		else if (isFilledO[0][2] == true && isFilledO[1][1] == true && isFilledO[2][0] == true)isLoser = true;
		else if (isFilledO[0][0] == true && isFilledO[1][0] == true && isFilledO[2][0] == true)isLoser = true;
		else if (isFilledO[0][1] == true && isFilledO[1][1] == true && isFilledO[2][1] == true)isLoser = true;
		else if (isFilledO[0][2] == true && isFilledO[1][2] == true && isFilledO[2][2] == true)isLoser = true;
		return isLoser;
	}
	bool findTie(bool isTie, bool** isEmpty)
	{
		isTie = false;
		if (isEmpty[0][0] == false && isEmpty[0][1] == false && isEmpty[0][2] == false &&
		isEmpty[1][0] == false && isEmpty[1][1] == false && isEmpty[1][2] == false &&
		isEmpty[2][0] == false && isEmpty[2][1] == false && isEmpty[2][2] == false &&
		isEmpty[0][0] == false && isEmpty[1][1] == false && isEmpty[2][2] == false &&
		isEmpty[0][2] == false && isEmpty[1][1] == false && isEmpty[2][0] == false &&
		isEmpty[0][0] == false && isEmpty[1][0] == false && isEmpty[2][0] == false &&
		isEmpty[0][1] == false && isEmpty[1][1] == false && isEmpty[2][1] == false &&
		isEmpty[0][2] == false && isEmpty[1][2] == false && isEmpty[2][2] == false)
		isTie = true;
		return isTie;
	}
	void cleaner()
	{
		Printer background(Color::GREEN, Color::BLUE);
		Printer frame(Color::LIGHT_GREEN, Color::GREEN);
		setCursorPosition(0, 2);
		string bodyLine = string(consoleWidth - 2, ' ');
		for (unsigned i = 0; i < 28; ++i)
		{
			frame << " ";
			background << bodyLine;
			frame << " ";
		}
	}
	void GameOver()
	{
		cleaner();
		printAtLineCenter(10, "Game Over", lGreenOnBlue);
		printAtLineCenter(12, "Your scores: " + NumberToString(scores), lGreenOnBlue);
		showCursor(false);
	}
	View* handle()
	{
		View* nextView = this;
		cleaner();
		showCursor(true);
		printAtLineCenter(24, "Scores:   " + NumberToString(scores), lGreenOnBlue);
		//cout << scores;

		printEmptyField();
		HANDLE Screen;
		Screen = GetStdHandle(STD_OUTPUT_HANDLE);
		
		COORD gameCursor;
		int startX = 29; // start position
		int startY = 5;  // for gameCursor
		gameCursor.X = startX;
		gameCursor.Y = startY;
		SetConsoleCursorPosition(Screen, gameCursor);

		bool isTie = false;
		//array of field, shows which cells are empty, or filled
		bool** isEmpty = new bool*[3];
		for (int i = 0; i < 3; ++i)
			isEmpty[i] = new bool[3];
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				isEmpty[i][j] = true;
			}
		}

		bool isWinner = false;
		//array of field, shows which cells are filled by X
		bool** isFilledX = new bool*[3];
		for (int i = 0; i < 3; ++i)
			isFilledX[i] = new bool[3];
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				isFilledX[i][j] = false;

		bool isLoser = false;
		//array of field, shows which cells are filled by X
		bool** isFilledO = new bool*[3];
		for (int i = 0; i < 3; ++i)
			isFilledO[i] = new bool[3];
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				isFilledO[i][j] = false;

		Cursor cursor; //cursor for storing information, is certain cell filled
		
		int key = 0;
		while ((key = _getch()) != KEY_ESC)
		{
			switch (key)
			{
			case 224:
				key = _getch();
				switch (key)
				{
				case KEY_DOWN:
					if (gameCursor.Y <= startY + 7 && cursor.y < 2)
					{
						gameCursor.Y += 7;
						++cursor.y;
						SetConsoleCursorPosition(Screen, gameCursor);
					}break;
				case KEY_UP:
					if (gameCursor.Y >= startY && cursor.y >= 1)
					{
						gameCursor.Y -= 7;
						--cursor.y;
						SetConsoleCursorPosition(Screen, gameCursor);
					}break;
				case KEY_RIGHT:
					if (gameCursor.X <= startX + 7 * 2 && cursor.x < 2)
					{
						gameCursor.X += 7;
						++cursor.x;
						SetConsoleCursorPosition(Screen, gameCursor);
					}break;
				case KEY_LEFT:
					if (gameCursor.X >= startX && cursor.x >= 1)
					{
						gameCursor.X -= 7;
						--cursor.x;
						SetConsoleCursorPosition(Screen, gameCursor);
					}break;
				}
				break;
			case KEY_ENTER:
			case KEY_SPACE:
			case 'X':
			case 'x':
				if (findWinner(isWinner, isFilledX) == true)
				{
					printAtLineCenter(26, "You won\n", lGreenOnBlue);
					scores += 20;
					handle();
					break;
				}
				else if (findLoser(isLoser, isFilledO) == true)
				{
					GameOver();
					break;
				}
				else if (findTie(isTie, isEmpty) == true)
				{
					printAtLineCenter(26, "It is tie.\n", lGreenOnBlue);
					handle();
					break;
				}
				else
				{
					if (isEmpty[cursor.x][cursor.y] == true)
					{
						printX(gameCursor);
						isEmpty[cursor.x][cursor.y] = false;
						isFilledX[cursor.x][cursor.y] = true;
						if (findWinner(isWinner, isFilledX) == true)
						{
							printAtLineCenter(26, "You won\n", lGreenOnBlue);
							scores += 20;
							handle();
							break;
						}
						else if (findLoser(isLoser, isFilledO) == true)
						{
							GameOver();
							break;
						}
						else if (findTie(isTie, isEmpty) == true)
						{
							printAtLineCenter(26, "It is tie.\n", lGreenOnBlue);
							handle();
							break;
						}
						//For O, BOT
						//    x _ _
						//    _ x _
						//    _ _ o
						if (gameCursor.Y <= startY + 7 && cursor.y < 2 && gameCursor.X <= startX + 7 * 2 && cursor.x < 2  && isFilledX[0][0] == true && isFilledX[1][1] == true && isEmpty[2][2] == true)
						{
							gameCursor.Y += 7;
							gameCursor.X += 7;
							++cursor.y;
							++cursor.x;
							SetConsoleCursorPosition(Screen, gameCursor);
							if (gameCursor.Y <= startY + 7 && cursor.y < 2)
							{
								gameCursor.Y += 7;
								gameCursor.X += 7;
								++cursor.y;
								++cursor.x;
								SetConsoleCursorPosition(Screen, gameCursor);
							}
							printO(gameCursor);
							isEmpty[cursor.x][cursor.y] = false;
							isFilledO[cursor.x][cursor.y] = true;
							if (findWinner(isWinner, isFilledX) == true)
							{
								printAtLineCenter(26, "You won\n", lGreenOnBlue);
								scores += 20;
								handle();
								break;
							}
							else if (findLoser(isLoser, isFilledO) == true)
							{
								GameOver();
								break;
							}
							else if (findTie(isTie, isEmpty) == true)
							{
								printAtLineCenter(26, "It is tie.\n", lGreenOnBlue);
								handle();
								break;
							}
						}

						// 1) x
						//    x
						//    o
						else if (gameCursor.Y <= startY + 7 && cursor.y < 2 && isFilledX[cursor.x][0] == true && isFilledX[cursor.x][1] == true && isEmpty[cursor.x][2] == true)
						{
							gameCursor.Y += 7;
							++cursor.y;
							SetConsoleCursorPosition(Screen, gameCursor);
							if (gameCursor.Y <= startY + 7 && cursor.y < 2)
							{
								gameCursor.Y += 7;
								++cursor.y;
								SetConsoleCursorPosition(Screen, gameCursor);
							}
							printO(gameCursor);
							isEmpty[cursor.x][cursor.y] = false;
							isFilledO[cursor.x][cursor.y] = true;
							if (findWinner(isWinner, isFilledX) == true)
							{
								printAtLineCenter(26, "You won\n", lGreenOnBlue);
								scores += 20;
								handle();
								break;
							}
							else if (findLoser(isLoser, isFilledO) == true)
							{
								GameOver();
								break;
							}
							else if (findTie(isTie, isEmpty) == true)
							{
								printAtLineCenter(26, "It is tie.\n", lGreenOnBlue);
								handle();
								break;
							}
						}
						// 2) x x o
						//
						//
						else if (gameCursor.X <= startX + 7 * 2 && cursor.x < 2 && isFilledX[0][cursor.y] == true && isFilledX[1][cursor.y] == true && isEmpty[2][cursor.y] == true)
						{
							gameCursor.X += 7;
							++cursor.x;
							SetConsoleCursorPosition(Screen, gameCursor);
							if (gameCursor.X <= startX + 7 * 2 && cursor.x < 2)
							{
								gameCursor.X += 7;
								++cursor.x;
								SetConsoleCursorPosition(Screen, gameCursor);
							}
							printO(gameCursor);
							isEmpty[cursor.x][cursor.y] = false;
							isFilledO[cursor.x][cursor.y] = true;
							if (findWinner(isWinner, isFilledX) == true)
							{
								printAtLineCenter(26, "You won\n", lGreenOnBlue);
								scores += 20;
								handle();
								break;
							}
							else if (findLoser(isLoser, isFilledO) == true)
							{
								GameOver();
								break;
							}
							else if (findTie(isTie, isEmpty) == true)
							{
								printAtLineCenter(26, "It is tie.\n", lGreenOnBlue);
								handle();
								break;
							}
						}
						// 3) _ x o
						//    x o _
						//    _ _ x
						else if (gameCursor.X <= startX + 7 * 2 && cursor.x < 2 && isEmpty[cursor.x + 1][cursor.y] == true)
						{
							gameCursor.X += 7;
							++cursor.x;
							SetConsoleCursorPosition(Screen, gameCursor);
							printO(gameCursor);
							isEmpty[cursor.x][cursor.y] = false;
							isFilledO[cursor.x][cursor.y] = true;
							if (findWinner(isWinner, isFilledX) == true)
							{
								printAtLineCenter(26, "You won\n", lGreenOnBlue);
								scores += 20;
								handle();
								break;
							}
							else if (findLoser(isLoser, isFilledO) == true)
							{
								GameOver();
								break;
							}
							else if (findTie(isTie, isEmpty) == true)
							{
								printAtLineCenter(26, "It is tie.\n", lGreenOnBlue);
								handle();
								break;
							}
						}
						// 3) o x _
						//    _ o x
						//    x _ _
						else if (gameCursor.X >= startX && cursor.x >= 1 && isEmpty[cursor.x - 1][cursor.y] == true)
						{
							gameCursor.X -= 7;
							--cursor.x;
							SetConsoleCursorPosition(Screen, gameCursor);
							printO(gameCursor);
							isEmpty[cursor.x][cursor.y] = false;
							isFilledO[cursor.x][cursor.y] = true;
							if (findWinner(isWinner, isFilledX) == true)
							{
								printAtLineCenter(26, "You won\n", lGreenOnBlue);
								scores += 20;
								handle();
								break;
							}
							else if (findLoser(isLoser, isFilledO) == true)
							{
								GameOver();
								break;
							}
							else if (findTie(isTie, isEmpty) == true)
							{
								printAtLineCenter(26, "It is tie.\n", lGreenOnBlue);
								handle();
								break;
							}
						}
						// 4) o _ x
						//    x o _
						//    _ x _
						else if (gameCursor.Y <= startY + 7 && cursor.y < 2 && isEmpty[cursor.x][cursor.y + 1] == true)
						{
							gameCursor.Y += 7;
							++cursor.y;
							SetConsoleCursorPosition(Screen, gameCursor);
							printO(gameCursor);
							isEmpty[cursor.x][cursor.y] = false;
							isFilledO[cursor.x][cursor.y] = true;
							if (findWinner(isWinner, isFilledX) == true)
							{
								printAtLineCenter(26, "You won\n", lGreenOnBlue);
								scores += 20;
								handle();
								break;
							}
							else if (findLoser(isLoser, isFilledO) == true)
							{
								GameOver();
								break;
							}
							else if (findTie(isTie, isEmpty) == true)
							{
								printAtLineCenter(26, "It is tie.\n", lGreenOnBlue);
								handle();
								break;
							}
						}
						// 4) x _ _
						//    o x _
						//    _ o x
						else if (gameCursor.Y <= startY + 7 && cursor.y < 2 && isEmpty[cursor.x][cursor.y - 1] == true)
						{
							gameCursor.Y -= 7;
							--cursor.y;
							SetConsoleCursorPosition(Screen, gameCursor);
							printO(gameCursor);
							isEmpty[cursor.x][cursor.y] = false;
							isFilledO[cursor.x][cursor.y] = true;
							if (findWinner(isWinner, isFilledX) == true)
							{
								printAtLineCenter(26, "You won\n", lGreenOnBlue);
								scores += 20;
								handle();
								break;
							}
							else if (findLoser(isLoser, isFilledO) == true)
							{
								GameOver();
								break;
							}
							else if (findTie(isTie, isEmpty) == true)
							{
								printAtLineCenter(26, "It is tie.\n", lGreenOnBlue);
								handle();
								break;
							}
						}break;
						break;
					}break;
					
				}break;
			}
		}
		printAtLineCenter(28, "You've decided to quit the game. Press ESC.\n", lGreenOnBlue);
		return nextView;
	}
};