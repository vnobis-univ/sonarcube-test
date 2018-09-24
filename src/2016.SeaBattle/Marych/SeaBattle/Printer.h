#pragma once

#include <string>
#include <windows.h> 
#include "Color.h"

class Printer
{
	Color text;
	Color background;

	HANDLE& hConsole;

	int getTextAttribute() const;
public:
	Printer();
	Printer(Color _text, Color _background);

	const Printer& operator<< (std::string textToPrint) const;
	void print(char) const;
	Printer& operator = (const Printer& p);
	bool operator== (const Printer& p);

	friend std::ostream& operator <<(std::ostream& os, const Printer& printer);
	friend std::istream& operator >>(std::istream& is, Printer& printer);
};