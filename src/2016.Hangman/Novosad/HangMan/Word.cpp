#include "Word.h"
#include "Visibility.h"


Word::Word()
{
}

int Word::getLength()
{
	return length;
}

Letter* Word::getLetters()
{
	return letters;
}

Word::Word(string str)
{
	length = str.length();
	letters = new Letter[length];
	for (int i = 0; i < length; i++)
	{
		letters[i].setLetter(str[i]);
		letters[i].setVisibility(Visibility::Invisible);
	}
}

ostream& operator << (ostream& out, Word& word)
{
	for (int i = 0; i < word.length; i++)
	{
		if (word.letters[i].getVisibility() == Visibility::Visible)
		{
			out << word.letters[i].getLetter();
		}
		else
		{
			out << " ";
		}
	}
	return out;
}
