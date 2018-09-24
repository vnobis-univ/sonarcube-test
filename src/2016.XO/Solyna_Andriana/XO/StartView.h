#pragma once
#include "View.h"
#include <windows.h>
#include <string>
#include <conio.h>
using namespace std;

void printInTheCentre(string str, int numberOfLine, int consoleWidth);

class StartView: public View
{
	string *arr;
	string selected;
	View * nextView();
	string getSelected()const;
public:
	StartView();
	//string getSelected()const;
	void draw();
	//View * nextView();
	View * handle();
};
