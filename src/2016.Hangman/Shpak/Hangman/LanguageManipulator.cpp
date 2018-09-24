#include "LanguageManipulator.h"
#include "MenuView.h"
#include <locale>
#include <list>
#include <string>
#include "windows.h";


Language LanguageManipulator::gameLanguage = Language::English;


void LanguageManipulator::getHowToDrawMenuOptions(std::vector<std::string>& vec, size_t optionsSize)
{
	switch (gameLanguage)
	{
		case Language::English:
		{
			for (size_t i = 0; i < optionsSize; i++)
			{
				switch (static_cast<MenuView::MenuOptions> (i))
				{
				case MenuView::MenuOptions::start:
					vec.push_back("S T A R T");
					break;

				case MenuView::MenuOptions::options:
					vec.push_back("O P T I O N S");
					break;

				case MenuView::MenuOptions::highscores:
					vec.push_back("H I G H S C O R E S");
					break;

				case MenuView::MenuOptions::exit:
					vec.push_back("E X I T");
					break;

				default:
					throw std::string("call of LanguageManipulator::getHowToDrawMenuOptions with problems");
				}
			}
		}
		break;

	case Language::Ukranian:
	{
		for (size_t i = 0; i < optionsSize; ++i)
		{
			switch (static_cast<MenuView::MenuOptions> (i))
			{
			case MenuView::MenuOptions::start:
				vec.push_back("� � � � � � � � �");
				break;

			case MenuView::MenuOptions::options:
				vec.push_back("� � � � � � � � � � � �");
				break;

			case MenuView::MenuOptions::highscores:
				vec.push_back("� � � � � � � � � �");
				break;

			case MenuView::MenuOptions::exit:
				vec.push_back("� � � I �");
				break;

			default:
				throw std::string("call of LanguageManipulator::getHowToDrawMenuOptions with problems");
			}
		}
	}
		break;

	default:
		throw std::string("call of LanguageManipulator::getHowToDrawMenuOptions with problems");
	}

}

void LanguageManipulator::setGameLanguage(Language newLanguage)
{
	switch (newLanguage)
	{
	case Language::English:
		setlocale(LC_CTYPE, "Eng");
		break;

	case Language::Ukranian:
		setlocale(LC_CTYPE, "ukr");
		break;

	default:
		throw std::string("call of LanguageManipulator::setGameLanguage with problems");
	}

	gameLanguage = newLanguage;
}

Language LanguageManipulator::getGameLanguage() const
{
	return gameLanguage;
}

int LanguageManipulator::getNumberOfLetters() const
{
	switch (gameLanguage)
	{
	case Language::English:
		return 26;

	case Language::Ukranian:
		return 32;

	default:
		throw std::string("call of LanguageManipulator::getNumberOfLetters with problems");
	}
}

std::string LanguageManipulator::getHowToDrawOptionsHeader()
{
	switch (gameLanguage)
	{
	case Language::English:
		return "O P T I O N S";

	case Language::Ukranian:
		return "� � � � � � � � � � � �";

	default:
		throw std::string("call of LanguageManipulator::getHowToDrawOptionsHeader with problems");
	}
}

void LanguageManipulator::getHowToDrawOptionsLanguage(std::vector<std::string>& vec)
{
	switch (gameLanguage)
	{
	case Language::English:
		vec.push_back("choose language");
		vec.push_back("E n g l i s h");
		vec.push_back("   /   ");
		vec.push_back("U k r a n i a n");
		break;

	case Language::Ukranian:
		vec.push_back("�����i�� ����");
		vec.push_back("� � � � i � � � � �");
		vec.push_back("   /   ");
		vec.push_back("� � � � � � � � � �");

		break;

	default:
		throw std::string("call of LanguageManipulator::getHowToDrawOptionsLanguage with problems");
	}
}

void LanguageManipulator::getHowToDrawOptionsDifficulty(std::vector<std::string>& vec)
{
	switch (gameLanguage)
	{
	case Language::English:
		vec.push_back("choose difficulty");
		vec.push_back("e a s y");
		vec.push_back("   /   ");
		vec.push_back("m e d i u m");
		vec.push_back("   /   ");
		vec.push_back("h a r d");
		break;

	case Language::Ukranian:
		vec.push_back("�����i�� ������i���");
		vec.push_back("� � � � �");
		vec.push_back("   /   ");
		vec.push_back("� � � � � � � �");
		vec.push_back("   /   ");
		vec.push_back("� � � � � � �");
		break;

	default:
		throw std::string("call of LanguageManipulator::getHowToDrawOptionsLanguage with problems");
	}
}

void LanguageManipulator::getHowToDrawOptionsColorOption(std::vector<std::string>& vec)
{
	switch (gameLanguage)
	{
	case Language::English:
		vec.push_back("choose main color");
		vec.push_back("r e d");
		vec.push_back("   /   ");
		vec.push_back("p u r p le");
		vec.push_back("   /   ");
		vec.push_back("a q u a");
		break;

	case Language::Ukranian:
		vec.push_back("�����i�� ���i�");
		vec.push_back("� � � � � � � �");
		vec.push_back("   /   ");
		vec.push_back("� i � � � � � � � �");
		vec.push_back("   /   ");
		vec.push_back("� � � � � � �");
		break;
	}
}

std::string LanguageManipulator::getHowToDrawBackButton()
{
	switch (gameLanguage)
	{
	case Language::English:
		return "*  B A C K  *";

	case Language::Ukranian:
		return "*  � � � � �  *";

	default:
		throw std::string("call of LanguageManipulator::getHowToDrawOptionsFooter with problems");
	}

}

void LanguageManipulator::getAlphabet(std::vector<char>& vec)
{
	switch (gameLanguage)
	{
		case Language::English:
			for (char i = 'A'; i <= 'Z'; ++i)
			{
				vec.push_back(i);
			}

			break;
	
		case Language::Ukranian:
			for (char i = '�'; i <= '�'; ++i)
			{
				if (i == '�' || i == '�' || i == '�')
					continue;

				vec.push_back(i);

				if (i == '�')
					 vec.push_back('�');

				if (i == '�')
				{ 
					vec.push_back('I');
					vec.push_back('�');
				}				
			}

			break;

		default:
			throw std::string("call of LanguageManipulator::getAlphabet with problems");
	}	
}

std::string LanguageManipulator::getHowToDrawHint()
{
	switch (gameLanguage)
	{
	case Language::English:
		return "(use only english letters)";
		break;

	case Language::Ukranian:
		return "(�������������� ���� ��������i �i����)";
		break;

	default:
		throw std::string("call of LLanguageManipulator::getHowToDrawHint with problems");
	}
}

void LanguageManipulator::varifyLetters(std::list<std::string>& list)
{
	std::list<std::string>::iterator itEnd = list.end();

	switch (gameLanguage)
	{
	case Language::English:
		for (std::list<std::string>::iterator it = list.begin(); it != itEnd; ++it)
		{
			for (size_t j = 0; j < it->length(); ++j)
			{
				bool isGoodLetter = false;

				for (char k = 'a'; k <= 'z'; ++k)
				{
					// check whether letter is in lower case

					if ((*it)[j] == k)
					{
						isGoodLetter = true;
						break;
					}
				}

				if (!isGoodLetter)
				{
					// check whether letter is in upper case
					for (char k = 'A'; k <= 'Z'; ++k)
					{
						if ((*it)[j] == k)
						{
							isGoodLetter = true;
							break;
						}
					}
				}

				if (!isGoodLetter)
				{
					throw std::string("Problem in file with words (bad symbol)");
				}
			}
		}
		break;

	case Language::Ukranian:
		
		for (std::list<std::string>::iterator it = list.begin(); it != itEnd; ++it)
		{
			for (size_t j = 0; j < it->length(); ++j)
			{
				bool isGoodLetter = false;

				for (char k = '�'; k <= '�'; ++k)
				{
					// check whether letter is in lower case

					if (k == '�' || k == '�' || k == '�')
						continue;


					if ((*it)[j] == k || (*it)[j] == '�' || (*it)[j] == 'i' || (*it)[j] == '�')
					{
						isGoodLetter = true;
						break;
					}
				}

				if (!isGoodLetter)
				{
					// check whether letter is in upper case
					for (char k = '�'; k <= '�'; ++k)
					{
						if (k == '�' || k == '�' || k == '�')
							continue;


						if ((*it)[j] == k || (*it)[j] == '�' || (*it)[j] == 'I' || (*it)[j] == '�')
						{
							isGoodLetter = true;
							break;
						}
					}
				}

				if (!isGoodLetter)
				{
					throw std::string("Problem in file with words (bad symbol)");
				}
			}
		}
		break;

	default:
		throw std::string("call of LanguageManipulator::varifyLetters with problems");
	}

}

void LanguageManipulator::makeAllLettersBig(std::list<std::string>& list)
{
	// enable to write in file words in small or big case ("CaR" and "car" is allowed)

	std::list<std::string>::iterator itEnd = list.end();

	switch (gameLanguage)
	{
	case Language::English:
		for (std::list<std::string>::iterator it = list.begin(); it != itEnd; ++it)
			for (size_t j = 0; j < it->length(); ++j)
			{
				for (char k = 'a'; k <= 'z'; ++k)
				{
					if ((*it)[j] == k)
					{
						(*it)[j] = k - 32; // in ASCII big letter has code: (code of small letter - 32)
						break;
					}
				}
			}

		break;

	case Language::Ukranian:
		
		for (std::list<std::string>::iterator it = list.begin(); it != itEnd; ++it)
			for (size_t j = 0; j < it->length(); ++j)
			{
				for (char k = '�'; k <= '�'; ++k)
				{
					if ((*it)[j] == k)
					{
						(*it)[j] = k - 32; // in ASCII big letter has code: (code of small letter - 32)
						break;
					}

					if ((*it)[j] == '�')
						(*it)[j] = '�';

					if ((*it)[j] == 'i')
						(*it)[j] = 'I';

					if ((*it)[j] == '�')
						(*it)[j] = '�';
				}
			}

		break;

	default:
		throw std::string("call of LanguageManipulator::makeAllLettersBig with problems");
	}

}

void LanguageManipulator::getNewResultMessage(std::vector<std::string>& vec)
{
	switch (gameLanguage)
	{
	case Language::English:
		vec.push_back("You achived the highscore");
		vec.push_back("Please enter you name");
		break;

	case Language::Ukranian:
		vec.push_back("�� ������� ������ �������");
		vec.push_back("����i�� ��� i�'�");
		break;

	default:
		throw std::string("call of LanguageManipulator::getNewResultMessage with problems");
	}

}

char LanguageManipulator::getWhichLetterIsPressed(char ch)
{
	switch (gameLanguage)
	{
	case Language::English:
		return ch;

	case Language::Ukranian:
	{
		for (char i = '�'; i <= '�'; ++i)
		{
			if (i == '�' || i == '�' || i == '�')
				continue;

			if (ch == i - 64)
				return  i;

			if (ch + 32 == i - 64)
				return i - 32;
		}

		if (ch == 63) return 'i';

		char otherLetters[15] = { '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�' };

		for (size_t i = 0; i < 15; ++i)
		{
			if (ch == otherLetters[i] - 16)
				return otherLetters[i];

			if (ch + 32 == otherLetters[i] - 16)
				return otherLetters[i] - 32;
		}
	}
		break;
	default:
		throw std::string("call of LanguageManipulator::getWhichLetterIsPressed with problems");
	}

	return 0;
}

void LanguageManipulator::getStandartResultMessage(std::vector<std::string>& vec)
{
	switch (gameLanguage)
	{
	case Language::English:
		vec.push_back("You haven't achived the highscore");
		break;

	case Language::Ukranian:
		vec.push_back("�� �� ������� ������ �������");
		break;

	default:
		throw std::string("call of LanguageManipulator::getStandartResultMessage with problems");
	}
}

std::string LanguageManipulator::getHowToDrawHighscoresHeader()
{
	switch (gameLanguage)
	{
	case Language::English:
		return "H I G H S C O R E S";

	case Language::Ukranian:
		return "� � � � � � � � � �";

	default:
		throw std::string("call of LanguageManipulator::getHowToDrawHighscoresHeader with problems");
	}
}

void LanguageManipulator::getHowToDrawTableMainRow(std::vector<std::string>& vec)
{
	switch (gameLanguage)
	{
	case Language::English:
		vec.push_back("e n g l i s h");
		vec.push_back("u k r a i n i a n");
		break;

	case Language::Ukranian:
		vec.push_back("� � � � i � � � � �");
		vec.push_back("� � � � � � � � � �");
		break;

	default:
		throw std::string("call of LanguageManipulator::getStandartResultMessage with problems");
	}
}

void LanguageManipulator::getLevelsNames(std::vector<std::string>& vec)
{
	switch (gameLanguage)
	{
	case Language::English:
		vec.push_back("easy");
		vec.push_back("medium");
		vec.push_back("hard");
		break;

	case Language::Ukranian:
		vec.push_back("�����");
		vec.push_back("��������");
		vec.push_back("�������");
		break;

	default:
		throw std::string("call of LanguageManipulator::getLevelsNames with problems");
	}
}