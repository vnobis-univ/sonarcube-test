#include "GameLogic.h"
#include "Game.h"

GameLogic::Difficulty GameLogic::gameDifficulty = Difficulty::easy;

GameLogic::GameLogic():
	score(0)
{
	switch (gameDifficulty)
	{
	case Difficulty::easy: 	
		HPLeft = 20;
		break;
	case Difficulty::medium:
		HPLeft = 18;
		break;
	case Difficulty::hard:
		HPLeft = 16;
		break;
	}
}

unsigned GameLogic::getScore() const
{
	return score;
}

unsigned GameLogic::getHPLeft() const
{
	return HPLeft;
}

void GameLogic::setGameDifficulty(Difficulty newDifficulty)
{
	gameDifficulty = newDifficulty;
}

GameLogic::Difficulty GameLogic::getGameDifficulty() const
{
	return gameDifficulty;
}

void GameLogic::increaseScore()
{
	++score;
}

void GameLogic::increaseHP()
{
	switch (gameDifficulty)
	{
	case GameLogic::Difficulty::easy:
		HPLeft += 10;
		break;

	case GameLogic::Difficulty::medium:
		HPLeft += 10;
		break;

	case GameLogic::Difficulty::hard:
		HPLeft += 10;
		break;

	default:
		throw std::string("Problem in GameLogic::increaseScore");
	}
}

void GameLogic::decreaseHP()
{
	--HPLeft;
}