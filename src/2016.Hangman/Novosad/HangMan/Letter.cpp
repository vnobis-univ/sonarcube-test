#include "Letter.h"

Letter::Letter()
{
}

char Letter::getLetter()
{
	return letter;
}

Visibility Letter::getVisibility()
{
	return visibility;
}

void Letter::setLetter(char c)
{
	letter = c;
}

void Letter::setVisibility(Visibility v)
{
	visibility = v;
}
