#pragma once
#include "StartView.h"
#include "ResultView.h"
#include "Printers.h"
#include "ConsoleUtils.h"
#include "Dictionary.h"
#include "GlobalVar.h"

enum class LetterStates { DEFAULT, INWORD, NOTINWORD};
extern int guessedLetters;

class GameView :public View
{
	LetterStates letters[26];
	string allLetters;
	int numOfSelectedLetter;
	bool isSelected(int i);
	LetterStates getState(int i);
	void drawSelectedLetter(int i, bool isSelect, LetterStates state);
	void printAllLetters();
	Levels level;
	string word;
	string invWord;
	char * arrOfGuessedLet;
	char * arrOfNotGuessedLet;
	int countGuessed;
	int countNotGuessed;
	void isLetterInWord(char let);
	bool win();
	bool lose();
	int score;
	int health;
	Dictionary dictionary;
	bool isWordUsed[20];
	void choseWord();
	void printGameText();
public:
	GameView(Levels _level, int _score = 0, int _health = 15);
	void draw();
	View * handle();
};