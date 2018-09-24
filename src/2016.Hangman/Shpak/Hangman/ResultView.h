#pragma once
#include "View.h"
#include <string>
#include <vector>


class ResultView : public View
{
	int newScore;
	int newNumberLetters;

	std::vector<char> possibleLetters;

public:
	ResultView(int, int, std::vector<char>);

	void draw();

	View* handle();

private:
	int newHighscoreHandler(std::vector<std::pair<int, int>>&);

	void drawNotNewHighscoresCase();

	void drawNewHighscoresCase();

	bool varifyButtonCodeInput(char);

	std::string getName();

	void drawEnteringName(std::string);
};

