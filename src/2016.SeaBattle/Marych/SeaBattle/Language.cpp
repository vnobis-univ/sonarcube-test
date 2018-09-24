#include "Language.h"
#include <string>

Language language = Language::ENGLISH;//our starter language

void setLangToEng()
{
	setlocale(LC_ALL, "English");
	language = Language::ENGLISH;
}

void setLangToUkr()
{
	setlocale(LC_ALL, "Ukrainian");
	language = Language::UKRAINIAN;
}

void setOptionForStartMenu(std::string* &options)
{
	if (language == Language::ENGLISH)
	{
		setLangToEng();
		options[0] = "New Game";
		options[1] = "High Scores";
		options[2] = "Options";
		options[3] = "Exit";
	}
	else if (language == Language::UKRAINIAN)
	{
		setLangToUkr();
		options[0] = "Нова Гра";
		options[1] = "Результати";
		options[2] = "Параметри";
		options[3] = "Вихiд";
	}
}
void setOptionForOptionMenu(std::string* &options)
{
	if (language == Language::ENGLISH)
	{
		setLangToEng();
		options[0] = "Change language";
		options[1] = "Change color";
		options[2] = "Back";
	}
	else if (language == Language::UKRAINIAN)
	{
		setLangToUkr();
		options[0] = "Змiнити мову";
		options[1] = "Змiнити колiр";
		options[2] = "Назад";
	}
}
void setOptionForGameMenu(std::string* &options)
{
	if (language == Language::ENGLISH)
	{
		setLangToEng();
		options[0] = "Choose your opponent:";
		options[1] = "Computer";
		options[2] = "Human(temporaly is not worked)";
		options[3] = "Exit";
	}
	else if (language == Language::UKRAINIAN)
	{
		setLangToUkr();
		options[0] = "Виберiть опонента:";
		options[1] = "Комп*ютер";
		options[2] = "Людина(поки що недоступно)";
		options[2] = "Вихiд";
	}
}