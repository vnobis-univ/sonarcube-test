#pragma once
#include <string>
#include <vector>
#include "ConsoleUtils.h"

using std::string; using std::vector;

struct HScore {

	string name;
	int score;

	HScore(string = "", int = 0);

	friend std::istream& operator >> (std::istream& is, HScore& obj);
};

class HScoreManager {

	vector<HScore>easy;
	vector<HScore>norm;
	vector<HScore>hard;
public:
	HScoreManager();

	vector<HScore> getHScore(Difficulty lvl);
	void update(Difficulty lvl, HScore upd);
};