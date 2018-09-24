#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "Score.h"
#include "Field.h"
#include "Main.h"

using namespace std;

class StartView: public Head
{
private:
	HANDLE hStdOut;
	int f;
	string ofmenu[4][80];
	void SetColor(int text, int background);
	
	string menu[3]; int a;
	void gotoxy(int x,int y);


public:
	StartView();
	void Draw();
};