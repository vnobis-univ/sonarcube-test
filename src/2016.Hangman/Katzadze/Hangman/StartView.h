#pragma once
#include "View.h"
#include <conio.h>
#include <Windows.h>
#include <string>

using namespace std;

class StartView : public View
{
	

	
	short position;
public:
	StartView();

	void draw();
	void printMenu();

	View* handle();
};