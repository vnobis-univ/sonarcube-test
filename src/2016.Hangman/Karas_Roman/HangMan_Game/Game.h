#pragma once
#include "GameTools.h"

class Game{
	int scores;
	string name;
public:
	Game();

	int getScore();
	void setScore(int);

	bool operator>(const Game&)const;
	bool operator<(const Game&)const;

	friend istream& operator>>(istream&, Game&);
	friend ostream& operator<<(ostream&, const Game&);

	void sort(Game*, int, ostream&);
	void draw(bool);
};