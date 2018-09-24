#pragma once
#include "View.h"
#include "LevelOptions.h"
#include "TranslationService.h"
#include <string>
using namespace std;
class ResultView :
	public View
{
private:
	TranslationService service;
	LevelOptions level;
	char* ukrLetters;
	string name = "";
	bool nameEntered = false;
	int count = 0;
	int score;
	int guessedLetters;
	bool hasAchievedHighscore();
	void setUkrLetters();
	bool isUkrLetter(char c);
public:
	ResultView();
	ResultView(LevelOptions level, int score, int letters);
	void draw();
	View* handle();

};

