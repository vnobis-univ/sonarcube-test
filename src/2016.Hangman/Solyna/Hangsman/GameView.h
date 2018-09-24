#pragma once
#include "View.h"
#include "ModesView.h"
#include "functions.h"
#include "Dictionary.h"
#include "ResultView.h"

extern int healthPoints;
extern int score;
extern Dictionary dictionary;
extern int guessedLetters;
class GameView :public View
{
	string word;
	string invisibleWord;
	unsigned char *arrayOfLetters;
	unsigned char *arrayOfGuessedLetters;
	unsigned char *arrayOfNotGuessedLetters;
	int counterOfGuessed;
	int counterOfNotGuessed;
	void hasLetter(char ch);
	bool won();
	bool lost();
	void drawHangingMan();
public:
	GameView(Languages l,Difficulty d);
	void draw();
	View * handle();
};

