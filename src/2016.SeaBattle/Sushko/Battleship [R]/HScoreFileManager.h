#pragma once

#include <string>
#include <vector>
#include "ConsoleUtils.h"

using std::string; using std::vector;

struct HScore {

	string name;
	int score;

	HScore(string = "", int = 0);

	bool operator <(const HScore& obj) const;

	friend std::istream& operator >> (std::istream& is, HScore& obj);
};

class HScoreManager {

	vector<HScore>scores;
public:
	HScoreManager();

	vector<HScore> getScores();
	void update(HScore upd);
};