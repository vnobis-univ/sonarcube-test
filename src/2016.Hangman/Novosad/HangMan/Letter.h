#pragma once
#include "Visibility.h"
class Letter
{
private:
	char letter;
	Visibility visibility;
public:
	Letter();
	char getLetter();
	Visibility getVisibility();
	void setLetter(char c);
	void setVisibility(Visibility v);
};

