#include "Player.h"
#include <string>
using namespace std;

Player::Player() : score(0)
{
}

Player::Player(string _name, int _score) : name(_name), score(_score)
{
}

Player::Player(Player& player) : name(player.name), score(player.score)
{
}

int Player::getScore() const
{
	return score;
}

string Player::getName()
{
	return name;
}

istream& operator >> (istream& in, Player& player)
{
	in >> player.name >> player.score;
	return in;
}

ostream& operator << (ostream& out, Player& player)
{
	out << player.name << " " << player.score << " " << endl;
	return out;
}
