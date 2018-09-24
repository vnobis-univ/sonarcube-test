#include "Player.h"
#include "Globals.h"

Player::Player()
{
}

Player::Player(string name, LevelOptions level, int score, int guessedLetters) :
	name(name),
	level(level),
	score(score),
	guessedLetters(guessedLetters)
{
}

Player::Player(Player& player)
{
	name = player.name;
	level = player.level;
	score = player.score;
	guessedLetters = player.guessedLetters;
}

int Player::getScore()
{
	return score;
}

string Player::getName()
{
	return name;
}

LevelOptions Player::getLevel()
{
	return level;
}

int Player::getGuessedLetters()
{
	return guessedLetters;
}

LevelOptions convertToLevelOptions(string text)
{
	if (text == "Easy")
	{
		return LevelOptions::Easy;
	}
	else if (text == "Middle")
	{
		return LevelOptions::Middle;
	}
	else
	{
		return LevelOptions::Hard;
	}
}

bool Player:: operator > (Player& player)
{
	if ((int)level > (int)player.getLevel())
	{
		return true;
	}
	else if ((int)level < (int)player.getLevel())
	{
		return false;
	}
	else
	{
		if (score > player.getScore())
		{
			return true;
		}
		else if (score < player.getScore())
		{
			return false;
		}
		else
		{
			if (guessedLetters > player.getGuessedLetters())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

istream& operator >> (istream& in, Player& player)
{
	string text;
	in >> player.name >> text >>  player.score >> player.guessedLetters;
	player.level = convertToLevelOptions(text);
	return in;
}

ostream& operator << (ostream& out, Player& player)
{
	out << player.name << " " << convertToString(player.level) << " " << player.score << " " << player.guessedLetters << endl;
	return out;
}
