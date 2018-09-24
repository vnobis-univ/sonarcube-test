#include <Windows.h>
#include "MenuEN.h"
#include <iostream>
#include <conio.h>
#include "Field.h"
#include "Score.h"
using namespace std;




extern void gotoXY( int x, int y )
{
	HANDLE hConOut;
	hConOut = GetStdHandle( STD_OUTPUT_HANDLE );
	COORD pos;

	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition( hConOut, pos );
}

extern void SetColors(int text, int background) 
{
	HANDLE hConOut;
	hConOut = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute(hConOut, background * 16 + text);
}

MenuEN::MenuEN()
{
	menu[0] = "Start";
	menu[1] = "Result";
	menu[2] = "Exit";
	sel=1;
}

void MenuEN::print()
{
	SetColors(4,8);
	gotoXY(35,10);
	cout<<menu[0];
	SetColors(7,8);
	gotoXY(35,11);
	cout<<menu[1];
	gotoXY(35,12);
	cout<<menu[2];

	while (true) 
	{ 
		int k;
		k = _getch(); 
		if (k == 224) 
		{ 
			k = _getch(); 
		} 
		switch(k)
		{
		case 80:
			{
				if(sel==1)
				{
					SetColors(7,8);
					gotoXY(35,10);
					cout<<menu[0];
					SetColors(4,8);
					gotoXY(35,11);
					cout<<menu[1];
					gotoXY(35,12);
					SetColors(7,8);
					cout<<menu[2];
					sel=2;break;

				}
				if(sel==2)
				{
					SetColors(7,8);
					gotoXY(35,10);
					cout<<menu[0];
					SetColors(7,8);
					gotoXY(35,11);
					cout<<menu[1];
					gotoXY(35,12);
					SetColors(4,8);
					cout<<menu[2];
					sel=3;break;
				}
				if(sel==3)
				{
					SetColors(4,8);
					gotoXY(35,10);
					cout<<menu[0];
					SetColors(7,8);
					gotoXY(35,11);
					cout<<menu[1];
					gotoXY(35,12);
					SetColors(7,8);
					cout<<menu[2];
					sel=1;break;
				}
			}//80
		case 72:
			{
				if(sel==3)
				{
					SetColors(7,8);
					gotoXY(35,10);
					cout<<menu[0];
					SetColors(4,8);
					gotoXY(35,11);
					cout<<menu[1];
					gotoXY(35,12);
					SetColors(7,8);
					cout<<menu[2];
					sel=2;break;
				}
				if(sel==2)
				{
					SetColors(4,8);
					gotoXY(35,10);
					cout<<menu[0];
					SetColors(7,8);
					gotoXY(35,11);
					cout<<menu[1];
					gotoXY(35,12);
					SetColors(7,8);
					cout<<menu[2];
					sel=1;break;
				}
				if(sel==1)
				{
					SetColors(7,8);
					gotoXY(35,10);
					cout<<menu[0];
					SetColors(7,8);
					gotoXY(35,11);
					cout<<menu[1];
					gotoXY(35,12);
					SetColors(4,8);
					cout<<menu[2];
					sel=3;break;
				}
			}//72
		case 13:
			{
				if(sel==1)
				{
					Field game;
					game.main();
					break;
				}
				if(sel==2)
				{
					Score temp;
					temp.draw();
					break;
				}
				if(sel==3)
				{
					exit(0);
				}
			}//13

		}
	}
}