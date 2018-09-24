#include "Player.h"



Player::Player() : name(""), score(0), guessedLetters(0)
{
}

Player::Player(string _name, int _score, int _guessedLetters):
	name(_name), score(_score), guessedLetters(_guessedLetters)
{
}

string Player::getName() const
{
	return name;
}

int Player::getScore() const
{
	return score;
}

void Player::setName(string _name)
{
	name = _name;
}

int Player::getGuessedLetters() const
{
	return guessedLetters;
}


bool Player::operator > (const Player & player)
{
	if(score != player.score)
	{ 
		return score > player.score;
	}
	else
	{
		return guessedLetters > player.guessedLetters;
	}
}

ostream & operator <<(ostream & os, const Player & player)
{
	os << player.name << " " << player.score << " " << player.guessedLetters;
	return os;
}

istream & operator >> (istream & is, Player & player)
{
	is >> player.name >> player.score >> player.guessedLetters;
	return is;
}
