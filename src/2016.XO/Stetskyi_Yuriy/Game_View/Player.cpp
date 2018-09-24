#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "Player.h"

using namespace std;

Player::Player(string n, int s)
	: nickname(n), score(s)
{
}

int Player::getScore() const
{ 
	return score; 
}

void Player::setScore(int s) 
{ 
	score = s;
}

string Player::getNickname() const 
{ 
	return nickname; 
}

Player& Player::operator=(const Player& p)
{
	if (this != &p)
	{
		nickname = p.nickname;
		score = p.score;
	}
	return *this;
}

istream& operator>>(istream& in, Player& p)
{
	in >> p.nickname >> p.score;
	return in;
}

ostream& operator<<(ostream& out, const Player& p)
{
	out << p.nickname << " " << p.score;
	return out;
}