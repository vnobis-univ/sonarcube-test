#pragma once
#include <iostream>
#include <string>

enum class Color
{
	Black,
	Blue,
	Green,
	Aqua,
	Red,
	Purple,
	Yellow,
	White,
	Gray,
	LightBlue,
	LightGreen,
	LightAqua,
	LightRed,
	LightPurple,
	LightYellow,
	LightWhite
};


class Printer
{
private:
	Color words;
	Color background;

public:

	Printer::Printer(Color m_words = Color::LightWhite, Color m_background = Color::Black);


	template<typename T>
	void print(T text);
	void printOnCenter(int line, std::string);

};
