#pragma once
#include "View.h"
#include "LevelOptions.h"
#include "Dictionary.h"
#include "Word.h"
#include "TranslationService.h"
class GameView :
	public View
{
private:
	TranslationService service;
	LevelOptions level;
	Word currentWord;
	int guessedLetters = 0;
	Dictionary dictionary;
	int amountOfLettersInAlphabet = 26;
	const static int amountOfWords = 20;
	bool usedIndexes[amountOfWords];
	bool* usedLetters;
	int score = 0;
	int triesLeft = 12;
	char* alphabet;
	void changeVisibility(int index, char symbol);
	void setUkrainianAlphabet();
	int getIndexOfUkrLetter(char c);
	bool hasGuessed(char symbol);
	bool letterAlreadyUsed(int index);
	bool userLost();
	bool userWon();
	void drawMan();
	void drawAlphabet();
	void setCurrentWord();
public:
	GameView();
	GameView(LevelOptions _level);
	GameView(int score);
	void draw();
	View* handle();
};

