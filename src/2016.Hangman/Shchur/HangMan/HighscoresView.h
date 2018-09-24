#pragma once
#include "View.h"
#include "Lokalization.h"
#include "StartView.h"
#include <fstream>


using namespace std;

struct Result
{
	string name;
	short score;
	string level;
	//bool operator>(Result&);
	friend istream& operator>>(istream&, Result&);
	friend ostream& operator<<(ostream&, const Result&);
};
class HighscoresView : public View
{
	Result result[10];
	Lokalization language;
	Complexity complexity;
public:
	HighscoresView(Lokalization, Complexity);
	void draw();
	View *handle();
};

bool isInTable(short);
void putInTable(Result, Result[], ofstream&);
string complexityUa(string);