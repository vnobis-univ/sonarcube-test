#pragma once

#include <iostream>
#include <string>
#include "GlobalVars.h"
using namespace std;

class Player
{
	string name;
	int score;
public:
	Player();
	Player(string _name, int _score);
	int getScore();
	string getName();

	friend istream & operator >>(istream & in, Player & player);
	friend ostream & operator <<(ostream & out, Player & player);
};

void readPlayersList(Language lang);
extern int numOfPlayers;
extern Player * playersList;