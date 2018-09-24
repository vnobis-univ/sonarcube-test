#include "Player.h"



Player::Player(): 
	name(""),
	score(0)
{
}

Player::Player(string _name, int _score):
	name(_name),
	score(_score)
{
}


void Player::setName(string _name)
{
	name = _name;
}

void Player::print(int line, Printer &p)
{
	setCursoreAtPosition(30, line);
	p.print(name);
	setCursoreAtPosition(50, line);
	p.print(to_string(score));
}

bool Player::operator>(const Player & player)
{
	return score > player.score;
}

istream & operator >> (istream & is, Player & player)
{
	is >> player.name >> player.score;
	return is;
}

ostream & operator<<(ostream & os, const Player & player)
{
	os << player.name << " " << player.score << endl;
	return os;
}
