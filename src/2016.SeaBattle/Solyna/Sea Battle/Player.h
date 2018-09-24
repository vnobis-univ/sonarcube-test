#pragma once
#include "functions.h"
#include <string>
#include "globals.h"

using namespace std;

class Player
{
	string name;
	int score;
public:
	Player();
	Player(string _name, int _score);
	friend istream & operator >> (istream &is, Player &player);
	friend ostream & operator <<(ostream &os, const Player & player);
	void setName(string _name);
	void print(int line, Printer &p);
	bool operator > (const Player & player);
};

