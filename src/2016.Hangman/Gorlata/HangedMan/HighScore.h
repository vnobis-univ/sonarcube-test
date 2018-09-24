#pragma once

#include <iostream>
#include <string>
#include "View.h"
#include <vector>

using std::string;
using std::istream;
using std::ostream;
using std::endl;
using std::vector;

struct Row
{
	string player;
	int score;
	friend ostream & operator << (ostream& os, const Row& obj);
	friend istream & operator >>(istream& is, Row& obj);


	bool operator < (const Row& obj)const;
};


class HighScore :public View
{
private:
	vector<Row> easy;
	vector<Row> med;
	vector<Row> hard;
public:

	HighScore(Language m_lang = Language::ENG);

	void HighScore::draw();
	View* HighScore::handle();

};