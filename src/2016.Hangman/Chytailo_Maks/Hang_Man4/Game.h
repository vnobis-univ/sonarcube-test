#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>

using namespace std;

class Game
{
	
	short curI = 0;
	short curJ = 0;
	int k = 0, l = 0;
	int wrong = 0;
	int score = 0;
	int countLet = 0;
	int MaxWrong;
	char SelLetter[3][11];
	char EntKey[3][11];
	char name[50];
	char guess;
	string used = "";
	vector<string>words;
public:
	Game();
	void InputWords();
	void Selected(string, string);
	void DrawCell(short, short);
	void CheckEnd(string);
	void MainGame(string, string);
	void Exit(string);
	void draw();
};

