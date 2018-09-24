#pragma once
#include "View.h"
#include "Player.h"
#include <fstream>
#include "HighScoresView.h"
class ResultView : public View
{
	static const int size = 10;
	Player arrayOfPlayers[size];
	Player currentPlayer;
	string nameOfPlayer;
	ifstream in;
	ofstream of;
	void printingPlayersName();
	bool achievedTheHighScore();
	void sortArrayOfPlayers();
	void ifKeyIsAnArrow(int &key);
public:
	ResultView(Languages l, TypeOfGame t);
	void draw();
	View * handle();
};

