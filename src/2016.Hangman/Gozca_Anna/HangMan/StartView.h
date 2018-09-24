#pragma once
#include "View.h"
#include "Printers.h"
#include "ConsoleUtils.h"
#include "GlobalVar.h"
#include <string>
using namespace std;

class StartView : public View
{
	string option[3];
	int selected;
public:
	StartView();
	void draw();
	View * handle();	 
};