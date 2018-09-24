#pragma once
#include "View.h"
#include "StartView.h"
#include <fstream>
#include <iostream>

using namespace std;

struct Result
{
	string name;
	short score;
	friend istream& operator >> (istream&, Result&);
	friend ostream& operator<<(ostream&, const Result&);
};
class HighscoresView : public View
{
	Result result[10];
public:
	HighscoresView();
	void draw();
	View *handle();
};

bool isInTable(short);
void putInTable(Result, Result[], ofstream&);