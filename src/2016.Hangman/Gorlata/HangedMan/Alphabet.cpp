#include "Alphabet.h"
#include "Utils.h"
#include "Printer.h"
#include <string>


using namespace std;

Letter::Letter(char m_letter, bool m_clikked) :
	letter(m_letter),
	clicked(m_clikked)
	{};

Alphabet::Alphabet(Language m_lang) 
{
	if (m_lang == Language::ENG)
	{
		alpha = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
			'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	}
	else
	{
		alpha = { 'À', 'Á', 'Â', 'Ã', '¥', 'Ä', 'Å', 'ª', 'Æ', 'Ç', 'È', '²', '¯', 'É',
			'Ê', 'Ë', 'Ì', 'Í', 'Î', 'Ï', 'Ð', 'Ñ', 'Ò', 'Ó', 'Ô', 'Õ', 'Ö', '×', 'Ø', 'Ù', 'Ü', 'Þ', 'ß', '\'' };
	}
}
int Alphabet::getSize()
{
	return alpha.size();
}
;

void Alphabet::print(int sel)
{
	int x = 15;
	int y = 20;

	if (alpha.size() == 34)
	{
		x = 8;
	}

	for (int i = 0; i < alpha.size(); ++i)
	{
		moveCursorTo(x, y);
		if (i == sel)
		{
			greenOnBlack.print(alpha[i].letter);
		}
		else if (alpha[i].clicked == true)
		{
			lightPurpleOnBlack.print(alpha[i].letter);
		}
		else
		{
			purleOnBlack.print(alpha[i].letter);
		}
		x = x + 2;
	}
}

Letter Alphabet::getLetter(int sel)
{
	return alpha[sel];
}

void Alphabet::setCliked(int sel)
{
	alpha[sel].clicked = true;
}


