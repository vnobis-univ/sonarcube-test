#include "FieldView.h"
#include "ResultView.h"
#include "StartView.h"
#include "Printer.h"
#include "artificialIntelligence.h"
#include "Utils.h"
#include <iostream>

using namespace std;

FieldView::FieldView(difficulty _lvl) :
	selected(1, 1), gameState(GameState::playerMove), 
	lvl(_lvl), playerScore(0), movesCount(0)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3;++j)
			field[i][j] = Cell(i, j);
}

void FieldView::changeGameState()
{
	gameState == GameState::playerMove ? gameState = (GameState)1 : gameState = (GameState)0;
}
bool FieldView::checkForGameOver(bool& game)
{
	bool gameEnded = false;

	for (int i = 0; i < 3; ++i)
	{
		if (field[0][i] == field[1][i] && field[0][i] == field[2][i])
			hightlightWinCombination(field[0][i], field[1][i], field[2][i], gameEnded);
		if (field[i][0] == field[i][2] && field[i][0] == field[i][1])
			hightlightWinCombination(field[i][0], field[i][2], field[i][1], gameEnded);
	}

	if (field[0][0] == field[1][1] && field[0][0] == field[2][2])
		hightlightWinCombination(field[0][0], field[1][1], field[2][2], gameEnded);
	if (field[0][2] == field[1][1] && field[0][2] == field[2][0])
		hightlightWinCombination(field[0][2], field[1][1], field[2][0], gameEnded);
	
	if (movesCount == 5 && !gameEnded)
	{
		gameEnded = true;
		lightRed.MidLinePrint(23, "  It's a tie!");
		systemPauseInLine(44, 25);
	}

	gameEnded ? game = gameEnded : changeGameState();
	return gameEnded;
}

void FieldView::hightlightWinCombination(Cell c1, Cell c2, Cell c3, bool& win)
{
	selected.drawCell(bluePen);
	c1.drawCell(whitePen);
	c2.drawCell(whitePen);
	c3.drawCell(whitePen);
	win = true;
	
	gameState == GameState::playerMove ? lightRed.MidLinePrint(23, " You rock!")
		: lightRed.MidLinePrint(23, " Machine rocks!");

	if(gameState == GameState::playerMove) ++playerScore;

	systemPauseInLine(44, 25);
}

void FieldView::draw()
{
	clean();
	system("COLOR 0A");

	lvl == difficulty::normal ? lightRed.MidLinePrint(1, "It's gonna be easy...") :
	lightRed.MidLinePrint(1, "Try to beat my perfect artificial intelligence!");

	for (int i = 0; i < 3;++i)
		for (int j = 0; j < 3; ++j)
			field[i][j].drawCell( bluePen);
	
	selected.drawCell(redPen);

	lightRed.MidLinePrint(22, " Score: ", playerScore);
	white.MidLinePrint(28, " Press ESC to return to main menu");
}

void FieldView::clearField()
{
	for (int i = 0; i < 3;++i)
		for (int j = 0; j < 3; ++j)
			field[i][j].state = Cell::State::empty;
	movesCount = 0;
}

View* FieldView::handle()
{
	View* nextView = this;
	artificialIntelligence machine(this);
	
	bool gameOver = false;

	while (!gameOver)
	{
		switch (_getwch())
		{
		case 13: 
			if (field[selected.x][selected.y].state == Cell::State::empty)
			{
				(field[selected.x][selected.y]).drawX(redPen);
				movesCount++;
				if (!checkForGameOver(gameOver))
				{
					lvl == difficulty::normal ? machine.makeNoobMove(): machine.makeExpertMove();
					checkForGameOver(gameOver);
				}
			}
			break;
		case 72:
			selected.drawCell(bluePen);
			--selected.y;
			selected.drawCell(redPen);
			break;
		case 75:
			selected.drawCell(bluePen);
			--selected.x;
			selected.drawCell(redPen);
			break;
		case 77:
			selected.drawCell(bluePen);
			++selected.x;
			selected.drawCell(redPen);
			break;
		case 80:
			selected.drawCell(bluePen);
			++selected.y;
			selected.drawCell(redPen);
			break;
		case 27:
			nextView = new StartView;
			gameOver = true;
			break;
		}
	}

	if (gameState == GameState::playerMove)
		clearField();
	else
		nextView = new ResultView(playerScore);
	
	return nextView;
}
