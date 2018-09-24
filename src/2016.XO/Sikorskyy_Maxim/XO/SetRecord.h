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
	Result arr[hsSize + 1];
	void Sort();
public:
	SavingWinners();
	bool isHigh(int _score);
	void save(const Result & r);
	Result operator[](int i) const;
	void loadScores();
};
extern SavingWinners buff;
