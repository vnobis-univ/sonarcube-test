#pragma once
#include "View.h"
#include <conio.h>
#include "StartView.h"
#include "FieldView.h"

using namespace std;
class ComplexityView: public View
{
	string options[3] = {"Easy", "Medium", "Hard"};
	short position = 0;
public:
	void draw();
	View* handle();
	void printMenu();
};