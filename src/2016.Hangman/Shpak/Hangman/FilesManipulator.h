#pragma once
#include "GameLogic.h"
#include <vector>
#include <list>
#include <string>

class FilesManipulator
{
public:
	void getLogo(std::vector<std::string>&);

	void getWords(std::list<std::string>&);

	void getHighscores(std::vector<std::string>&, 
		std::vector<std::pair<int, int>>&, 
		GameLogic::Difficulty = GameLogic().getGameDifficulty());

	void writeHighscores(std::vector<std::string>&, std::vector<std::pair<int, int>>&);

private:
	std::string getFileName(GameLogic::Difficulty = GameLogic().getGameDifficulty());
};

