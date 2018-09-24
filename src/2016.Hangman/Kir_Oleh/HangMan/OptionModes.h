#pragma once


enum class Sex{ Male, Female };
extern Sex currSex;

enum class Language{ Ukrainian, English };
extern Language currLang;


enum class DifficultyModes{ Easy, Medium, Hard };
class Difficulty
{
	DifficultyModes mode;
public:
	Difficulty() :
		mode(DifficultyModes::Easy)
	{
	}

	DifficultyModes getDifficulty()
	{
		return mode;
	}

	void setDifficulty(DifficultyModes m)
	{
		mode = m;
	}


	int getHP()
	{
		switch (mode)
		{
		case DifficultyModes::Easy:
			return 20;
		case DifficultyModes::Medium:
			return 15;
		case DifficultyModes::Hard:
			return 10;
		}
	}

	int getBonusses()
	{
		switch (mode)
		{
		case DifficultyModes::Easy:
			return 4;
		case DifficultyModes::Medium:
			return 2;
		case DifficultyModes::Hard:
			return 1;
		}
	}

	int getFines()
	{
		switch (mode)
		{
		case DifficultyModes::Easy:
			return 2;
		case DifficultyModes::Medium:
			return 2;
		case DifficultyModes::Hard:
			return 1;
		}
	}
};

extern Difficulty currDifficulty;