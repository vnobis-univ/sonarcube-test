#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
using namespace std;

static int consoleWidth = 50;
static int consoleHeught = 20;
enum Languages
{
	English,
	Ukrainian
};
enum Difficulty
{
	Easy,
	Medium,
	Hard
};
class View
{
protected:
	Difficulty dif;
	Languages lang;
public:
	View(Languages l, Difficulty d);
	virtual void draw() = 0;
    virtual View* handle() = 0;
	void clean();
};

