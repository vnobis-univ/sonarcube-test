#pragma once
#include "GameLogic.h"
#include "GameField.h"

class GameLogicComputer: public GameLogic
{
public:
	enum class Difficulty
	{
		easy,
		hard
	};

private:
	static Difficulty gameDifficulty;

	int score;

public:
	GameLogicComputer(COORD);

	bool handlePlayerChoice(int, int, bool&, bool&);

	bool handleOponentChoice(GameField&, bool&);

	int getScore();

	friend void setGameDifficulty(Difficulty);

	friend int getGameDifficulty();

	friend void redrawScore(int);

	bool isOnlineJoinedGame() const;

private:
	bool searchForPossibleAround(GameField&, std::pair<int, int>&, int, int, int = -1, int = -1);
};

