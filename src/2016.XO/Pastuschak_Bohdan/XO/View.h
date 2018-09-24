#pragma once
#include <Windows.h>

class View{
public:
	void clean(){
		system("cls");
	}

	void draw(){
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}
};