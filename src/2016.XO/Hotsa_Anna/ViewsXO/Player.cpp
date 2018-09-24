#include "Player.h"
#include <fstream>
#include "ExternVar.h"

Player::Player() {}
Player::Player(string _name, int _score) : name(_name), score(_score) {}

int Player::getScore()
{
	return score;
}

string Player::getName()
{
	return name;
}

istream & operator >>(istream & in, Player & player)
{
	in >> player.name >> player.score;
	return in;
}

ostream & operator <<(ostream & out, Player & player)
{
	out << player.name << "      " << player.score << endl;
	return out;
}

void readPlayersList()
{
	ifstream in("ScoresList.txt");
	for (int i = 0; i < 5; i++)
	{
		in >> playersList[i];
	}
}
