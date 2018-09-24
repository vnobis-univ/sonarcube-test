#pragma once

#include "Player.h"
#include "View.h"

using namespace std;

class ResultView : public View
{
	Result hasAchievedHighScore;
	int score;
	int highScore;
	Player* records;
	int playersNumber;

public:
	ResultView(Result = Result::DEFEAT);

	int getScore() const;
	int getHighScore() const;
	int getPlayersNumber() const;

	Player& operator[](int);
	const Player& operator[](int) const;

	void setResult(Result);
	void setHighScore(int);
	void setNumOfRecords(int);
	void sortPlayers();
	void defineResult();

	string getUserNick();

	void draw();
	~ResultView();
};