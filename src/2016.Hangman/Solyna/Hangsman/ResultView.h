#pragma once
#include "Player.h"
#include "View.h"
#include <fstream>
#include "functions.h"
#include "Printer.h"
#include "HighScoresView.h"

class ResultView: public View
{
	Player arrayOfPlayers[7];
	Player currentPlayer;
	string nameOfPlayer;
	ifstream in;
	ofstream of;
	void printingPlayersName();
	bool achievedTheHighScore();
	void sortArrayOfPlayers();
	void ifKeyIsAnArrow(int &key);
	bool checkIfArrowPressed();
public:
	ResultView(Languages l, Difficulty d);
	void draw();
	View * handle();
};

