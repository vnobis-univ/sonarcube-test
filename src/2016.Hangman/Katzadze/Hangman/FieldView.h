#pragma once
#include <conio.h>
#include <fstream>
#include <vector>
#include <time.h>
#include "View.h"
#include "Console_.h"
#include "StartView.h"
#include "ResultView.h"

using namespace std;

class FieldView : public View
{
	string _word;
	string words[30];
	
	string usedEnLetter[26];
	string arrOfUsedWords[30];
	int index;
	short hp;
	string* part;
	short score = 0;
	short unicounter = 0;

public:
	FieldView();
	FieldView(short, short, short, string[]);
	void draw();
	View* handle();
	void printAlphabet();
	void print_Word();
	void printScoreText();
	void printAttempts();
	void drawNextWordButton();
	void outWord();
	bool isLetterInWord(char);
	void _wordChanger(char);
	void keyHandler(char, short, short, short);
	bool isWordCompleted();
	bool isUsed(string);
	bool isLetterUsed(int);
};