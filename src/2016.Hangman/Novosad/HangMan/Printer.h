#pragma once
#include <string>
#include "Color.h"
#include "Word.h"
using namespace std;

class Printer
{
private:
	Color color_of_text;
	Color color_of_background;
public:
	Printer();
	Printer(Color color_of_text1, Color color_of_background1);
	void print(string text);
	void print(Word word);
};

