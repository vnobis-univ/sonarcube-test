#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>

using namespace std;
extern int Lang;
class LevelMenu
{
	string* Selector;
	short curI = 0;
	int k = 0;
public:
	LevelMenu();
	void Selected();
	void draw();
};
