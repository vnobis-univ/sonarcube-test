#pragma once
#include  "View.h"
#include <string>
using namespace std;

class StartView : public View
{
	string options[3];
	int selected;
public:
	StartView();
	void draw();
	View* handle();	
};