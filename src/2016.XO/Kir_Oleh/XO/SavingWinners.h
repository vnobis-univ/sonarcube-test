#pragma once
#include <fstream>
#include <string>

using namespace::std;

static const int hsSize = 5;

struct Result
{
public:
	string name;
	int scores;
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
	bool isHighEnough(int _score);
	void save(const Result & r);
	Result operator[](int i) const;
	void loadHighScores();
};

extern SavingWinners saver;