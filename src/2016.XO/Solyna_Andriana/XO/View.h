#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
using namespace std;


class View
{
public:
	virtual void draw() = 0;
    virtual View* handle() = 0;
	void clean();
};

struct Scores
{
	string name;
	unsigned score;
	Scores();
	friend istream & operator >>(istream &in, Scores &s);
	friend ostream & operator <<(ostream &os, const Scores &s);
};