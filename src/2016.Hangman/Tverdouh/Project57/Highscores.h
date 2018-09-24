#pragma once
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class HighscoreView 
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
		ifstream in("Score1.txt");
		for (int i = 0; i < 5; i++)
			in >> b[i];

		for (int i = 0; i < 5; i++)
			cout << endl;
		for (int i = 0; i < 5; i++)
			cout << "                                     " << b[i] << endl;
		SetColor(8, 4);
		printInTheCentre("BACK", 14, 80);
		SetColor(4, 8);

	}
};
