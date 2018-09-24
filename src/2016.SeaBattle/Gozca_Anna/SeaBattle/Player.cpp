#include "Player.h"
#include <fstream>
int numOfPlayers = 5;
Player * playersList = new Player[numOfPlayers];

Player::Player() {}
Player::Player(string _name,int _score) : name(_name),score(_score) {}

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
	in >> player.name >> player.score ;
	return in;
}

ostream & operator <<(ostream & out, Player & player)
{
	out << player.name << player.score << endl;
	return out;
}

void readPlayersList(Language lang)
{
	if (lang == Language::ENGLISH)
	{
		ifstream in("HighScores.txt");
		for (int i = 0; i < numOfPlayers; i++)
		{
			in >> playersList[i];
		}
	}
	else
	{
		ifstream ik("Рекорди.txt");
		for (int i = 0; i < numOfPlayers; i++)
		{
			ik >> playersList[i];
		}
	}
}