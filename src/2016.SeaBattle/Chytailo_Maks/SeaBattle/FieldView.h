#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

extern int mypole[10][10];
extern int pole[10][10];
extern int first;

class FieldView
{
	int f, e, i, j, x, y, nap, u, ui, w;
	int ud[2], hod[1];
	int comp(int pole[10][10], int, int ud[2], int hod[1]);
	int player(int pole[10][10], int);
public:
	int AutoPosShips(int pole[10][10]);
	int ManPosShips(int mypole[10][10]);
	void Game();
};

