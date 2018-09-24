#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>


class WhoFirst
{
	std::string* Selector;
	short curI = 0;
	int k = 0;
public:
	WhoFirst();
	void Selected();
	void draw();
};

