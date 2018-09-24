#pragma once
#include <iostream>
#include <string>
#include "Main.h"

using namespace std;

class HighScores : public Head
{
	string name;
	int score;
	HANDLE hStdOut;


	void SetColor(int text, int background) 
	{
		SetConsoleTextAttribute(hStdOut, background * 16 + text);
	}
	void gotoxy(int x,int y)
	{
	  HANDLE hConsole;
	  COORD cursorLoc;
	  std::cout.flush();
	  cursorLoc.X = x;
	  cursorLoc.Y = y;
	  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	  SetConsoleCursorPosition(hConsole, cursorLoc);
	}
public:
	HighScores() : name("-"), score(0) {hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);}
	HighScores(string _name, int _score) : name(_name), score(_score) {}

	friend istream& operator>>(istream& in, HighScores& h);
	friend ostream& operator<<(ostream& cout, HighScores& h);

	void Draw();
};