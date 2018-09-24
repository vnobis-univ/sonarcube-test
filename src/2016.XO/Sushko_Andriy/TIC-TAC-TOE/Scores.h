#pragma once
#include "View.h"
#include <vector>
#include <algorithm>
#include <iostream>

using std::ostream;
using std::vector;

struct hightScore
{
	hightScore(string s = " ", int i = -1);

	string name;
	int score;

	friend istream& operator >>(istream& is, hightScore& obj);
	friend ostream& operator <<(ostream& os, const hightScore& obj);

	bool operator<(const hightScore& object) const;
};

bool validateName(string name);