#include "LanguageManipulator.h"
#include "MenuView.h"
#include <locale>
#include <list>
#include <string>


Language LanguageManipulator::gameLanguage = Language::English;

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


//methods for options

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
				vec.push_back("Р О З П О Ч А Т И");
				break;

			case MenuView::MenuOptions::options:
				vec.push_back("Н А Л А Ш Т У В А Н Н Я");
				break;

			case MenuView::MenuOptions::highscores:
				vec.push_back("Р Е З У Л Ь Т А Т И");
				break;

			case MenuView::MenuOptions::exit:
				vec.push_back("В И Х I Д");
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

std::string LanguageManipulator::getHowToDrawOptionsHeader()
{
	switch (gameLanguage)
	{
	case Language::English:
		return "O P T I O N S";

	case Language::Ukranian:
		return "Н А Л А Ш Т У В А Н Н Я";

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
		vec.push_back("виберiть мову");
		vec.push_back("А н г л i й с ь к а");
		vec.push_back("   /   ");
		vec.push_back("У к р а ї н с ь к а");

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
		vec.push_back("h a r d");
		break;

	case Language::Ukranian:
		vec.push_back("виберiть складнiсть");
		vec.push_back("л е г к о");
		vec.push_back("   /   ");
		vec.push_back("с к л а д н о");
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
		vec.push_back("виберiть колiр");
		vec.push_back("ч е р в о н и й");
		vec.push_back("   /   ");
		vec.push_back("ф i о л е т о в и й");
		vec.push_back("   /   ");
		vec.push_back("г о л у б и й");
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
		return "*  Н А З А Д  *";

	default:
		throw std::string("call of LanguageManipulator::getHowToDrawOptionsFooter with problems");
	}

}

// methods for choosing game

void LanguageManipulator::getHowToDrawGameOptions(std::vector<std::string>& vec)
{
	switch (gameLanguage)
	{
	case Language::English:
		vec.push_back("S I N G L E  G A M E");
		vec.push_back("O N L I N E  G A M E");
		break;

	case Language::Ukranian:
		vec.push_back("О Ф Ф Л А Й Н  Г Р А");
		vec.push_back("О Н Л А Й Н  Г Р А");
		break;

	default:
		throw std::string("call of LanguageManipulator::getHowToDrawGameOptions with problems");
	}
}

void LanguageManipulator::getHowToDrawOnlineGameOptions(std::vector<std::string>& vec)
{
	switch (gameLanguage)
	{
	case Language::English:
		vec.push_back("H O S T  G A M E");
		vec.push_back("J O I N  G A M E");
		break;

	case Language::Ukranian:
		vec.push_back("С Т В О Р И Т И  Г Р У");
		vec.push_back("З Н А Й Т И  Г Р У");
		break;

	default:
		throw std::string("call of LanguageManipulator::getHowToDrawOnlineGameOptions with problems");
	}
}

// methods for game

void LanguageManipulator::getLettersAboveField(std::vector<char>& vec)
{
	switch (gameLanguage)
	{
	case Language::English:
		for (char i = 'a'; i <= 'j'; ++i)
		{
			vec.push_back(i);
		}
		break;

	case Language::Ukranian:
		for (char i = 'а'; i <= 'е'; ++i)
		{
			vec.push_back(i);
		}
		vec.push_back('є');
		vec.push_back('ж');
		vec.push_back('з');
		vec.push_back('i');
		break;

	default:
		throw std::string("call of LanguageManipulator::getLettersAboveField with problems");
	}
}

std::string LanguageManipulator::getHowToDrawScore()
{
	switch (gameLanguage)
	{
	case Language::English:
		return "Score: ";

	case Language::Ukranian:
		return "Рахунок: ";
	}
}

// methods for hints for game

void LanguageManipulator::getHowToDrawShipPlacementHint(std::vector<std::string>& vec)
{
	switch (gameLanguage)
	{
	case Language::English:
		vec.push_back("Use arrows to move ship and enter to place it.");
		vec.push_back("Use q button to rotate ship.");
		break;

	case Language::Ukranian:
		vec.push_back("Використовуйте стрiлочки для розмiщення кораблiв.");
		vec.push_back("Використовуйте кнопку q для повороту корабля.");
		break;
	}
}

void LanguageManipulator::getHowToDrawWin(std::vector<std::string>& vec)
{
	switch (gameLanguage)
	{
	case Language::English:
		vec.push_back("You win this game.");
		vec.push_back("Press any key to continue..");
		break;

	case Language::Ukranian:
		vec.push_back("Ви виграли гру.");
		vec.push_back("Натиснiсть будь-яку кнопку щоб продовжити..");
		break;
	}
}

void LanguageManipulator::getHowToDrawLose(std::vector<std::string>& vec)
{
	switch (gameLanguage)
	{
	case Language::English:
		vec.push_back("You lose this game.");
		vec.push_back("Press any key to continue..");
		break;

	case Language::Ukranian:
		vec.push_back("Ви програли гру.");
		vec.push_back("Натиснiсть будь-яку кнопку щоб продовжити..");
		break;
	}
}

void LanguageManipulator::getHowToDrawWaitUntilJoin(std::vector<std::string>& vec)
{
	switch (gameLanguage)
	{
	case Language::English:
		vec.push_back("Your roomId: ");
		vec.push_back("Waiting until player join..");
		break;

	case Language::Ukranian:
		vec.push_back("Номер вашої кiмнати: ");
		vec.push_back("Очiкування поки зайде гравець..");
		break;
	}
}

void LanguageManipulator::getHowToDrawWaintUntilMakeMove(std::vector<std::string>& vec)
{
	switch (gameLanguage)
	{
	case Language::English:
		vec.push_back("Waiting until player choose..");
		break;

	case Language::Ukranian:
		vec.push_back("Очiкування поки гравець робить свiй вибiр..");
		break;
	}
}

void LanguageManipulator::getHowToDrawGetIdForGame(std::vector<std::string>& vec)
{
	switch (gameLanguage)
	{
	case Language::English:
		vec.push_back("Enter id: ");
		break;
		
	case Language::Ukranian:
		vec.push_back("Введiть номер кiмнати: ");
		break;
	}
}

// methods for resultView

std::string LanguageManipulator::getHowToDrawHint()
{
	switch (gameLanguage)
	{
	case Language::English:
		return "(use only english letters)";
		break;

	case Language::Ukranian:
		return "(використовуйте лише українськi лiтери)";
		break;

	default:
		throw std::string("call of LLanguageManipulator::getHowToDrawHint with problems");
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
		vec.push_back("Ви досягли нового рекорду");
		vec.push_back("Введiть своє iм'я");
		break;

	default:
		throw std::string("call of LanguageManipulator::getNewResultMessage with problems");
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
		for (char i = 'А'; i <= 'Я'; ++i)
		{
			if (i == 'Ъ' || i == 'Э' || i == 'Ы')
				continue;

			vec.push_back(i);

			if (i == 'Е')
				vec.push_back('Є');

			if (i == 'И')
			{
				vec.push_back('I');
				vec.push_back('Ї');
			}
		}

		break;

	default:
		throw std::string("call of LanguageManipulator::getAlphabet with problems");
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
		for (char i = 'а'; i <= 'я'; ++i)
		{
			if (i == 'Ъ' || i == 'Э' || i == 'Ы')
				continue;

			if (ch == i - 64)
				return  i;

			if (ch + 32 == i - 64)
				return i - 32;
		}

		if (ch == 63) return 'i';

		char otherLetters[15] = { 'ц', 'у', 'ш', 'щ', 'х', 'ф', 'р', 'є', 'я', 'ч', 'с', 'т', 'ь', 'ю', 'ї' };

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
		vec.push_back("Ви не досягли нового рекорду");
		break;

	default:
		throw std::string("call of LanguageManipulator::getStandartResultMessage with problems");
	}
}

// methods for highscores

std::string LanguageManipulator::getHowToDrawHighscoresHeader()
{
	switch (gameLanguage)
	{
	case Language::English:
		return "H I G H S C O R E S";

	case Language::Ukranian:
		return "Р Е З У Л Ь Т А Т И";

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
		vec.push_back("а н г л i й с ь к а");
		vec.push_back("у к р а ї н с ь к а");
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
		vec.push_back("hard");
		break;

	case Language::Ukranian:
		vec.push_back("легко");
		vec.push_back("складно");
		break;

	default:
		throw std::string("call of LanguageManipulator::getLevelsNames with problems");
	}
}