#pragma once
#include <string>
using namespace std;

class Player
{
private:
	string name;
	int score;
public:
	Player();
	Player(string name, int score);
	Player(Player& player);
	int getScore();
	string getName();
	friend istream& operator >> (istream& in, Player& player);
	friend ostream& operator << (ostream& out, Player& player);
};

