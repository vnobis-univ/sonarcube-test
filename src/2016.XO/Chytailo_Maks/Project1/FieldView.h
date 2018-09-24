#pragma once
#include <iostream>
#include <string>
#include "View.h"

using namespace std;

class FieldView : public View
{
protected:
	
	int score = 0;
	char name[50];
	bool gameDraw = false;
	bool winnerX = false;
	bool winnerO = false;
	

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	void SetColor(int text, int background)
	{
		SetConsoleTextAttribute(hStdOut, background * 16 + text);
	}
	string board[3][3] = { " ", " ", " ", " ", " ", " ", " ", " " ," " };
	short curI = 1, curJ = 1;
	int k = 0;
	int count = 0;
	friend ostream& operator<<(ostream& out, FieldView &h);
	

	void Check();

	void DrawCell(short , short );

	void bot(string board[3][3]);
	
	void winner(string board[3][3]);

	void SelectedCell();
	void centre();
public:
	void Draw();


};
