#pragma once
#include <vector>
#include <string>
#include <list>

enum class Language
{
	English,
	Ukranian
};


class LanguageManipulator
{
	static Language gameLanguage;

public:
	Language getGameLanguage() const;

	int getNumberOfLetters() const;

	void setGameLanguage(Language);

	std::string getHowToDrawBackButton();

	// methods for main menu
	void getHowToDrawMenuOptions(std::vector<std::string>&, size_t);

	// methods for options 
	std::string getHowToDrawOptionsHeader();

	void getHowToDrawOptionsLanguage(std::vector<std::string>&);

	void getHowToDrawOptionsDifficulty(std::vector<std::string>&);

	void getHowToDrawOptionsColorOption(std::vector<std::string>&);

	//methods for game
	void getAlphabet(std::vector<char>&);

	void makeAllLettersBig(std::list<std::string>&);

	void varifyLetters(std::list<std::string>&);

	// method for resultView

	void getNewResultMessage(std::vector<std::string>&);

	void getStandartResultMessage(std::vector<std::string>&);

	std::string getHowToDrawHint();

	char getWhichLetterIsPressed(char);

	// methods for highscores

	std::string getHowToDrawHighscoresHeader();

	void getHowToDrawTableMainRow(std::vector<std::string>&);

	void getLevelsNames(std::vector<std::string>&);
};

