#pragma once
#include "Player.h"
#include "View.h"
#include "GlobalVar.h"
using namespace std;

extern int numberOfPlayersForLevel;
class ResultView :public View
{
private:
	int score;
	string levelName;
	string playerName;
	bool isNameEntered;
	int counter ;

	int numOfGuessedLet;
public:
	ResultView();
	ResultView(int _score, string _levelName, int _numOfGuessedLet);
	bool hasAchievedHighscore();
	void draw();
	View* handle();
	friend void listWithNew(Player& gamer1);
		
};