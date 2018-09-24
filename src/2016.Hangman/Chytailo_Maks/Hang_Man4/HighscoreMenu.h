#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class HighscoresView 
{
	string name;
	int score;
	int lastCount;
	string level;
public:
	HighscoresView() : name("-"), score(0), lastCount(0), level("-") {}
	HighscoresView(string _name, int _score, int _lastCount, string _level) : name(_name), score(_score), lastCount(_lastCount), level(_level){}

	friend istream& operator>>(istream& in, HighscoresView& h);
	friend ostream& operator<<(ostream& cout, HighscoresView& h);

	void draw();
};
