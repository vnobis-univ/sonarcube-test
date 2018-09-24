#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
extern int Lang;

using namespace std;

class MainMenu
{
	string* Selector;
	short curI = 0;
	int k = 0;
public:
	MainMenu();
	void Selected();
	void draw();
};
