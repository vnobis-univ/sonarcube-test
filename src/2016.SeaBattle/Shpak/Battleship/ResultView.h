#pragma once
#include "View.h"
#include <string>
#include <vector>


class ResultView : public View
{
	int newScore;

	std::vector<char> possibleLetters;

public:
	ResultView(int);

	void draw();

	View* handle();

private:
	int newHighscoreHandler(std::vector<int>&);

	void drawNotNewHighscoresCase();

	void drawNewHighscoresCase();

	bool varifyButtonCodeInput(char);

	std::string getName();

	void drawEnteringName(std::string);
};

