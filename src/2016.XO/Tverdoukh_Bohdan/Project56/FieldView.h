#pragma once
#include "View.h"
#include "MenuView.h"
#include <ctime>
#include "FunctionsForText.h"
#include "FunctionsForField.h"
#include "ResaultView.h"




struct Cursor
{
	int x;
	int y;
	Cursor(int xx = 0, int yy = 0) :x(xx), y(yy){}
};

class Field : public View
{
public:
	int scores ;
	Field(int _scores=0):scores(_scores){}
	bool findWinner(bool isWinner, bool** isFilledX)
	{
	isWinner = false;
	for (int i = 0; i < 3; ++i)
	{
	if (isFilledX[i][0] == true && isFilledX[i][1] == true && isFilledX[i][2] == true)
	{
	isWinner = true;
	}
	}
	for (int j = 0; j < 3; ++j)
	{
	if (isFilledX[0][j] == true && isFilledX[1][j] == true && isFilledX[2][j] == true)
	{
	isWinner = true;
	}
	}
	if (isFilledX[0][0] == true && isFilledX[1][1] == true && isFilledX[2][2] == true)
	{
	isWinner=true;
	}
	if (isFilledX[0][2] == true && isFilledX[1][1] == true && isFilledX[2][0] == true)
	{
	isWinner = true;
	}

	return isWinner;
	}
	bool findLoser(bool isWinner, bool** isFilledX)
	{
		isWinner = false;
		for (int i = 0; i < 3; ++i)
		{
			if (isFilledX[i][0] == true && isFilledX[i][1] == true && isFilledX[i][2] == true)
			{
				isWinner = true;
			}
		}
		for (int j = 0; j < 3; ++j)
		{
			if (isFilledX[0][j] == true && isFilledX[1][j] == true && isFilledX[2][j] == true)
			{
				isWinner = true;
			}
		}
		if (isFilledX[0][0] == true && isFilledX[1][1] == true && isFilledX[2][2] == true)
		{
			isWinner = true;
		}
		if (isFilledX[0][2] == true && isFilledX[1][1] == true && isFilledX[2][0] == true)
		{
			isWinner = true;
		}

		return isWinner;
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

	

	void draw()
	{

		system("cls");
		cout << "Scores: ";
		cout << scores;
		drawField();
		HANDLE Screen;
		Screen = GetStdHandle(STD_OUTPUT_HANDLE);

		COORD gameCursor;
		COORD gameCursorO;
		int startX = 32; // start position
		int startY = 6;  // for gameCursor
		gameCursor.X = startX;
		gameCursor.Y = startY;
		SetConsoleCursorPosition(Screen, gameCursor);

		bool isTie = false;
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
		bool** isFilledX = new bool*[3];
		for (int i = 0; i < 3; ++i)
		isFilledX[i] = new bool[3];
		for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
		isFilledX[i][j] = false;

		bool isLoser = false;
		bool** isFilledO = new bool*[3];
		for (int i = 0; i < 3; ++i)
		isFilledO[i] = new bool[3];
		for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
		isFilledO[i][j] = false;
		

		Cursor cursor; //for storring information(filled or not)

		int key = 0;
		while ((key = _getch()) != 27)
		{
			switch (key)
			{
			case 224:
				key = _getch();
				switch (key)
				{
				case 80:
					if (gameCursor.Y <= startY + 7 && cursor.y < 2)
					{
						gameCursor.Y += 7;
						++cursor.y;
						SetConsoleCursorPosition(Screen, gameCursor);
					}break;
				case 72:
					if (gameCursor.Y >= startY && cursor.y >= 1)
					{
						gameCursor.Y -= 7;
						--cursor.y;
						SetConsoleCursorPosition(Screen, gameCursor);
					}break;
				case 77:
					if (gameCursor.X <= startX + 7 * 2 && cursor.x < 2)
					{
						gameCursor.X += 7;
						++cursor.x;
						SetConsoleCursorPosition(Screen, gameCursor);
					}break;
				case 75:
					if (gameCursor.X >= startX && cursor.x >= 1)
					{
						gameCursor.X -= 7;
						--cursor.x;
						SetConsoleCursorPosition(Screen, gameCursor);
					}break;
				}break;

			case 13:
			case 32:
			
					if (isEmpty[cursor.x][cursor.y] == true)
					{
						drawX(gameCursor);
						isEmpty[cursor.x][cursor.y] = false;
						isFilledX[cursor.x][cursor.y] = true;
						if (findWinner(isWinner, isFilledX) == true)
						{
							system("cls");
							SetColor(2, 0);
							scores++;
							draw();
							break;
						}
						else if (findLoser(isLoser, isFilledO) == true)
						{
							SetColor(4, 0);
							printInTheCentre("You lose:(", 12, 80);
							printInTheCentre("Press Enter to continue", 12, 80);
							bool exit = false;
							while (!exit)
							{
								switch (_getch())
								{
								case 13:
									
									ResaultView menu;
									ResaultView* menu1 = new ResaultView[5];
									ifstream in("Highscore.txt");
									ofstream out("Text.txt");
									for (int i(0); i < 5; i++)
										in >> menu1[i];
									menu.setScore(scores);
									menu.draw();
									menu.sort(menu1, 5, out);
									
									exit = true;
								}
							}
							break;
						}
						else if (findTie(isTie, isEmpty) == true)
						{
							SetColor(8, 0);
							draw();
							break;
						}

						int startX[3] = { 32, 39, 46 };
						int startY[3] = { 6, 13, 20 };

						int coolX;
						int coolY;

						while (true)
						{
							bool isAllFull = true;

							for (size_t i = 0; i < 3; i++)
							{
								for (size_t j = 0; j < 3; j++)
								{
									if (isEmpty[i][j] == true)
									{
										isAllFull = false;
										break;
									}
								}
							}

							if (isAllFull)
							{
								break;
							}


							coolX = rand() % 3;
							coolY = rand() % 3;
							gameCursorO.X = startX[coolX];
							gameCursorO.Y = startY[coolY];


							if (isEmpty[coolX][coolY] == true)
								break;

						}


						isFilledO[coolX][coolY] = true;
						drawO(gameCursorO);
						SetConsoleCursorPosition(Screen, gameCursor);
						isEmpty[coolX][coolY] = false;
						if (findWinner(isWinner, isFilledX) == true)
						{
							system("cls");
							SetColor(2, 0);
							scores++;
							draw();
							break;
						}
						else if (findLoser(isLoser, isFilledO) == true)
						{
							SetColor(4, 0);
							printInTheCentre("You lose:(", 12, 80);
							printInTheCentre("Press Enter to continue", 12, 80);
							bool exit = false;
							while (!exit)
							{
								switch (_getch())
								{
								case 13:

									ResaultView menu;
									ResaultView* menu1 = new ResaultView[100];
									ifstream in("Highscore.txt");
									ofstream out("Text.txt");
									for (int i(0); i < 100; i++)
										in >> menu1[i];
									menu.setScore(scores);
									menu.draw();
									menu.sort(menu1, 100,out);
								}
							}
							break;
						}
						else if (findTie(isTie, isEmpty) == true)
						{
							SetColor(8, 0);
							draw();
							break;
						}
					}
					break;
			}
		}
		
	}
};