#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstring>
#include <sstream>
#include <locale.h>
#include <cstring>
#include <sstream>
#include <conio.h>
#include <Windows.h>
#include "Color.h"
#include "SetConsoleSize.h"
#include "Parametrs.h"
#include "Highscores.h"
using namespace std;

extern Parametrs game;
extern HANDLE hConsole;

class HighScoresMenu{
public:
	int highScoreLanguage;
	HighScore scores[9];
public:
	HighScoresMenu() : highScoreLanguage(game.language)
	{
		ifstream read("HighScores.txt");
		HighScore scores[9];
		for (size_t i = 0; i < 9; ++i)
			read >> scores[i];

		read.seekg(0);
		read.clear();
		read.close();
	}

	HighScoresMenu(HighScore hsc[9]){
		for (size_t i = 0; i < 9; ++i)
			scores[i] = hsc[i];

		highScoreLanguage = game.language;
	}

	void drawHighScores(){

		ifstream read("HighScores.txt");
		HighScore scores[9];
		for (size_t i = 0; i < 9; ++i)
			read >> scores[i];

		read.seekg(0);
		read.clear();
		read.close();

		system("cls");
		SetConsoleTextAttribute(hConsole, Aqua);

		for (size_t i = 0; i < 5; ++i)
			cout << endl;

		const string spaces = "                       ";

		string EnNAME = "NAME";
		string EnWORDS = "WORDS";
		string EnLITERS = "LITERS";
		string EnDIFFICULTY = "DIFFICULTY";
		string UaNAME = "";
		UaNAME += I;
		UaNAME += "Ì'ß";
		string UaWORDS = "ÑËÎÂÀ";
		string UaLITERS = "ÁÓÊÂÈ";
		string UaDIFFICULTY = "ÑÊËÀÄÍ";
		UaDIFFICULTY += I;
		UaDIFFICULTY += "ÑÒÜ";


		if (game.language == 0){

			cout << spaces << EnNAME << "            " << EnWORDS << "  " << EnLITERS << "  " << EnDIFFICULTY << endl << endl;
			SetConsoleTextAttribute(hConsole, Red);
			for (size_t i = 0; i < 9; ++i)
				cout << spaces << scores[i];

			cout << endl << endl << endl;

			SetConsoleTextAttribute(hConsole, Yellow);
			cout << "                             PRESS ESC TO EXIT TO MAIN MENU" << endl;
			SetConsoleTextAttribute(hConsole, Blue);


			bool isFalseButton = true;
			char escapePressed = ' ';

			while (isFalseButton){
				escapePressed = _getch();

				if (escapePressed == 27)
					isFalseButton = false;
			}
		}

		if (game.language == 1){

			cout << spaces << UaNAME << "            " << UaWORDS << "   " << UaLITERS << "  " << UaDIFFICULTY << endl << endl;
			SetConsoleTextAttribute(hConsole, Red);
			for (size_t i = 0; i < 9; ++i)
				cout << spaces << scores[i];

			cout << endl << endl << endl;

			SetConsoleTextAttribute(hConsole, Yellow);
			string PRESSESCAPE = "ÍÀÒÈÑÍ";
			PRESSESCAPE += I;
			PRESSESCAPE += "ÒÜ ESC ÄËß ÂÈÕÎÄÓ";

			cout << "                         " << PRESSESCAPE << endl;
			SetConsoleTextAttribute(hConsole, Blue);


			bool isFalseButton = true;
			char escapePressed = ' ';

			while (isFalseButton){
				escapePressed = _getch();

				if (escapePressed == 27)
					isFalseButton = false;
			}

		}
	}
};

HighScoresMenu drawHighScoresMenu;