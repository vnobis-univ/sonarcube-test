#pragma once
#include <iostream>
#include <string>
#include "View.h"

using std::string;
using std::istream;
using std::ostream;
using std::endl;



struct hScore
{
	string player;
	int score;
	friend ostream & operator << (ostream& os, const hScore& obj);
	friend istream & operator >>(istream& is, hScore& obj);
	string hScore::getName();
	int hScore::getScore();

	bool operator <(const hScore& obj)const;
};


class HighScore : public View
{
private:
	hScore* scores;
	size_t size;
	void HighScore::sort();

public:
	HighScore();

	int HighScore::getLow();
	void HighScore::draw();
	View* HighScore::handle();

	
};

