#pragma once
#include "View.h"
#include "TranslationService.h"
#include "Player.h"

using namespace std;

class ResultView : public View
{
	TranslationService service;
	int score;
	string name = "";
	int* ukrLetters;
	bool nameEntered = false;
	bool hasAchievedHighscore();
	void returnNewHighscoresList(Player& player);
	void swap(Player& a, Player& b);
	void setUkrLetters();
	bool isUkrLetter(char c);
public:
	ResultView(int score);
	void draw() override;
	View* handle() override;
};

