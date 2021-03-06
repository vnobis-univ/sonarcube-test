#pragma once
#include <iostream>
#include <string>



enum class Color {
	Black, Blue, Green, Aqua, Red, Purple, Yellow, White, Gray,
	LightBlue, LightGreen, LightAqua, LightRed, LightPurple, LightYellow, LightWhite
};

class Printer
{
private:
	Color words;
	Color back;

public:
	Printer::Printer(Color m_words = Color::LightWhite, Color m_back = Color::Black);
	void print(std::string s);
	void print(int num);

	void printOnCenter(int line, std::string);
};