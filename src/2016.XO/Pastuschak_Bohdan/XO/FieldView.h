#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include "Color.h"
#include "View.h"
using namespace std;

class FieldView : public View{
public:
	int currentCell;
	int currentScore;
	bool* isEmpty;
	bool* isX;
	bool* isO;
	bool botWin;
	bool playerWin;
public:
	FieldView(){
		currentCell = 0, currentScore = 0, botWin = false, playerWin = false, isEmpty = new bool[9], isX = new bool [9], isO = new bool [9];
		for (size_t i = 0; i < 9; ++i)
		{
			isEmpty[i] = true; 
			isO[i] = false;
			isX[i] = false;
		}
	} 
	
	FieldView(int y){
		currentCell = 0;
		currentScore = y;
		botWin = false;
		playerWin = false;
		isEmpty = new bool[9];
		isX = new bool [9];
		isO = new bool [9];

		for (size_t i = 0; i < 9; ++i)
		{
			isEmpty[i] = true; 
			isO[i] = false;
			isX[i] = false;
		}
	}

	void draw(int x[5], int b[4]){
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, Purple);
		
		for (size_t i = 0; i < 5; ++i)
			cout<<endl;
		
		POINT op;
		HWND hWnd=GetConsoleWindow();
		HDC hDC=GetDC(hWnd);
		HPEN hPenBLUE = CreatePen(PS_SOLID, 0, RGB(0,0,255));
		SelectObject(hDC,hPenBLUE);
				
		//draw 9 squares in console
		
		MoveToEx(hDC,350,200,&op);
		LineTo(hDC,650,200);
				
		MoveToEx(hDC,350,500,&op);
		LineTo(hDC,650,500);
							
		MoveToEx(hDC,350,200,&op);
		LineTo(hDC,350,500);	

		MoveToEx(hDC,650,200,&op);
		LineTo(hDC,650,500);

		MoveToEx(hDC,350,300,&op);
		LineTo(hDC,650,300);

		MoveToEx(hDC,350,400,&op);
		LineTo(hDC,650,400);

		MoveToEx(hDC,450,200,&op);
		LineTo(hDC,450,500);

		MoveToEx(hDC,550,200,&op);
		LineTo(hDC,550,500);		
		
		HPEN hPenYELLOW = CreatePen(PS_SOLID, 0, RGB(255,255,0));
		SelectObject(hDC,hPenYELLOW);
		
		switch (currentCell)
		{
		case 0:
			{
				MoveToEx(hDC,350,200,&op);
				LineTo(hDC,350,300);
				MoveToEx(hDC,350,200,&op);
				LineTo(hDC,450,200);
				MoveToEx(hDC,450,200,&op);
				LineTo(hDC,450,300);
				MoveToEx(hDC,450,300,&op);
				LineTo(hDC,350,300);
				break;
			}

		case 1:
		{
				MoveToEx(hDC,450,200,&op);
				LineTo(hDC,550,200);
				MoveToEx(hDC,450,200,&op);
				LineTo(hDC,450,300);
				MoveToEx(hDC,550,300,&op);
				LineTo(hDC,550,200);
				MoveToEx(hDC,550,300,&op);
				LineTo(hDC,450,300);
				break;
		}

		case 2:
			{
				MoveToEx(hDC,550,200,&op);
				LineTo(hDC,650,200);
				MoveToEx(hDC,550,200,&op);
				LineTo(hDC,550,300);
				MoveToEx(hDC,650,300,&op);
				LineTo(hDC,550,300);
				MoveToEx(hDC,650,300,&op);
				LineTo(hDC,650,200);
				break;
			}

		case 3:
			{
				MoveToEx(hDC,350,400,&op);
				LineTo(hDC,450,400);
				MoveToEx(hDC,350,400,&op);
				LineTo(hDC,350,300);
				MoveToEx(hDC,450,300,&op);
				LineTo(hDC,350,300);
				MoveToEx(hDC,450,300,&op);
				LineTo(hDC,450,400);
				break;
			}

		case 4:
			{
				MoveToEx(hDC,550,400,&op);
				LineTo(hDC,450,400);
				MoveToEx(hDC,550,400,&op);
				LineTo(hDC,550,300);
				MoveToEx(hDC,450,300,&op);
				LineTo(hDC,450,400);
				MoveToEx(hDC,450,300,&op);
				LineTo(hDC,550,300);
				break;
			}

		case 5:
			{
				MoveToEx(hDC,550,300,&op);
				LineTo(hDC,550,400);
				MoveToEx(hDC,550,300,&op);
				LineTo(hDC,650,300);
				MoveToEx(hDC,650,400,&op);
				LineTo(hDC,650,300);
				MoveToEx(hDC,650,400,&op);
				LineTo(hDC,550,400);
				break;
			}

		case 6:
			{
				MoveToEx(hDC,350,400,&op);
				LineTo(hDC,350,500);
				MoveToEx(hDC,350,400,&op);
				LineTo(hDC,450,400);
				MoveToEx(hDC,450,500,&op);
				LineTo(hDC,450,400);
				MoveToEx(hDC,450,500,&op);
				LineTo(hDC,350,500);
				break;
			}

		
		case 7:
			{
				MoveToEx(hDC,450,400,&op);
				LineTo(hDC,450,500);
				MoveToEx(hDC,450,400,&op);
				LineTo(hDC,550,400);
				MoveToEx(hDC,550,500,&op);
				LineTo(hDC,550,400);
				MoveToEx(hDC,550,500,&op);
				LineTo(hDC,450,500);
				break;
			}

		case 8:
			{
				MoveToEx(hDC,550,400,&op);
				LineTo(hDC,550,500);
				MoveToEx(hDC,550,400,&op);
				LineTo(hDC,650,400);
				MoveToEx(hDC,650,500,&op);
				LineTo(hDC,650,400);
				MoveToEx(hDC,650,500,&op);
				LineTo(hDC,550,500);
				break;
			}
		}

		HPEN hPenRED = CreatePen(PS_SOLID, 2, RGB(255,0,0));
		SelectObject(hDC,hPenRED);

		if (playerWin == false && botWin == false){

		for (size_t i = 0; i < 5; ++i){
			switch(x[i]){
			case 0:
				{
					MoveToEx(hDC,350,200,&op);
					LineTo(hDC,450,300);
					MoveToEx(hDC,350,300,&op);
					LineTo(hDC,450,200);
					break;
				}
			
			case 1:
				{
					MoveToEx(hDC,450,200,&op);
					LineTo(hDC,550,300);
					MoveToEx(hDC,450,300,&op);
					LineTo(hDC,550,200);
					break;
				}

			case 2:
				{
					MoveToEx(hDC,550,200,&op);
					LineTo(hDC,650,300);
					MoveToEx(hDC,550,300,&op);
					LineTo(hDC,650,200);
					break;
				}

			case 3:
				{
					MoveToEx(hDC,350,300,&op);
					LineTo(hDC,450,400);
					MoveToEx(hDC,450,300,&op);
					LineTo(hDC,350,400);
					break;
				}

			case 4:
				{
					MoveToEx(hDC,450,300,&op);
					LineTo(hDC,550,400);
					MoveToEx(hDC,550,300,&op);
					LineTo(hDC,450,400);
					break;
				}

			case 5:
				{
					MoveToEx(hDC,550,300,&op);
					LineTo(hDC,650,400);
					MoveToEx(hDC,650,300,&op);
					LineTo(hDC,550,400);
					break;
				}

			case 6:
				{
					MoveToEx(hDC,350,400,&op);
					LineTo(hDC,450,500);
					MoveToEx(hDC,350,500,&op);
					LineTo(hDC,450,400);
					break;
				}

			case 7:
				{
					MoveToEx(hDC,450,400,&op);
					LineTo(hDC,550,500);
					MoveToEx(hDC,450,500,&op);
					LineTo(hDC,550,400);
					break;
				}

			case 8:
				{
					MoveToEx(hDC,550,400,&op);
					LineTo(hDC,650,500);
					MoveToEx(hDC,550,500,&op);
					LineTo(hDC,650,400);
					break;
				}
			}

			isX[x[i]] = true;
			if (isX[0] == true && isX[1] == true && isX[2] == true) playerWin = true;
			if (isX[0] == true && isX[3] == true && isX[6] == true) playerWin = true;
			if (isX[3] == true && isX[4] == true && isX[5] == true) playerWin = true;
			if (isX[6] == true && isX[7] == true && isX[8] == true) playerWin = true;
			if (isX[1] == true && isX[4] == true && isX[7] == true) playerWin = true;
			if (isX[2] == true && isX[5] == true && isX[8] == true) playerWin = true;
			if (isX[0] == true && isX[4] == true && isX[8] == true) playerWin = true;
			if (isX[2] == true && isX[4] == true && isX[6] == true) playerWin = true;
		}
		}
		
		HPEN hPenGREEN = CreatePen(PS_SOLID, 0, RGB(0,255,0));
		SelectObject(hDC,hPenGREEN);
		
		if (playerWin == false && botWin == false){
			for (size_t i = 0; i < 4; ++i)
			{
				switch (b[i]){
				case 0:	Ellipse(hDC, 350, 200, 450, 300); break;
				case 1:	Ellipse(hDC, 450, 200, 550, 300); break;
				case 2:	Ellipse(hDC, 550, 200, 650, 300); break;
				case 3:	Ellipse(hDC, 350, 300, 450, 400); break;
				case 4:	Ellipse(hDC, 450, 300, 550, 400); break;
				case 5:	Ellipse(hDC, 550, 300, 650, 400); break;
				case 6:	Ellipse(hDC, 350, 400, 450, 500); break;
				case 7:	Ellipse(hDC, 450, 400, 550, 500); break;
				case 8:	Ellipse(hDC, 550, 400, 650, 500); break;
				}
								
				isO[b[i]] = true;
				if (isO[0] == true && isO[1] == true && isO[2] == true) botWin = true;
				if (isO[0] == true && isO[3] == true && isO[6] == true) botWin = true;
				if (isO[3] == true && isO[4] == true && isO[5] == true) botWin = true;
				if (isO[6] == true && isO[7] == true && isO[8] == true) botWin = true;
				if (isO[1] == true && isO[4] == true && isO[7] == true) botWin = true;
				if (isO[2] == true && isO[5] == true && isO[8] == true) botWin = true;
				if (isO[0] == true && isO[4] == true && isO[8] == true) botWin = true;
				if (isO[2] == true && isO[4] == true && isO[6] == true) botWin = true;
			}
		}
			ReleaseDC(hWnd,hDC);
		
	}
};