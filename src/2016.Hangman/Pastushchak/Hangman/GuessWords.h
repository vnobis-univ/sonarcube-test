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
#include <stdlib.h>
#include <Windows.h>
#include "Color.h"
#include "SetConsoleSize.h"
#include "Parametrs.h"
#include "Highscores.h"
#include "ManWillDie.h"
#include <wingdi.h>
using namespace std;

extern Parametrs game;
extern HANDLE hConsole;

class Guessing{
private:
	size_t wordLength;
	int guessingLanguage;
	size_t youAlreadyGuessWords;
	size_t youAlreadyGuessLiters;
	int healthPoints;
	bool ifWeDrawFirstTime;
	string words[20];
	bool isAlreadyUsed[20];
	bool endWasAlreadyBeen;
	int minHP;
public:
	Guessing() : wordLength(game.difficulty + 4),
		guessingLanguage(game.language),
		youAlreadyGuessWords(0),
		youAlreadyGuessLiters(0),
		healthPoints(20 - 5 * game.difficulty),
		ifWeDrawFirstTime(true),
		endWasAlreadyBeen(false),
		minHP(20 - 5 * game.difficulty)
	{
		for (size_t i = 0; i < 20; ++i)
			isAlreadyUsed[i] = false;
	}

	void drawGame(){


		system("cls");
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);

		if (ifWeDrawFirstTime){
			wordLength = game.difficulty + 4;
			guessingLanguage = game.language;
			youAlreadyGuessWords = 0;
			youAlreadyGuessLiters = 0;
			healthPoints = 20 - 5 * game.difficulty;
			minHP = 20 - 5 * game.difficulty;
			ifWeDrawFirstTime = false;
		}

		if (wordLength == 4 && guessingLanguage == 0)
		{
			ifstream read("VocabluralyEnEasy.txt");
			for (size_t i = 0; i < 20; ++i)
				read >> words[i];
		}

		if (wordLength == 5 && guessingLanguage == 0)
		{
			ifstream read("VocabluralyEnMedium.txt");
			for (size_t i = 0; i < 20; ++i)
				read >> words[i];
		}

		if (wordLength == 6 && guessingLanguage == 0)
		{
			ifstream read("VocabluralyEnHard.txt");
			for (size_t i = 0; i < 20; ++i)
				read >> words[i];
		}

		if (wordLength == 4 && guessingLanguage == 1)
		{
			ifstream read("VocabluralyUaEasy.txt");
			for (size_t i = 0; i < 20; ++i)
				read >> words[i];
		}

		if (wordLength == 5 && guessingLanguage == 1)
		{
			ifstream read("VocabluralyUaMedium.txt");
			for (size_t i = 0; i < 20; ++i)
				read >> words[i];
		}

		if (wordLength == 6 && guessingLanguage == 1)
		{
			ifstream read("VocabluralyUaHard.txt");
			for (size_t i = 0; i < 20; ++i)
				read >> words[i];
		}

		bool isNew = false;
		size_t randomIndex;

		srand(time(NULL));

		while (!isNew){

			if (isNew) break;

			randomIndex = rand() % 20;
			if (isAlreadyUsed[randomIndex] == false){
				isNew = true;
				isAlreadyUsed[randomIndex] = true;
			}
		}

		drawYouGuessAWord(words[randomIndex]);

		if (!endWasAlreadyBeen){
			endWasAlreadyBeen = true;
			HighScore h[9];
			ifstream readHighScore("HighScores.txt");
			for (size_t i = 0; i < 9; ++i)
				readHighScore >> h[i];

			readHighScore.seekg(0);
			readHighScore.clear();
			readHighScore.close();

			bool youBeatRecord = false;

			switch (wordLength)
			{
			case 4:
			{
				if (youAlreadyGuessWords > h[8].numberGuessedWords)
					youBeatRecord = true;
				if (youAlreadyGuessWords == h[8].numberGuessedWords && youAlreadyGuessLiters > h[8].numberGuessedLiters)
					youBeatRecord = true;
			}
			case 5:
			{
				if (youAlreadyGuessWords > h[5].numberGuessedWords)
					youBeatRecord = true;
				if (youAlreadyGuessWords == h[5].numberGuessedWords && youAlreadyGuessLiters > h[5].numberGuessedLiters)
					youBeatRecord = true;
			}

			case 6:
			{
				if (youAlreadyGuessWords > h[2].numberGuessedWords)
					youBeatRecord = true;
				if (youAlreadyGuessWords == h[2].numberGuessedWords && youAlreadyGuessLiters > h[2].numberGuessedLiters)
					youBeatRecord = true;
			}
			}

			POINT op;
			HWND hWnd = GetConsoleWindow();
			HDC hDC = GetDC(hWnd);
			HPEN hPenBLACK = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
			SelectObject(hDC, hPenBLACK);
			HBRUSH hNewBrush;
			HBRUSH hOldBrush;
			hNewBrush = CreateSolidBrush(0x000000);
			hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
			Ellipse(hDC, 0, 0, 500, 500);


			if (youBeatRecord == false){
				system("cls");

				for (size_t i = 0; i < 5; ++i)
					cout << endl;

				SetConsoleTextAttribute(hConsole, Red);

				if (game.language == 0){
					cout << "                     SORRY, BUT YOU DO NOT BEAT A RECORD..." << endl;
					cout << "                               TRY ONE MORE TIME" << endl;

					cout << endl << endl << endl;
					cout << "                               PRESS ESC TO EXIT" << endl;
				}
				else{
					cout << "                         ÂÈ ÍÅ ÏÎÁÈËÈ ÐÅÊÎÐÄ..." << endl;
					cout << "                            ÑÏÐÎÁÓÉÒÅ ÙÅ ÐÀÇ  " << endl;

					cout << endl << endl << endl;
					cout << "                       ÍÀÒÈÑÍ²ÒÜ ESC ÄËß ÂÈÕÎÄÓ" << endl;
				}

				char exitPress = ' ';
				while (exitPress != 27)
				{
					if (exitPress == 27) break;
					exitPress = _getch();
				}
			}

			else{

				system("cls");

				for (size_t i = 0; i < 5; ++i)
					cout << endl;


				string spaces = "                            ";
				if (game.language == 0){
					cout << spaces << "  CONGRATULATIONS!!!" << endl;
					cout << spaces << " YOU BEAT THE RECORD!" << endl;
					cout << endl << endl;
					cout << spaces << "PLEASE ENTER YOUR NAME" << endl;
				}
				else{
					cout << spaces << "   Â²ÒÀªÌÎ!!!" << endl;
					cout << spaces << "ÂÈ ÏÎÁÈËÈ ÐÅÊÎÐÄ!" << endl;
					cout << endl << endl;
					cout << spaces << "ÂÂÅÄ²ÒÜ ÂÀØÅ ²Ì'ß" << endl;
				}

				string nameOfPlayer;

				cin >> nameOfPlayer;
				if (nameOfPlayer.length() > 15)
				{
					string s;
					for (size_t i = 0; i < 15; ++i)
						s[i] = nameOfPlayer[i];

					nameOfPlayer = s;
				}


				string diff;
				if (game.language == 0 && game.difficulty == 0) diff = "EASY";
				if (game.language == 0 && game.difficulty == 1) diff = "MEDIUM";
				if (game.language == 0 && game.difficulty == 2) diff = "HARD";
				if (game.language == 1 && game.difficulty == 0) diff = "ËÅÃÊÀ";
				if (game.language == 1 && game.difficulty == 1) diff = "ÑÅÐÅÄÍß";
				if (game.language == 1 && game.difficulty == 2) diff = "ÂÀÆÊÀ";

				HighScore yourScore(nameOfPlayer, youAlreadyGuessWords, youAlreadyGuessLiters, diff);
				HighScore additionalHighscore;
				HighScore secondAdditional;

				if (game.difficulty == 2){

					if (yourScore > h[0]){
						additionalHighscore = h[0];
						h[0] = yourScore;
						secondAdditional = h[1];
						h[1] = additionalHighscore;
						h[2] = secondAdditional;
					}

					else{

						if (yourScore > h[1]){
							secondAdditional = h[1];
							h[1] = yourScore;
							h[2] = secondAdditional;
						}

						else h[2] = yourScore;
					}
				}

				if (game.difficulty == 1){

					if (yourScore > h[3]){
						additionalHighscore = h[3];
						h[3] = yourScore;
						secondAdditional = h[4];
						h[4] = additionalHighscore;
						h[5] = secondAdditional;
					}

					else{

						if (yourScore > h[4]){
							secondAdditional = h[4];
							h[4] = yourScore;
							h[5] = secondAdditional;
						}

						else h[5] = yourScore;
					}
				}

				if (game.difficulty == 0){

					if (yourScore > h[6]){
						additionalHighscore = h[6];
						h[6] = yourScore;
						secondAdditional = h[7];
						h[7] = additionalHighscore;
						h[8] = secondAdditional;
					}

					else{

						if (yourScore > h[7]){
							secondAdditional = h[7];
							h[7] = yourScore;
							h[8] = secondAdditional;
						}

						else h[8] = yourScore;
					}
				}

				for (size_t i = 0; i < 9; ++i)
				{
					if (h[i].playerDifficulty == "EASY" && game.language == 1) h[i].playerDifficulty = "ËÅÃÊÀ";
					if (h[i].playerDifficulty == "MEDIUM" && game.language == 1) h[i].playerDifficulty = "ÑÅÐÅÄÍß";
					if (h[i].playerDifficulty == "HARD" && game.language == 1) h[i].playerDifficulty = "ÂÀÆÊÀ";
					if (h[i].playerDifficulty == "ËÅÃÊÀ" && game.language == 0) h[i].playerDifficulty = "EASY";
					if (h[i].playerDifficulty == "ÑÅÐÅÄÍß" && game.language == 0) h[i].playerDifficulty = "MEDIUM";
					if (h[i].playerDifficulty == "ÂÀÆÊÀ" && game.language == 0) h[i].playerDifficulty = "HARD";
				}


				system("cls");

				ofstream write("HighScores.txt");
				for (size_t i = 0; i < 9; ++i)
					write << h[i];

				write.close();

				HighScoresMenu newHighScoresMenu(h);
				newHighScoresMenu.drawHighScores();

			}
		}
	};

	void drawYouCurrentlyGuessEn4(bool youAlreadyChooseThisLetter[26], char EnLetters[26], char symbols[4]){

		system("cls");

		SetConsoleTextAttribute(hConsole, Purple);

		cout << "                        YOU CURRENTLY GUESS " << youAlreadyGuessWords << " WORDS" << endl <<
			"                       YOU CURRENT HEALTH POINTS: " << healthPoints << endl;

		for (size_t i = 0; i < 11; ++i)
			cout << endl;

		if (healthPoints < 20)
			drawMan(20 - healthPoints, minHP);

		const string spaces = "                                 ";
		cout << spaces;
		SetConsoleTextAttribute(hConsole, Yellow);
		for (size_t i = 0; i < 4; ++i)
			cout << symbols[i] << " ";

		cout << endl << endl;

		SetConsoleTextAttribute(hConsole, Blue);

		for (size_t i = 0; i < 26; ++i)
		{
			if (i == 0 || i == 13) cout << endl << "                     ";
			if (youAlreadyChooseThisLetter[i] == true)
				SetConsoleTextAttribute(hConsole, Green);

			cout << EnLetters[i] << "  ";
			SetConsoleTextAttribute(hConsole, Blue);
		}
	}

	void drawYouCurrentlyGuessEn5(bool youAlreadyChooseThisLetter[26], char EnLetters[26], char symbols[5]){

		system("cls");

		SetConsoleTextAttribute(hConsole, Purple);

		cout << "                        YOU CURRENTLY GUESS " << youAlreadyGuessWords << " WORDS" << endl <<
			"                       YOU CURRENT HEALTH POINTS: " << healthPoints << endl;

		for (size_t i = 0; i < 11; ++i)
			cout << endl;

		if (healthPoints < 20)
			drawMan(20 - healthPoints, minHP);

		const string spaces = "                                 ";
		cout << spaces;
		SetConsoleTextAttribute(hConsole, Yellow);
		for (size_t i = 0; i < 5; ++i)
			cout << symbols[i] << " ";

		cout << endl << endl;

		SetConsoleTextAttribute(hConsole, Blue);

		for (size_t i = 0; i < 26; ++i)
		{
			if (i == 0 || i == 13) cout << endl << "                     ";
			if (youAlreadyChooseThisLetter[i] == true)
				SetConsoleTextAttribute(hConsole, Green);

			cout << EnLetters[i] << "  ";
			SetConsoleTextAttribute(hConsole, Blue);
		}
	}

	void drawYouCurrentlyGuessEn6(bool youAlreadyChooseThisLetter[26], char EnLetters[26], char symbols[6]){

		system("cls");

		SetConsoleTextAttribute(hConsole, Purple);

		cout << "                        YOU CURRENTLY GUESS " << youAlreadyGuessWords << " WORDS" << endl <<
			"                       YOU CURRENT HEALTH POINTS: " << healthPoints << endl;

		for (size_t i = 0; i < 11; ++i)
			cout << endl;

		if (healthPoints < 20)
			drawMan(20 - healthPoints, minHP);


		const string spaces = "                                 ";
		cout << spaces;
		SetConsoleTextAttribute(hConsole, Yellow);
		for (size_t i = 0; i < 6; ++i)
			cout << symbols[i] << " ";

		cout << endl << endl;

		SetConsoleTextAttribute(hConsole, Blue);

		for (size_t i = 0; i < 26; ++i)
		{
			if (i == 0 || i == 13) cout << endl << "                     ";
			if (youAlreadyChooseThisLetter[i] == true)
				SetConsoleTextAttribute(hConsole, Green);

			cout << EnLetters[i] << "  ";
			SetConsoleTextAttribute(hConsole, Blue);
		}
	}

	void drawYouCurrentlyGuessUa4(bool youAlreadyChooseThisLetter[33], char EnLetters[33], char symbols[4]){

		system("cls");

		SetConsoleTextAttribute(hConsole, Purple);

		string SLOVO = "ÑËÎÂÀ";
		if (youAlreadyGuessWords == 1) SLOVO = "ÑËÎÂÎ";
		if (youAlreadyGuessWords == 0 || youAlreadyGuessWords > 4) SLOVO = "ÑË²Â";
		cout << "                        ÂÈ ÂÆÅ Â²ÄÃÀÄÀËÈ " << youAlreadyGuessWords << " " << SLOVO << endl <<
			"                  Ó ÂÀÑ ÙÅ ÇÀËÈØÈËÎÑÜ " << healthPoints << " Î×Ê²Â ÇÄÎÐÎÂ'ß" << endl;

		for (size_t i = 0; i < 11; ++i)
			cout << endl;

		if (healthPoints < 20)
			drawMan(20 - healthPoints, minHP);


		const string spaces = "                                 ";
		cout << spaces;
		SetConsoleTextAttribute(hConsole, Yellow);
		for (size_t i = 0; i < 4; ++i)
			cout << symbols[i] << " ";

		cout << endl << endl << endl << "                       ";

		SetConsoleTextAttribute(hConsole, Blue);

		for (size_t i = 0; i < 33; ++i)
		{
			if (i == 11 || i == 22){
				cout << endl;
				cout << "                       ";
			}

			if (youAlreadyChooseThisLetter[i] == true)
				SetConsoleTextAttribute(hConsole, Green);

			cout << EnLetters[i] << "  ";
			SetConsoleTextAttribute(hConsole, Blue);
		}

		cout << endl << endl;
	}

	void drawYouCurrentlyGuessUa5(bool youAlreadyChooseThisLetter[33], char EnLetters[33], char symbols[5]){

		system("cls");

		SetConsoleTextAttribute(hConsole, Purple);

		string SLOVO = "ÑËÎÂÀ";
		if (youAlreadyGuessWords == 1) SLOVO = "ÑËÎÂÎ";
		if (youAlreadyGuessWords == 0 || youAlreadyGuessWords > 4) SLOVO = "ÑË²Â";
		cout << "                        ÂÈ ÂÆÅ Â²ÄÃÀÄÀËÈ " << youAlreadyGuessWords << " " << SLOVO << endl <<
			"                  Ó ÂÀÑ ÙÅ ÇÀËÈØÈËÎÑÜ " << healthPoints << " Î×Ê²Â ÇÄÎÐÎÂ'ß" << endl;

		for (size_t i = 0; i < 11; ++i)
			cout << endl;

		if (healthPoints < 20)
			drawMan(20 - healthPoints, minHP);


		const string spaces = "                                 ";
		cout << spaces;
		SetConsoleTextAttribute(hConsole, Yellow);
		for (size_t i = 0; i < 5; ++i)
			cout << symbols[i] << " ";

		cout << endl << endl << endl << "                       ";

		SetConsoleTextAttribute(hConsole, Blue);

		for (size_t i = 0; i < 33; ++i)
		{
			if (i == 11 || i == 22){
				cout << endl;
				cout << "                       ";
			}

			if (youAlreadyChooseThisLetter[i] == true)
				SetConsoleTextAttribute(hConsole, Green);

			cout << EnLetters[i] << "  ";
			SetConsoleTextAttribute(hConsole, Blue);
		}

		cout << endl << endl;

	}

	void drawYouCurrentlyGuessUa6(bool youAlreadyChooseThisLetter[33], char EnLetters[33], char symbols[6]){

		system("cls");

		SetConsoleTextAttribute(hConsole, Purple);

		string SLOVO = "ÑËÎÂÀ";
		if (youAlreadyGuessWords == 1) SLOVO = "ÑËÎÂÎ";
		if (youAlreadyGuessWords == 0 || youAlreadyGuessWords > 4) SLOVO = "ÑË²Â";
		cout << "                        ÂÈ ÂÆÅ Â²ÄÃÀÄÀËÈ " << youAlreadyGuessWords << " " << SLOVO << endl <<
			"                  Ó ÂÀÑ ÙÅ ÇÀËÈØÈËÎÑÜ " << healthPoints << " Î×Ê²Â ÇÄÎÐÎÂ'ß" << endl;

		for (size_t i = 0; i < 11; ++i)
			cout << endl;

		if (healthPoints < 20)
			drawMan(20 - healthPoints, minHP);

		const string spaces = "                                 ";
		cout << spaces;
		SetConsoleTextAttribute(hConsole, Yellow);
		for (size_t i = 0; i < 6; ++i)
			cout << symbols[i] << " ";

		cout << endl << endl << endl << "                       ";

		SetConsoleTextAttribute(hConsole, Blue);

		for (size_t i = 0; i < 33; ++i)
		{
			if (i == 11 || i == 22){
				cout << endl;
				cout << "                       ";
			}

			if (youAlreadyChooseThisLetter[i] == true)
				SetConsoleTextAttribute(hConsole, Green);

			cout << EnLetters[i] << "  ";
			SetConsoleTextAttribute(hConsole, Blue);
		}

		cout << endl << endl;
		SetConsoleTextAttribute(hConsole, Blue);
	}

	void drawYouGuessAWordEn4(string wordYouMustGuess){
		bool youAlreadyChooseThisLetter[26];
		for (size_t i = 0; i < 26; ++i)
			youAlreadyChooseThisLetter[i] = false;

		char EnLetters[26];
		for (size_t i = 0; i < 26; ++i)
			EnLetters[i] = 65 + i;

		char symbols[4];
		for (size_t i = 0; i < 4; ++i)
			symbols[i] = '_';

		bool youGuess = false;
		bool lettersGuessed[4];
		for (size_t i = 0; i < 4; ++i)
			lettersGuessed[i] = false;


		while (healthPoints > 0 && !youGuess)
		{
			drawYouCurrentlyGuessEn4(youAlreadyChooseThisLetter, EnLetters, symbols);

			int indexYourSymbol = -1;

			while (indexYourSymbol == -1){
				if (indexYourSymbol >= 0) break;
				char yourSymbol;
				yourSymbol = _getch();

				for (size_t i = 0; i < 26; ++i)
					if (EnLetters[i] == yourSymbol) indexYourSymbol = i;
			}

			bool youGuessALetter = false;
			for (size_t i = 0; i < 4; ++i)
			{
				if (wordYouMustGuess[i] == EnLetters[indexYourSymbol])
				{
					symbols[i] = EnLetters[indexYourSymbol];
					youGuessALetter = true;
					lettersGuessed[i] = true;
				}
			}

			youGuess = true;
			youAlreadyGuessLiters = 4;
			for (size_t i = 0; i < 4; ++i)
				if (lettersGuessed[i] == false){
					youGuess = false;
					--youAlreadyGuessLiters;
				}

			if (!youGuessALetter)
			{
				--healthPoints;
				--minHP;
			}

			youAlreadyChooseThisLetter[indexYourSymbol] = true;
			drawYouCurrentlyGuessEn4(youAlreadyChooseThisLetter, EnLetters, symbols);
		}

		if (youGuess)
		{
			healthPoints += 5;
			youAlreadyGuessWords++;
			drawGame();
		}
	}

	void drawYouGuessAWordEn5(string wordYouMustGuess){

		bool youAlreadyChooseThisLetter[26];
		for (size_t i = 0; i < 26; ++i)
			youAlreadyChooseThisLetter[i] = false;

		char EnLetters[26];
		for (size_t i = 0; i < 26; ++i)
			EnLetters[i] = 65 + i;

		char symbols[5];
		for (size_t i = 0; i < 5; ++i)
			symbols[i] = '_';

		bool youGuess = false;
		bool lettersGuessed[5];
		for (size_t i = 0; i < 5; ++i)
			lettersGuessed[i] = false;


		while (healthPoints > 0 && !youGuess)
		{
			drawYouCurrentlyGuessEn5(youAlreadyChooseThisLetter, EnLetters, symbols);

			int indexYourSymbol = -1;

			while (indexYourSymbol == -1){
				if (indexYourSymbol >= 0) break;
				char yourSymbol;
				yourSymbol = _getch();

				for (size_t i = 0; i < 26; ++i)
					if (EnLetters[i] == yourSymbol) indexYourSymbol = i;
			}

			bool youGuessALetter = false;
			for (size_t i = 0; i < 5; ++i)
			{
				if (wordYouMustGuess[i] == EnLetters[indexYourSymbol])
				{
					symbols[i] = EnLetters[indexYourSymbol];
					youGuessALetter = true;
					lettersGuessed[i] = true;
				}
			}

			youGuess = true;
			youAlreadyGuessLiters = 5;
			for (size_t i = 0; i < 5; ++i)
				if (lettersGuessed[i] == false){
					youGuess = false;
					--youAlreadyGuessLiters;
				}

			if (!youGuessALetter)
			{
				--healthPoints;
				--minHP;
			}

			youAlreadyChooseThisLetter[indexYourSymbol] = true;
			drawYouCurrentlyGuessEn5(youAlreadyChooseThisLetter, EnLetters, symbols);
		}

		if (youGuess)
		{
			healthPoints += 4;
			youAlreadyGuessWords++;
			drawGame();
		}

	}

	void drawYouGuessAWordEn6(string wordYouMustGuess){

		bool youAlreadyChooseThisLetter[26];
		for (size_t i = 0; i < 26; ++i)
			youAlreadyChooseThisLetter[i] = false;

		char EnLetters[26];
		for (size_t i = 0; i < 26; ++i)
			EnLetters[i] = 65 + i;

		char symbols[6];
		for (size_t i = 0; i < 6; ++i)
			symbols[i] = '_';

		bool youGuess = false;
		bool lettersGuessed[6];
		for (size_t i = 0; i < 6; ++i)
			lettersGuessed[i] = false;


		while (healthPoints > 0 && !youGuess)
		{
			drawYouCurrentlyGuessEn6(youAlreadyChooseThisLetter, EnLetters, symbols);

			int indexYourSymbol = -1;

			while (indexYourSymbol == -1){
				if (indexYourSymbol >= 0) break;
				char yourSymbol;
				yourSymbol = _getch();

				for (size_t i = 0; i < 26; ++i)
					if (EnLetters[i] == yourSymbol) indexYourSymbol = i;
			}

			bool youGuessALetter = false;
			for (size_t i = 0; i < 6; ++i)
			{
				if (wordYouMustGuess[i] == EnLetters[indexYourSymbol])
				{
					symbols[i] = EnLetters[indexYourSymbol];
					youGuessALetter = true;
					lettersGuessed[i] = true;
				}
			}

			youGuess = true;
			youAlreadyGuessLiters = 6;
			for (size_t i = 0; i < 6; ++i)
				if (lettersGuessed[i] == false){
					youGuess = false;
					--youAlreadyGuessLiters;
				}

			if (!youGuessALetter)
			{
				--healthPoints;
				--minHP;
			}

			youAlreadyChooseThisLetter[indexYourSymbol] = true;
			drawYouCurrentlyGuessEn6(youAlreadyChooseThisLetter, EnLetters, symbols);
		}

		if (youGuess)
		{
			healthPoints += 3;
			youAlreadyGuessWords++;
			drawGame();
		}
	}

	void drawYouGuessAWordUa4(string wordYouMustGuess) {

		bool youAlreadyChooseThisLetter[33];
		for (size_t i = 0; i < 33; ++i)
			youAlreadyChooseThisLetter[i] = false;

		char UaLetters[33];
		UaLetters[0] = 'À';
		UaLetters[1] = 'Á';
		UaLetters[2] = 'Â';
		UaLetters[3] = 'Ã';
		UaLetters[4] = '¥';
		UaLetters[5] = 'Ä';
		UaLetters[6] = 'Å';
		UaLetters[7] = 'ª';
		UaLetters[8] = 'Æ';
		UaLetters[9] = 'Ç';
		UaLetters[10] = 'È';
		UaLetters[11] = '²';
		UaLetters[12] = '¯';
		UaLetters[13] = 'É';
		UaLetters[14] = 'Ê';
		UaLetters[15] = 'Ë';
		UaLetters[16] = 'Ì';
		UaLetters[17] = 'Í';
		UaLetters[18] = 'Î';
		UaLetters[19] = 'Ï';
		UaLetters[20] = 'Ð';
		UaLetters[21] = 'Ñ';
		UaLetters[22] = 'Ò';
		UaLetters[23] = 'Ó';
		UaLetters[24] = 'Ô';
		UaLetters[25] = 'Õ';
		UaLetters[26] = 'Ö';
		UaLetters[27] = '×';
		UaLetters[28] = 'Ø';
		UaLetters[29] = 'Ù';
		UaLetters[30] = 'Ü';
		UaLetters[31] = 'Þ';
		UaLetters[32] = 'ß';

		char symbols[4];
		for (size_t i = 0; i < 4; ++i)
			symbols[i] = '_';

		bool youGuess = false;
		bool lettersGuessed[4];
		for (size_t i = 0; i < 4; ++i)
			lettersGuessed[i] = false;



		while (healthPoints > 0 && !youGuess)
		{
			drawYouCurrentlyGuessUa4(youAlreadyChooseThisLetter, UaLetters, symbols);

			int indexYourSymbol = -1;

			while (indexYourSymbol == -1){
				if (indexYourSymbol >= 0) break;
				char yourSymbol;
				yourSymbol = _getch();

				for (size_t i = 0; i < 33; ++i)
					if (UaLetters[i] == yourSymbol) indexYourSymbol = i;
			}

			bool youGuessALetter = false;
			for (size_t i = 0; i < 4; ++i)
			{
				if (wordYouMustGuess[i] == UaLetters[indexYourSymbol])
				{
					symbols[i] = UaLetters[indexYourSymbol];
					youGuessALetter = true;
					lettersGuessed[i] = true;
				}
			}

			youGuess = true;
			youAlreadyGuessLiters = 4;
			for (size_t i = 0; i < 4; ++i)
				if (lettersGuessed[i] == false){
					youGuess = false;
					--youAlreadyGuessLiters;
				}

			if (!youGuessALetter)
			{
				--healthPoints;
				--minHP;
			}

			youAlreadyChooseThisLetter[indexYourSymbol] = true;
			drawYouCurrentlyGuessUa4(youAlreadyChooseThisLetter, UaLetters, symbols);
		}

		if (youGuess)
		{
			healthPoints += 5;
			youAlreadyGuessWords++;
			drawGame();
		}
	}

	void drawYouGuessAWordUa5(string wordYouMustGuess){


		bool youAlreadyChooseThisLetter[33];
		for (size_t i = 0; i < 33; ++i)
			youAlreadyChooseThisLetter[i] = false;

		char UaLetters[33];
		UaLetters[0] = 'À';
		UaLetters[1] = 'Á';
		UaLetters[2] = 'Â';
		UaLetters[3] = 'Ã';
		UaLetters[4] = '¥';
		UaLetters[5] = 'Ä';
		UaLetters[6] = 'Å';
		UaLetters[7] = 'ª';
		UaLetters[8] = 'Æ';
		UaLetters[9] = 'Ç';
		UaLetters[10] = 'È';
		UaLetters[11] = '²';
		UaLetters[12] = '¯';
		UaLetters[13] = 'É';
		UaLetters[14] = 'Ê';
		UaLetters[15] = 'Ë';
		UaLetters[16] = 'Ì';
		UaLetters[17] = 'Í';
		UaLetters[18] = 'Î';
		UaLetters[19] = 'Ï';
		UaLetters[20] = 'Ð';
		UaLetters[21] = 'Ñ';
		UaLetters[22] = 'Ò';
		UaLetters[23] = 'Ó';
		UaLetters[24] = 'Ô';
		UaLetters[25] = 'Õ';
		UaLetters[26] = 'Ö';
		UaLetters[27] = '×';
		UaLetters[28] = 'Ø';
		UaLetters[29] = 'Ù';
		UaLetters[30] = 'Ü';
		UaLetters[31] = 'Þ';
		UaLetters[32] = 'ß';

		char symbols[5];
		for (size_t i = 0; i < 5; ++i)
			symbols[i] = '_';

		bool youGuess = false;
		bool lettersGuessed[5];
		for (size_t i = 0; i < 5; ++i)
			lettersGuessed[i] = false;

		while (healthPoints > 0 && !youGuess)
		{
			drawYouCurrentlyGuessUa5(youAlreadyChooseThisLetter, UaLetters, symbols);

			int indexYourSymbol = -1;

			while (indexYourSymbol == -1){
				if (indexYourSymbol >= 0) break;
				char yourSymbol;
				yourSymbol = _getch();

				for (size_t i = 0; i < 33; ++i)
					if (UaLetters[i] == yourSymbol) indexYourSymbol = i;
			}

			bool youGuessALetter = false;
			for (size_t i = 0; i < 5; ++i)
			{
				if (wordYouMustGuess[i] == UaLetters[indexYourSymbol])
				{
					symbols[i] = UaLetters[indexYourSymbol];
					youGuessALetter = true;
					lettersGuessed[i] = true;
				}
			}

			youGuess = true;
			youAlreadyGuessLiters = 5;
			for (size_t i = 0; i < 5; ++i)
				if (lettersGuessed[i] == false){
					youGuess = false;
					--youAlreadyGuessLiters;
				}

			if (!youGuessALetter)
			{
				--healthPoints;
				--minHP;
			}

			youAlreadyChooseThisLetter[indexYourSymbol] = true;
			drawYouCurrentlyGuessUa5(youAlreadyChooseThisLetter, UaLetters, symbols);
		}

		if (youGuess)
		{
			healthPoints += 4;
			youAlreadyGuessWords++;
			drawGame();
		}
	}

	void drawYouGuessAWordUa6(string wordYouMustGuess){

		bool youAlreadyChooseThisLetter[33];
		for (size_t i = 0; i < 33; ++i)
			youAlreadyChooseThisLetter[i] = false;

		char UaLetters[33];
		UaLetters[0] = 'À';
		UaLetters[1] = 'Á';
		UaLetters[2] = 'Â';
		UaLetters[3] = 'Ã';
		UaLetters[4] = '¥';
		UaLetters[5] = 'Ä';
		UaLetters[6] = 'Å';
		UaLetters[7] = 'ª';
		UaLetters[8] = 'Æ';
		UaLetters[9] = 'Ç';
		UaLetters[10] = 'È';
		UaLetters[11] = '²';
		UaLetters[12] = '¯';
		UaLetters[13] = 'É';
		UaLetters[14] = 'Ê';
		UaLetters[15] = 'Ë';
		UaLetters[16] = 'Ì';
		UaLetters[17] = 'Í';
		UaLetters[18] = 'Î';
		UaLetters[19] = 'Ï';
		UaLetters[20] = 'Ð';
		UaLetters[21] = 'Ñ';
		UaLetters[22] = 'Ò';
		UaLetters[23] = 'Ó';
		UaLetters[24] = 'Ô';
		UaLetters[25] = 'Õ';
		UaLetters[26] = 'Ö';
		UaLetters[27] = '×';
		UaLetters[28] = 'Ø';
		UaLetters[29] = 'Ù';
		UaLetters[30] = 'Ü';
		UaLetters[31] = 'Þ';
		UaLetters[32] = 'ß';

		char symbols[6];
		for (size_t i = 0; i < 6; ++i)
			symbols[i] = '_';

		bool youGuess = false;
		bool lettersGuessed[6];
		for (size_t i = 0; i < 6; ++i)
			lettersGuessed[i] = false;

		while (healthPoints > 0 && !youGuess)
		{
			drawYouCurrentlyGuessUa6(youAlreadyChooseThisLetter, UaLetters, symbols);

			int indexYourSymbol = -1;

			while (indexYourSymbol == -1){
				if (indexYourSymbol >= 0) break;
				char yourSymbol;
				yourSymbol = _getch();

				for (size_t i = 0; i < 33; ++i)
					if (UaLetters[i] == yourSymbol) indexYourSymbol = i;
			}

			bool youGuessALetter = false;
			for (size_t i = 0; i < 6; ++i)
			{
				if (wordYouMustGuess[i] == UaLetters[indexYourSymbol])
				{
					symbols[i] = UaLetters[indexYourSymbol];
					youGuessALetter = true;
					lettersGuessed[i] = true;
				}
			}

			youGuess = true;
			youAlreadyGuessLiters = 6;
			for (size_t i = 0; i < 6; ++i)
				if (lettersGuessed[i] == false){
					youGuess = false;
					--youAlreadyGuessLiters;
				}

			if (!youGuessALetter)
			{
				--healthPoints;
				--minHP;
			}

			youAlreadyChooseThisLetter[indexYourSymbol] = true;
			drawYouCurrentlyGuessUa6(youAlreadyChooseThisLetter, UaLetters, symbols);
		}

		if (youGuess)
		{
			healthPoints += 3;
			youAlreadyGuessWords++;
			drawGame();
		}

	}

	void drawYouGuessAWord(string wordYouMustGuess){

		if (game.language == 0 && game.difficulty == 0)
			drawYouGuessAWordEn4(wordYouMustGuess);

		if (game.language == 0 && game.difficulty == 1)
			drawYouGuessAWordEn5(wordYouMustGuess);

		if (game.language == 0 && game.difficulty == 2)
			drawYouGuessAWordEn6(wordYouMustGuess);

		if (game.language == 1 && game.difficulty == 0)
			drawYouGuessAWordUa4(wordYouMustGuess);

		if (game.language == 1 && game.difficulty == 1)
			drawYouGuessAWordUa5(wordYouMustGuess);

		if (game.language == 1 && game.difficulty == 2)
			drawYouGuessAWordUa6(wordYouMustGuess);
	}
};

Guessing reallyGame;