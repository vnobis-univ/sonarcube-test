#pragma once
#include "View.h"
#include <iostream>
#include <windows.h>
using namespace std;

void printInTheCentre(string str, int numberOfLine, int consoleWidth);
class HighScoresView : public View
{
	Scores arr[5];
public:
	HighScoresView();
	void draw();
	View * handle();
};

