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
#include "OptionsMenu.h"
#include "Highscores.h"
#include "HighScoresMenu.h"
#include "GuessWords.h"
#include "ManWillDie.h"
using namespace std;

extern Parametrs game;
extern OptionsMenu options;
extern HighScoresMenu drawHighScoresMenu;
extern Guessing reallyGame;
extern HANDLE hConsole;

class StartMenu{
public:
	int selectedOption;
	bool pressedEnter;
public:
	StartMenu() : selectedOption(0), pressedEnter(false) {}

	void draw()
	{
		pressedEnter = false;
		setlocale(LC_ALL, "UKR");
		string EnSTART = "START";
		string EnHIGHSCORE = "HIGHSCORE";
		string EnOPTIONS = "OPTIONS";
		string EnExit = "EXIT";
		string UaSTART = "—“¿–“";
		string UaHIGHSCORE = "–≈ Œ–ƒ»";
		string UaOPTIONS = " Œœ÷";
		UaOPTIONS += I;
		UaOPTIONS += "Ø";
		string UaExit = "¬»’";
		UaExit += I;
		UaExit += "ƒ";

		system("cls");
		SetConsoleTextAttribute(hConsole, Blue);
		switch (selectedOption)
		{

		case 0:
		{
			for (size_t i = 0; i < 10; ++i)
				cout << endl;

			const string spaces = "                                   ";

			if (game.language == 0){

				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << "  " << EnSTART << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << spaces << EnHIGHSCORE << endl;
				cout << spaces << " " << EnOPTIONS << endl;
				cout << spaces << "  " << EnExit << endl;
			}
			else{

				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << " " << UaSTART << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << spaces << UaHIGHSCORE << endl;
				cout << spaces << UaOPTIONS << endl;
				cout << spaces << " " << UaExit << endl;
			}
			break;
		}

		case 1:
		{
			for (size_t i = 0; i < 10; ++i)
				cout << endl;

			const string spaces = "                                   ";

			if (game.language == 0){

				cout << spaces << "  " << EnSTART << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << EnHIGHSCORE << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << spaces << " " << EnOPTIONS << endl;
				cout << spaces << "  " << EnExit << endl;
			}
			else{

				cout << spaces << " " << UaSTART << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << UaHIGHSCORE << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << spaces << UaOPTIONS << endl;
				cout << spaces << " " << UaExit << endl;
			}
			break;
		}

		case 2:
		{
			for (size_t i = 0; i < 10; ++i)
				cout << endl;

			const string spaces = "                                   ";

			if (game.language == 0){

				cout << spaces << "  " << EnSTART << endl;
				cout << spaces << EnHIGHSCORE << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << " " << EnOPTIONS << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << spaces << "  " << EnExit << endl;
			}
			else{

				cout << spaces << " " << UaSTART << endl;
				cout << spaces << UaHIGHSCORE << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << UaOPTIONS << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << spaces << " " << UaExit << endl;
			}
			break;
		}


		case 3:
		{
			for (size_t i = 0; i < 10; ++i)
				cout << endl;

			const string spaces = "                                   ";

			if (game.language == 0){

				cout << spaces << "  " << EnSTART << endl;
				cout << spaces << EnHIGHSCORE << endl;
				cout << spaces << " " << EnOPTIONS << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << "  " << EnExit << endl;
				SetConsoleTextAttribute(hConsole, Blue);
			}
			else{

				cout << spaces << " " << UaSTART << endl;
				cout << spaces << UaHIGHSCORE << endl;
				cout << spaces << UaOPTIONS << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << " " << UaExit << endl;
				SetConsoleTextAttribute(hConsole, Blue);
			}
			break;
		}
		}

		char selectOption = ' ';
		selectOption = _getch();

		switch (selectOption)
		{
		case 72:
		{
			--selectedOption;
			break;
		}

		case 75:
		{
			--selectedOption;
			break;
		}

		case 77:
		{
			++selectedOption;
			break;
		}

		case 80:
		{
			++selectedOption;
			break;
		}

		case 13:
		{
			pressedEnter = true;
			break;
		}

		default:
		{
			break;
		}
		}

		if (selectedOption < 0) selectedOption += 4;
		if (selectedOption > 3) selectedOption -= 4;

		if (pressedEnter)
		{
			afterPressingEnter();
		}

		if (!pressedEnter)
		{
			draw();
		}

	}

	void afterPressingEnter(){

		if (selectedOption == 0){
			reallyGame.drawGame();
		}

		if (selectedOption == 2){
			options.chooseOption();
			draw();
		}

		if (selectedOption == 1){
			drawHighScoresMenu.drawHighScores();
			draw();
		}
	}
};

StartMenu menu;