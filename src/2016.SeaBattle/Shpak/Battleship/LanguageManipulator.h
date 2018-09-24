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

	void setGameLanguage(Language);

	std::string getHowToDrawBackButton();

	// methods for main menu
	void getHowToDrawMenuOptions(std::vector<std::string>&, size_t);

	// methods for options 
	std::string getHowToDrawOptionsHeader();

	void getHowToDrawOptionsLanguage(std::vector<std::string>&);

	void getHowToDrawOptionsDifficulty(std::vector<std::string>&);

	void getHowToDrawOptionsColorOption(std::vector<std::string>&);

	// methods for choosing game

	void getHowToDrawGameOptions(std::vector<std::string>&);

	void getHowToDrawOnlineGameOptions(std::vector<std::string>&);

	// methods for game

	void getLettersAboveField(std::vector<char>&);

	std::string getHowToDrawScore();

	// methods for hints for game

	void getHowToDrawShipPlacementHint(std::vector<std::string>&);

	void getHowToDrawWin(std::vector<std::string>&);

	void getHowToDrawLose(std::vector<std::string>&);

	void getHowToDrawWaitUntilJoin(std::vector<std::string>&);

	void getHowToDrawWaintUntilMakeMove(std::vector<std::string>&);
	
	void getHowToDrawGetIdForGame(std::vector<std::string>&);

	// method for resultView

	void getNewResultMessage(std::vector<std::string>&);

	void getStandartResultMessage(std::vector<std::string>&);

	std::string getHowToDrawHint();

	void getAlphabet(std::vector<char>&);

	char getWhichLetterIsPressed(char);

	// methods for highscores

	std::string getHowToDrawHighscoresHeader();

	void getHowToDrawTableMainRow(std::vector<std::string>&);

	void getLevelsNames(std::vector<std::string>&);
};

