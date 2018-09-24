#pragma once
#include <string>

using namespace std;

class Player
{
	string name;
	int score;
	int guessedLetters;
public:
	Player();
	Player(string _name, int _score, int _guessedLetters);
	string getName() const;
	int getScore() const;
	void setName(string _name);
	int getGuessedLetters() const;
	friend ostream & operator << (ostream & os, const Player & player);
	bool operator > (const Player & player);
	friend istream & operator >> (istream & is, Player & player);
};

