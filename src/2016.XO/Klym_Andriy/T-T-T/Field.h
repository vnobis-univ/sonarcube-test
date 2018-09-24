#pragma once
#include <iostream>
#include <string>

#include "Main.h"

using namespace std;

class FieldView : public Head
{
protected:
	
	int score;
	char name[50];
	bool gameDraw;
	bool winnerX;
	bool winnerO;
	

	HANDLE hStdOut;
	void SetColor(int text, int background)
	{
		SetConsoleTextAttribute(hStdOut, background * 16 + text);
	}
	string board[3][3];
	short curI, curJ;
	int k;
	int count;
	friend ostream& operator<<(ostream& out, FieldView &h);
	

	void Check();

	void DrawCell(short , short );

	void bot(string board[3][3]);
	
	void winner(string board[3][3]);

	void SelectedCell();
	void centre();
public:
	void Draw();
	FieldView()
	{
		score = 0;
		gameDraw = false;
		winnerX = false;
		winnerO = false;
		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		curI = 1; curJ = 1; k=0; count = 0;
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
				board[i][j]=" ";
		}
	}

};