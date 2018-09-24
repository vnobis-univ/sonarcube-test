#pragma once
#include <vector>
#include "HighScore.h"
#include "Levels.h"

using std::vector;


class ScoresHandler
{
private:
public:

	vector<Row>  getScoresByDif(LevelState level);

};




