#pragma once
#include "Cell.h"
#include "View.h"
#include "DifficultyView.h"

class artificialIntelligence;

class FieldView : public View
{
	enum class GameState {playerMove, machineMove};

	Cell field[3][3];
	Cell selected; 
	GameState gameState;
	
	difficulty lvl;

	int playerScore;
	int movesCount; 
	
	void changeGameState();
	bool checkForGameOver(bool& );
	void hightlightWinCombination(Cell, Cell, Cell, bool&);
	void clearField();
public:
	FieldView(difficulty);

	virtual void draw();
	virtual View* handle();
	
	friend artificialIntelligence;
};

