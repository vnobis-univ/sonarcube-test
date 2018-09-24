#pragma once
#include "View.h"
#include "StartView.h"
#include <fstream>


using namespace std;

struct Result
{
	string name;
	short score;
	string level;
	friend istream& operator>>(istream&, Result&);
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