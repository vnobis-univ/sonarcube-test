#include "GameLogic.h"
#include "GameField.h"

GameLogic::GameLogic(COORD coord):
	oponentField(coord, GameField::FieldType::oponentField)
{
	oponentField.drawField();
}

void GameLogic::handleMove(int index_i, int index_j, bool isNewSelectedCell)
{
	oponentField.drawCurrentCell(index_i, index_j, isNewSelectedCell);
}

int GameLogic::getScore()
{
	return -1;
}

bool GameLogic::connectToGame()
{
	return true;
}