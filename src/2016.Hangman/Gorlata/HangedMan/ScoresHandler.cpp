#include "ScoresHandler.h"
#include "Levels.h"
#include <fstream>
#include <algorithm>


using namespace std;

vector<Row> ScoresHandler::getScoresByDif(LevelState level)
{
	vector<Row> requested(0);

	fstream file;
	switch (level)
	{
	case LevelState::EASY:
		file = fstream("Scores/DataEASY.txt");
		break;

	case LevelState::MEDIUM:
		file = fstream("Scores/DataMED.txt");
		break;

	case LevelState::HARD:
		file = fstream("Scores/DataHARD.txt");
		break;

	}
	Row temp;
	
	while (file >> temp)
	{
		requested.push_back(temp);
	}
	sort(requested.begin(), requested.end());

	return requested;
}
