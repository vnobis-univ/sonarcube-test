#pragma once
#include <fstream>
#include <string>

using namespace::std;

static const int hsSize = 5;

enum class DifficultyModes{ Easy, Medium, Hard };

extern DifficultyModes currMode;






extern string diffModes[3];

struct Result
{
public:
	string name;
	int scores;
	int letters;
	
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