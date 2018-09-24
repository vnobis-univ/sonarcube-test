#pragma once
#include <iostream>
#include <string>
using namespace std;

class Player
{
	string name;
	string level;
	int score;
	int guessedLetters;
public:
	Player();
	Player(string _name, string _level, int _score,	int _guessedLetters);
	int getScore();
	int getGuessedLetters();
	string getName();
	string getLevel();

	friend istream & operator >>(istream & in, Player & player);
	friend ostream & operator <<(ostream & out, Player & player);
};

void readPlayersList();
extern int numOfPlayers;
extern Player * playersList;
