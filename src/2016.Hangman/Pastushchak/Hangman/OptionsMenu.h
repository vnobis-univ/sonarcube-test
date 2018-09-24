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
using namespace std;

extern Parametrs game;
extern HANDLE hConsole;

class OptionsMenu{
public:
	int selectedOfTwo;//0 - select language, 1 - select difficulty
	int selectedLanguage;//0 - english, 1 - ukrainian
	int selectedDifficulty;//0 - easy, 1 - medium, 2 - hard
public:
	OptionsMenu() : selectedOfTwo(0), selectedLanguage(game.language), selectedDifficulty(game.difficulty) {}

	void chooseLanguage(){

		system("cls");

		string EnENGLISH = " ENGLISH";
		string EnUKRAINIAN = "UKRAINIAN";
		string UaENGLISH = "¿Õ√À";
		UaENGLISH += I;
		UaENGLISH += "…—‹ ¿";
		string UaUKRAINIAN = "” –¿ØÕ—‹ ¿";
		string EnBACK = "  BACK";
		string UaBACK = "  Õ¿«¿ƒ";


		const string spaces = "                               ";
		SetConsoleTextAttribute(hConsole, Blue);
		for (size_t i = 0; i < 10; ++i)
			cout << endl;

		if (selectedLanguage == 0){

			if (game.language == 0){

				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << EnENGLISH << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << spaces << EnUKRAINIAN << endl;
				cout << endl << endl << endl;
				cout << spaces << EnBACK << endl;
			}

			if (game.language == 1){

				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << UaENGLISH << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << spaces << UaUKRAINIAN << endl;
				cout << endl << endl << endl;
				cout << spaces << UaBACK << endl;
			}

		}

		if (selectedLanguage == 1){

			if (game.language == 0){

				cout << spaces << EnENGLISH << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << EnUKRAINIAN << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << endl << endl << endl;
				cout << spaces << EnBACK << endl;
			}

			if (game.language == 1){

				cout << spaces << UaENGLISH << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << UaUKRAINIAN << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << endl << endl << endl;
				cout << spaces << UaBACK << endl;
			}
		}

		if (selectedLanguage == 2){

			if (game.language == 0){

				cout << spaces << EnENGLISH << endl;
				cout << spaces << EnUKRAINIAN << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << endl << endl << endl;
				cout << spaces << EnBACK << endl;
				SetConsoleTextAttribute(hConsole, Blue);
			}

			if (game.language == 1){

				cout << spaces << UaENGLISH << endl;
				cout << spaces << UaUKRAINIAN << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << endl << endl << endl;
				cout << spaces << UaBACK << endl;
				SetConsoleTextAttribute(hConsole, Blue);
			}
		}


		char selectLanguagePress = ' ';
		bool isPressedEnter = false;

		selectLanguagePress = _getch();

		switch (selectLanguagePress){
		case 72:
		{
			--selectedLanguage;
			break;
		}

		case 75:
		{
			--selectedLanguage;
			break;
		}

		case 77:
		{
			++selectedLanguage;
			break;
		}

		case 80:
		{
			++selectedLanguage;
			break;
		}

		case 13:
		{
			isPressedEnter = true;
			break;
		}

		default:
		{
			break;
		}
		}


		if (selectedLanguage < 0) selectedLanguage += 3;
		if (selectedLanguage > 2) selectedLanguage -= 3;

		if (selectedLanguage < 2)
			game.language = selectedLanguage;

		if (!isPressedEnter){
			chooseLanguage();
		}

		if (isPressedEnter){

			if (selectedLanguage == 2)
				chooseOption();

			else
				chooseLanguage();

		}
	}

	void chooseDifficulty(){

		system("cls");

		string EnEASY = " EASY";
		string EnMEDIUM = "MEDIUM";
		string EnHARD = " HARD";
		string UaEASY = " À≈√ ¿";
		string UaMEDIUM = "—≈–≈ƒÕﬂ";
		string UaHARD = " ¬¿∆ ¿";
		string EnBACK = " BACK";
		string UaBACK = " Õ¿«¿ƒ";

		const string spaces = "                               ";
		SetConsoleTextAttribute(hConsole, Blue);
		for (size_t i = 0; i < 10; ++i)
			cout << endl;

		if (selectedDifficulty == 0){

			if (game.language == 0){

				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << EnEASY << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << spaces << EnMEDIUM << endl;
				cout << spaces << EnHARD << endl;
				cout << endl << endl << endl;
				cout << spaces << EnBACK << endl;
			}

			if (game.language == 1){

				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << UaEASY << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << spaces << UaMEDIUM << endl;
				cout << spaces << UaHARD << endl;
				cout << endl << endl << endl;
				cout << spaces << UaBACK << endl;
			}

		}

		if (selectedDifficulty == 1){

			if (game.language == 0){

				cout << spaces << EnEASY << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << EnMEDIUM << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << spaces << EnHARD << endl;
				cout << endl << endl << endl;
				cout << spaces << EnBACK << endl;
			}

			if (game.language == 1){

				cout << spaces << UaEASY << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << UaMEDIUM << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << spaces << UaHARD << endl;
				cout << endl << endl << endl;
				cout << spaces << UaBACK << endl;
			}
		}

		if (selectedDifficulty == 2){

			if (game.language == 0){

				cout << spaces << EnEASY << endl;
				cout << spaces << EnMEDIUM << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << EnHARD << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << endl << endl << endl;
				cout << spaces << EnBACK << endl;
			}

			if (game.language == 1){

				cout << spaces << UaEASY << endl;
				cout << spaces << UaMEDIUM << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << UaHARD << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << endl << endl << endl;
				cout << spaces << UaBACK << endl;
			}
		}

		if (selectedDifficulty == 3){

			if (game.language == 0){

				cout << spaces << EnEASY << endl;
				cout << spaces << EnMEDIUM << endl;
				cout << spaces << EnHARD << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << endl << endl << endl;
				cout << spaces << EnBACK << endl;
				SetConsoleTextAttribute(hConsole, Blue);
			}

			if (game.language == 1){

				cout << spaces << UaEASY << endl;
				cout << spaces << UaMEDIUM << endl;
				cout << spaces << UaHARD << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << endl << endl << endl;
				cout << spaces << UaBACK << endl;
				SetConsoleTextAttribute(hConsole, Blue);
			}
		}


		char selectDifficultyPress = ' ';
		bool isPressedEnter = false;

		selectDifficultyPress = _getch();

		switch (selectDifficultyPress){
		case 72:
		{
			--selectedDifficulty;
			break;
		}

		case 75:
		{
			--selectedDifficulty;
			break;
		}

		case 77:
		{
			++selectedDifficulty;
			break;
		}

		case 80:
		{
			++selectedDifficulty;
			break;
		}

		case 13:
		{
			isPressedEnter = true;
			break;
		}

		default:
		{
			break;
		}
		}


		if (selectedDifficulty < 0) selectedDifficulty += 4;
		if (selectedDifficulty > 3) selectedDifficulty -= 4;

		if (selectedDifficulty < 3 && isPressedEnter)
			game.difficulty = selectedDifficulty;


		if (!isPressedEnter){
			chooseDifficulty();
		}

		if (isPressedEnter){

			if (selectedDifficulty == 3)
				chooseOption();

			else
				chooseDifficulty();
		}
	}

	int chooseOption(){

		string EnCHOOSELANGUAGE = "CHOOSE LANGUAGE";
		string EnCHOOSEDIFFICULTY = "CHOOSE DIFFICULTY";
		string UaCHOOSELANGUAGE = "  ¬»¡≈–";
		UaCHOOSELANGUAGE += I;
		UaCHOOSELANGUAGE += "“‹ ÃŒ¬”";
		string UaCHOOSEDIFFICULTY = "¬»¡≈–";
		UaCHOOSEDIFFICULTY += I;
		UaCHOOSEDIFFICULTY += "“‹ — À¿ƒÕ";
		UaCHOOSEDIFFICULTY += I;
		UaCHOOSEDIFFICULTY += "—“‹";

		system("cls");
		const string spaces = "                               ";
		SetConsoleTextAttribute(hConsole, Blue);
		for (size_t i = 0; i < 10; ++i)
			cout << endl;

		if (selectedOfTwo == 0){

			if (game.language == 0){

				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << " " << EnCHOOSELANGUAGE << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << spaces << EnCHOOSEDIFFICULTY << endl;
			}
			else{

				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << " " << UaCHOOSELANGUAGE << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << spaces << UaCHOOSEDIFFICULTY << endl;
			}
		}
		if (selectedOfTwo == 1){

			if (game.language == 0){

				cout << spaces << " " << EnCHOOSELANGUAGE << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << EnCHOOSEDIFFICULTY << endl;
				SetConsoleTextAttribute(hConsole, Blue);
			}
			else{

				cout << spaces << " " << UaCHOOSELANGUAGE << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << UaCHOOSEDIFFICULTY << endl;
				SetConsoleTextAttribute(hConsole, Blue);
			}
		}

		for (size_t i = 0; i < 5; ++i)
			cout << endl;
		SetConsoleTextAttribute(hConsole, LightRed);
		if (game.language == 0)
			cout << "                        PRESS ESC TO EXIT TO MAIN MENU" << endl;
		if (game.language == 1)
			cout << "                   Õ¿“»—Õ" << I << "“‹ ESC ƒÀﬂ ¬»’Œƒ” ¬ √ŒÀŒ¬Õ≈ Ã≈Õﬁ" << endl;

		char select = ' ';
		bool pressedEnter = false;
		select = _getch();

		switch (select){
		case 72:
		{
			--selectedOfTwo;
			break;
		}

		case 75:
		{
			--selectedOfTwo;
			break;
		}

		case 77:
		{
			++selectedOfTwo;
			break;
		}

		case 80:
		{
			++selectedOfTwo;
			break;
		}

		case 27:
		{
			return 0;
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

		if (selectedOfTwo < 0) selectedOfTwo += 2;
		if (selectedOfTwo > 1) selectedOfTwo -= 2;

		if (!pressedEnter)
		{
			chooseOption();
		}

		if (pressedEnter){
			if (selectedOfTwo == 0) chooseLanguage();
			else chooseDifficulty();
		}
	}
};

OptionsMenu options;