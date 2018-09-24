#pragma once
#include <string>
#include "LevelOptions.h"
using namespace std;
class Player
{
private:
	string name;
	LevelOptions level;
	int score;
	int guessedLetters;
public:
	Player();
	Player(string name, LevelOptions level, int score, int guessedLetters);
	Player(Player& player);
	int getScore();
	string getName();
	LevelOptions getLevel();
	int getGuessedLetters();
	bool operator > (Player& player);
	friend istream& operator >> (istream& in, Player& player);
	friend ostream& operator << (ostream& out, Player& player);
};

