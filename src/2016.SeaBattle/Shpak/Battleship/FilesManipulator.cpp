#include <fstream>
#include "FilesManipulator.h"
#include "LanguageManipulator.h"
#include "GameLogicComputer.h"
#include "View.h"


void FilesManipulator::getLogo(std::vector<std::string>& vec)
{
	std::ifstream in("logo.txt");

	while (!in.eof())
	{
		std::string str;

		std::getline(in, str, '\n');

		vec.push_back(str);
	}
}

std::string FilesManipulator::getFileName(GameLogicComputer::Difficulty dif)
{
	std::string fileName = "";

	switch (LanguageManipulator().getGameLanguage())
	{
	case Language::English:
		fileName += "English";
		break;

	case Language::Ukranian:
		fileName += "Ukranian";
		break;

	default:
		throw std::string("call of FilesManipulator::getFileNameWithWords with problems");
	}


	switch (dif)
	{
	case GameLogicComputer::Difficulty::easy:
		fileName += "Easy";
		break;

	case GameLogicComputer::Difficulty::hard:
		fileName += "Hard";
		break;

	default:
		throw std::string("call of FilesManipulator::getFileNameWithWords with problems");
	}

	fileName += ".txt";

	return fileName;
}

void FilesManipulator::getHighscores(std::vector<std::string>& names, 
	std::vector<int>& scores,
	GameLogicComputer::Difficulty dif)
{
	std::ifstream in("highscores" + getFileName(dif));

	std::string tempName;
	int score;

	while (in >> tempName >> score)
	{
		names.push_back(tempName);
		scores.push_back(score);
	}
}

void FilesManipulator::writeHighscores(std::vector<std::string>& names, std::vector<int>& scores)
{
	std::ofstream out("highscores" + getFileName());

	for (size_t i = 0; i < names.size(); ++i)
	{
		out << names[i] << ' ' << scores[i] << '\n';
	}
}

void FilesManipulator::getHowToDrawField(std::vector<std::string>& vec)
{
	std::ifstream in("field.txt");
	
	while (!in.eof())
	{
		std::string str;

		std::getline(in, str, '\n');

		vec.push_back(str);
	}
}