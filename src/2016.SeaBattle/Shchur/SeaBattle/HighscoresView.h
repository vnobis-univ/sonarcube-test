#pragma once
#include "View.h"
#include "Lokalization.h"
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
	Lokalization language;
public:
	HighscoresView(Lokalization);
	void draw();
	View *handle();
};

bool isInTable(short);
void putInTable(Result, Result[], ofstream&);