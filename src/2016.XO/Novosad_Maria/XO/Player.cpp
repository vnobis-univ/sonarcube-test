#include "Player.h"

Player::Player(){}
Player::Player(string name, int score) : name(name), score(score){}
Player::Player(Player& player)
{
	name = player.name;
	score = player.score;
}
int Player::getScore()
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
	out << player.name << " " << player.score << endl;
	return out;
}