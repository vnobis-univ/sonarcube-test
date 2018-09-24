#pragma once

class GameLogic
{
public:
	enum class Difficulty
	{
		easy,
		medium,
		hard
	};

private:
	static Difficulty gameDifficulty;

	unsigned score;
	unsigned HPLeft;

public:
	GameLogic();

	unsigned getScore() const;

	unsigned getHPLeft() const;

	void setGameDifficulty(Difficulty);

	Difficulty getGameDifficulty() const;
	
	void increaseScore();

	void increaseHP();

	void decreaseHP();
};

