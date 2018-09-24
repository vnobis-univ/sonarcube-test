#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include "Navigation.h"

class LettersManipulator
{
public:
	enum class LetterState
	{
		default,
		right,
		wrong
	};

private:
	static int spaceBetweenChars;
	static int spaceBetweenRows;

	COORD whereLettersStarts;

	std::vector<char> letters;
	std::vector<LetterState> states;

	int numberOfLetters;
	int hoverLetter;

public:
	LettersManipulator();

	void drawLetters();

	void handleMove(Button);

	char getWhichSelected() const;

	void setNewState(LetterState);

	void renewStates();

	bool checkIfUsed();

	std::vector<char> getLetters() const;

private:
	void drawOneLetter(size_t) const;
};

