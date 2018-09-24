#include "Alphabet.h"
#include "ConsoleUtils.h"

using namespace std;

Alphabet::Char::Char(char l, bool used) : ch(l), wasUsed(used) {}

Alphabet::Alphabet(Lang lang)
{
	switch (lang)
	{
	case Lang::ENG:
		vec = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
			'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
		break;
	case Lang::UKR:
		vec = { 'À', 'Á', 'Â', 'Ã', '¥', 'Ä', 'Å', 'ª', 'Æ', 'Ç', 'È', '²', '¯', 'É', 'Ê', 'Ë','Ì',
			'Í', 'Î', 'Ï', 'Ð', 'Ñ', 'Ò', 'Ó', 'Ô', 'Õ', 'Ö', '×', 'Ø', 'Ù', 'Ü', 'Þ', 'ß', '\'' };
		break;
	}
}

void Alphabet::reset()
{
	for (auto& i : vec)
		i.wasUsed = false;
}


void Alphabet::setUsed(char c)
{
	for (auto& i : vec)
	{
		if (i.ch == c)
		{
			i.wasUsed = true;
			break;
		}
	}
}

bool Alphabet::validateKeypress(int c)
{
	char ch = toupper(char(c));

	for (auto& i : vec)
		if (i.ch == ch && !i.wasUsed)
			return true;

	return false;
}

ostream& operator<<(ostream& os, const Alphabet& obj)
{
	moveTo((consoleWidth - obj.vec.size()) / 2 - 5, 18);
	for (int i = 0; i < obj.vec.size(); ++i)
	{
		obj.vec[i].wasUsed ? yellow.setColor() : white.setColor();
		cout << obj.vec[i].ch << " ";

		if (i == obj.vec.size() / 2 + 4)
			moveTo((consoleWidth - obj.vec.size() + i) / 2 - 5, 20);
	}

	return os;
}
