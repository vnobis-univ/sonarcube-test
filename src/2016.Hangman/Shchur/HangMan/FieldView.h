#pragma once
#include <conio.h>
#include <fstream>
#include <vector>
#include <time.h>
#include "View.h"
#include "Console.h"
#include "StartView.h"
#include "ResultView.h"

using namespace std;

class FieldView : public View
{
	Lokalization language;
	Complexity complexity;
	string _word;
	string words[30];
	string englishLetter[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S",
		"T", "U", "V", "W", "X", "Y", "Z" };
	string ukrainianLetter[32] = { "À", "Á", "Â", "Ã", "Ä", "Å", "ª", "Æ", "Ç", "È", "²", "¯", "É", "Ê", "Ë", "Ì", "Í", "Î", "Ï", "Ð", "Ñ", "Ò",
		"Ó", "Ô", "Õ", "Ö", "×", "Ø", "Ù", "Ü", "Þ", "ß" };
	string usedEnLetter[26];
	string usedUaLetter[32];
	string arrOfUsedWords[30];
	int index;
	short hp;
	string* part;
	short score = 0;
	short unicounter = 0;

public:
	FieldView();
	FieldView(Lokalization, Complexity);
	FieldView(Lokalization, Complexity, short, short, short, string[]);
	void draw();
	View* handle();
	void printAlphabet();
	void print_Word();
	void printHelpText();
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
