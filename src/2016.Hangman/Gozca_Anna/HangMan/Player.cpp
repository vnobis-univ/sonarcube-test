#include "Player.h"
#include <fstream>
int numOfPlayers = 12;
Player * playersList = new Player[numOfPlayers];

Player::Player() {}
Player::Player(string _name, string _level, int _score, int _guessedLetters) : name(_name),
level(_level), score(_score), guessedLetters(_guessedLetters) {}

int Player::getScore()
{
	return score;
}

int Player::getGuessedLetters()
{
	return guessedLetters;
}

string Player::getName()
{
	return name;
}

string Player::getLevel()
{
	return level;
}
istream & operator >>(istream & in, Player & player)
{
	in >> player.name >> player.level >> player.score >> player.guessedLetters;
	return in;
}

ostream & operator <<(ostream & out, Player & player)
{
	out << player.name << "      " << player.level << "      "
		<< player.score <<"      " << player.guessedLetters << endl;
	return out;
}

void readPlayersList()
{
	ifstream in("ScoresList.txt");
	for (int i = 0; i < numOfPlayers; i++)
	{
		in >> playersList[i];
	}
}
