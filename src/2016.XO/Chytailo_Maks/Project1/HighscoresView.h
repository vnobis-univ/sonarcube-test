#pragma once
#include <iostream>
#include <string>
#include "View.h"

using namespace std;

class HighscoresView : public View
{
	string name;
	int score;
public:
	HighscoresView() : name("-"), score(0) {}
	HighscoresView(string _name, int _score) : name(_name), score(_score) {}

	friend istream& operator>>(istream& in, HighscoresView& h);
	friend ostream& operator<<(ostream& cout, HighscoresView& h);

	void Draw();
};