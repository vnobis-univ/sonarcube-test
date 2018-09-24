#pragma once
#include "Utils.h"
#include <iostream>
#include <vector>
#include "View.h"

using std::vector;


struct Letter
{
	char letter;
	bool clicked;

	Letter(char m_letter = ' ', bool m_clikked = false);
};


class Alphabet
{
	vector<Letter> alpha;
public:
	Alphabet(Language m_lang);

	int getSize();

	void print(int sel = 0 );
	Letter getLetter(int sel);
	void setCliked(int sel);
};