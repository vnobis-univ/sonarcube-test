#include "artificialIntelligence.h"

artificialIntelligence::artificialIntelligence(FieldView* p_field) :
	fld(p_field), doneMoves(0)
{
	diagonalCell[0] = Cell(1, 1);
	diagonalCell[1] = Cell(0, 0);
	diagonalCell[2] = Cell(2, 2);
	diagonalCell[3] = Cell(2, 0);
	diagonalCell[4] = Cell(0, 2);
}

void artificialIntelligence::makeMoveInCell(Cell cell)
{
	cell.drawO(redPen);
	fld->field[cell.x][cell.y].state = Cell::State::filledO;
}

int artificialIntelligence::countCrossInCol(int col)
{
	int result = 0;
	for (int i = 0; i < 3; ++i)
		if (fld->field[col][i].state == Cell::State::filledX)
			++result;

	return result;
}

int artificialIntelligence::countCrossInRow(int row)
{
	int result = 0;
	for (int i = 0; i < 3; ++i)
		if (fld->field[i][row].state == Cell::State::filledX)
			++result;

	return result;
}

int artificialIntelligence::countCrossInDiag(int i)
{
	int result = 0;
	if (i == 0)
	{
		for (int j = 0; j < 3; ++j)
			if (fld->field[j][j].state == Cell::State::filledX)
				++result;
	}
	else
	{
		if (fld->field[0][2].state == Cell::State::filledX) ++result;
		if (fld->field[1][1].state == Cell::State::filledX) ++result;
		if (fld->field[2][0].state == Cell::State::filledX) ++result;
	}
	return result;
}

bool artificialIntelligence::freeCellInCol(int col)
{
	for (int i = 0; i < 3; ++i)
		if (fld->field[col][i].state == Cell::State::empty)
			return true;

	return false;
}

bool artificialIntelligence::freeCellInRow(int row)
{
	for (int i = 0; i < 3; ++i)
		if (fld->field[i][row].state == Cell::State::empty)
			return true;

	return false;
}

bool artificialIntelligence::freeCellInDiag(int diag)
{
	if (diag == 0)
	{
		for (int j = 0; j < 3; ++j)
			if (fld->field[j][j].state == Cell::State::empty)
				return true;
	}
	else
	{
		if (fld->field[0][2].state == Cell::State::empty) return true;
		if (fld->field[1][1].state == Cell::State::empty) return true;
		if (fld->field[2][0].state == Cell::State::empty) return true;
	}
	return false;
}

void artificialIntelligence::makeMoveInCol(int row)
{
	for (int i = 0; i < 3; ++i)
		if (fld->field[row][i].state == Cell::State::empty)
			makeMoveInCell(Cell(row, i));
}

void artificialIntelligence::makeMoveInRow(int row)
{
	for (int i = 0; i < 3; ++i)
		if (fld->field[i][row].state == Cell::State::empty)
			makeMoveInCell(Cell(i, row));
}

void artificialIntelligence::makeMoveInDiag(int diag)
{
	if (diag == 0)
	{
		for (int j = 0; j < 3; ++j)
			if (fld->field[j][j].state == Cell::State::empty)
				makeMoveInCell(Cell(j, j));
	}
	else
	{
		if (fld->field[0][2].state == Cell::State::empty)
			makeMoveInCell(Cell(0, 2));
		else if (fld->field[1][1].state == Cell::State::empty)
			makeMoveInCell(Cell(1, 1));
		else 
			makeMoveInCell(Cell(2, 0));
	}
}

bool artificialIntelligence::preventPlayerWin()
{
	bool prevented = false;

	for (int i = 0; i < 3; ++i)
	{
		if (countCrossInCol(i) == 2 && freeCellInCol(i))
		{
			makeMoveInCol(i);
			prevented = true;
			break;
		}
		if (countCrossInRow(i) == 2 && freeCellInRow(i)) 
		{
			makeMoveInRow(i);
			prevented = true;
			break;
		}
		if (countCrossInDiag(i) == 2 && freeCellInDiag(i) && i != 2)
		{
			makeMoveInDiag(i);
			prevented = true;
			break;
		}
	}
	return prevented;
}

void artificialIntelligence::makeExpertMove()
{
	if(!preventPlayerWin() && doneMoves <4)
	{
		int i = 0;
		Cell move = diagonalCell[i];

		while (fld->field[move.x][move.y].state != Cell::State::empty)
		{
			if (i > 3)
			{
				while (fld->field[move.x][move.y].state != Cell::State::empty)
				++move;
				break;
			}

			if (fld->field[move.x][move.y].state == Cell::State::empty)
				break;
			else
				move = diagonalCell[++i];
		}

		makeMoveInCell(move);
	}
	++doneMoves;
}

void artificialIntelligence::makeNoobMove()
{
	int i = 0;
	Cell move = diagonalCell[i];

	while (fld->field[move.x][move.y].state != Cell::State::empty)
	{
		if (i > 3)
		{
			while (fld->field[move.x][move.y].state != Cell::State::empty)
				++move;
			break;
		}

		if (fld->field[move.x][move.y].state == Cell::State::empty)
			break;
		else
			move = diagonalCell[++i];
	}

	makeMoveInCell(move);
	++doneMoves;
}
