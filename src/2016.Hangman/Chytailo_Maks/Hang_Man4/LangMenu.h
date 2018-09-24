#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>

using namespace std;
extern int Lang;
class LangMenu
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo;
	string* Selector;
	short curI = 0;
	int k = 0;
public:
	

	LangMenu();
	void Selected();
	void draw();
};

