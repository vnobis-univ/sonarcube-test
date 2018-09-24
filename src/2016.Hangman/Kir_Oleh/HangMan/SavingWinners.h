#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "OptionModes.h"

using namespace::std;

static const int hsSize = 5;

extern string sexes[2];
extern string diffModes[3];

struct Result
{
public:
	string name;
	int scores;
	int letters;
	Sex sex;
	DifficultyModes mode;
	friend istream & operator>>(istream & in, Result & r);
	friend ostream & operator<<(ostream & out, const Result & r);
};

class SavingWinners
{
	static const int hsSize = 5;
	ifstream in;
	ofstream out;
	Result arr[hsSize + 1];//one additional place to save new result
	void Sort();
public:
	SavingWinners();
	bool isHighEnough(int _score, int _letters);
	void save(const Result & r);
	Result operator[](int i) const;
	void loadHighScores();
};

extern SavingWinners saver;