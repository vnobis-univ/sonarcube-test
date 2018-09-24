#pragma once
#include "GameLogicComputer.h"
#include <vector>
#include <list>
#include <string>

class FilesManipulator
{
public:
	void getLogo(std::vector<std::string>&);

	void getHighscores(std::vector<std::string>&, std::vector<int>&, 
			          GameLogicComputer::Difficulty = static_cast<GameLogicComputer::Difficulty>(getGameDifficulty()));

	void writeHighscores(std::vector<std::string>&, std::vector<int>&);

	void getHowToDrawField(std::vector< std::string>&);

	private:
	std::string getFileName(GameLogicComputer::Difficulty = static_cast<GameLogicComputer::Difficulty>(getGameDifficulty()));
};

