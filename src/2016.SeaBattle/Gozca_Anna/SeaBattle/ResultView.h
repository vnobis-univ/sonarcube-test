#pragma once
#include "View.h"
#include "GlobalVars.h"
#include "Player.h"
#include <fstream>

class ResultView :public View
{
private:
	int score;
	Language language;
	string playerName;
	bool isNameEntered;
	int counter;
	void listWithNew(Player& gamer1);
public:
	ResultView();
	ResultView(int _score, Language _language);
	bool hasAchievedHighscore();
	void printLogo();
	void draw();
	View* handle();
};