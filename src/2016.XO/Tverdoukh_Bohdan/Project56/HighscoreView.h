#pragma once
#include "View.h"
#include "MenuView.h"
#include <ctime>
#include "FunctionsForText.h"
#include "FunctionsForField.h"
#include "ResaultView.h"
#include <list>


class HighscoreView :public View
{
	int score;
	string name;
public:
	HighscoreView(){}
	friend istream& operator>>(istream& in, HighscoreView& winner)
	{

		in >> winner.name >> winner.score;
		return in;
	}
	friend ostream& operator<<(ostream& out, const HighscoreView& winner)
	{
		out << winner.name << "   " << winner.score;
		return out;
	}
	
	void draw()
	{ 
		HighscoreView b[5];
		ifstream in("Text.txt");
		for (int i = 0; i < 5; i++)
			in >> b[i];

		for (int i = 0; i < 5; i++)
			cout << endl;
		for (int i = 0; i < 5; i++)
			cout << "                                   " << b[i] << endl;
		SetColor(0,7);
		printInTheCentre("BACK", 12, 80);
		SetColor(7, 0);

	}
};

