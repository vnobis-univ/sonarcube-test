#pragma once
#include "View.h"
#include <fstream>

struct Result
{
	string name;
	short score;
	friend istream& operator>>(istream&, Result&);
	friend ostream& operator<<(ostream&, const Result&);
};

class HighScoresView : public View
{
private:
	Result result[10];
public:
	HighScoresView();
	void draw();
	View *handle();
};

bool inTable(short);
void writeIn(Result, Result[], ofstream&);