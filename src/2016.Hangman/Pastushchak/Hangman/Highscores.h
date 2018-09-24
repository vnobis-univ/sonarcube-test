#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstring>
#include <sstream>
#include <locale.h>
#include <Windows.h>
#include <iomanip>
#include "Color.h"
#include "Parametrs.h"
using namespace std;

extern Parametrs game;

class HighScore{
public:
	string playerName;
	int numberGuessedWords;
	int numberGuessedLiters;
	string playerDifficulty;
public:
	HighScore() : playerName("Noname"), numberGuessedWords(0), numberGuessedLiters(0), playerDifficulty("easy") {}

	HighScore(string name, int numb1, int numb2, string diff) :
		playerName(name),
		numberGuessedWords(numb1),
		numberGuessedLiters(numb2),
		playerDifficulty(diff)
	{}

	HighScore operator=(const HighScore& h){
		playerName = h.playerName;
		numberGuessedWords = h.numberGuessedWords;
		numberGuessedLiters = h.numberGuessedLiters;
		playerDifficulty = h.playerDifficulty;
		return *this;
	}

	bool operator>(const HighScore& h){
		if (numberGuessedWords > h.numberGuessedWords) return true;
		if (numberGuessedWords == h.numberGuessedWords && numberGuessedLiters > h.numberGuessedLiters) return true;

		if (numberGuessedWords < h.numberGuessedWords) return false;
		if (numberGuessedWords == h.numberGuessedWords && numberGuessedLiters < h.numberGuessedLiters) return false;

		if (numberGuessedWords == h.numberGuessedWords && numberGuessedLiters == h.numberGuessedLiters) return false;
	}

	friend istream& operator>>(istream& read, HighScore& h){
		read >> h.playerName >> h.numberGuessedWords >> h.numberGuessedLiters >> h.playerDifficulty;
		return read;
	}
	friend ostream& operator<<(ostream& write, HighScore& h){
		size_t lengthOfName = h.playerName.length();
		string s = "";
		for (size_t i = 0; i < 20 - lengthOfName; ++i)
			s += " ";

		if (game.language == 1){
			if (h.playerDifficulty == "EASY") h.playerDifficulty = "ËÅÃÊÀ";
			if (h.playerDifficulty == "MEDIUM") h.playerDifficulty = "ÑÅÐÅÄÍß";
			if (h.playerDifficulty == "HARD") h.playerDifficulty = "ÂÀÆÊÀ";

			if (h.playerDifficulty != "ÑÅÐÅÄÍß")
				write << h.playerName << s << h.numberGuessedWords << "       " << h.numberGuessedLiters << "       " << h.playerDifficulty << endl;
			else
				write << h.playerName << s << h.numberGuessedWords << "       " << h.numberGuessedLiters << "     " << h.playerDifficulty << endl;
		}


		if (game.language == 0){

			if (h.playerDifficulty != "MEDIUM")
				write << h.playerName << s << h.numberGuessedWords << "       " << h.numberGuessedLiters << "        " << h.playerDifficulty << endl;
			else
				write << h.playerName << s << h.numberGuessedWords << "       " << h.numberGuessedLiters << "      " << h.playerDifficulty << endl;
		}




		return write;
	}
};