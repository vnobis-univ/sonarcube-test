#include <fstream>
#include "FilesManipulator.h"
#include "LanguageManipulator.h"
#include "GameLogic.h"
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

void FilesManipulator::getWords(std::list<std::string>& wordsList)
{
	std::ifstream in("words" + getFileName());

	if (!in.good())
	{
		throw std::string("problems with file opening happened in FilesManipulator::getWords");
	}

	std::string word;

	while (in >> word)
	{
		wordsList.push_back(word);
	}
}

std::string FilesManipulator::getFileName(GameLogic::Difficulty dif)
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
	case GameLogic::Difficulty::easy:
		fileName += "Easy";
		break;

	case GameLogic::Difficulty::medium:
		fileName += "Medium";
		break;

	case GameLogic::Difficulty::hard:
		fileName += "Hard";
		break;

	default:
		throw std::string("call of FilesManipulator::getFileNameWithWords with problems");
	}

	fileName += ".txt";

	return fileName;
}

void FilesManipulator::getHighscores(std::vector<std::string>& names, 
	std::vector<std::pair<int, int>>& scores, 
	GameLogic::Difficulty dif)
{
	std::ifstream in("highscores" + getFileName(dif));

	std::string tempName;
	int score, letters;

	while (in >> tempName >> score >> letters)
	{
		names.push_back(tempName);
		scores.push_back(std::pair<int, int>(score, letters));
	}
}

void FilesManipulator::writeHighscores(std::vector<std::string>& names, std::vector<std::pair<int, int>>& scores)
{
	std::ofstream out("highscores" + getFileName());

	for (size_t i = 0; i < names.size(); ++i)
	{
		out << names[i] << ' ' << scores[i].first << ' ' << scores[i].first << '\n';
	}
}