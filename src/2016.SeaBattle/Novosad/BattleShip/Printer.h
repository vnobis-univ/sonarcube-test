#pragma once
#include <string>
#include "Color.h"
using namespace std;

class Printer
{
private:
	Color colorOfText;
	Color colorOfBackground;
public:
	Printer();
	Printer(Color colorOfText1, Color colorOfBackground1);
	void print(string text);
};