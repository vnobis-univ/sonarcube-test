#pragma once
#include "Color.h"
#include <Windows.h>


class Printer
{
	Color fore;
	Color back;
	HANDLE& hConsole;
	int getTextColor() const;
public:
	Printer();
	Printer(Color _fore, Color _back);

	const Printer& operator << (std::string textToPrint) const;

	Printer& operator = (const Printer& p);

	friend std::ostream& operator <<(std::ostream& os, const Printer& printer);
	friend std::istream& operator >>(std::istream& is, Printer& printer);
};
