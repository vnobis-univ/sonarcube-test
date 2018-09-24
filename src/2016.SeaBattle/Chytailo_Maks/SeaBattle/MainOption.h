#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>


class MainOption
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo;
	std::string* Selector;
	short curI = 0;
	int k = 0;
public:
	

	MainOption();
	void Selected();
	void draw();
};

