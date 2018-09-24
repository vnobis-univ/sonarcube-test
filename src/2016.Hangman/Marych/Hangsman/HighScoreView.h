#pragma once
#include "View.h"
#include <fstream>

struct Result
{
	string name;
	short score;
	int life;
	string complexity1;
	Result();
	friend istream& operator>>(istream&, Result&);
	friend ostream& operator<<(ostream&, const Result&);
};
class HighscoreView : public View
{
	Result result[10];
	string options[6];
public:
	HighscoreView();
	void setOptions();
	void draw();
	View *handle();
};
bool isInTable(int);
void putInTable(Result, Result[], ofstream&);