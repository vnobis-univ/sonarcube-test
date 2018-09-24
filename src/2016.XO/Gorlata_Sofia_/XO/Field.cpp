#include "Field.h"
#include <iostream>
#include <windows.h>
#include "MenuView.h"
#include "Utils.h"
#include "Result.h"

Field::Field():selected(Cell(1,1)), state(State::playersMove), playerScore(0)
{
	for (int i = 0; i < 3;++i)
		for (int j = 0; j < 3;++j)
			field[i][j] = Cell(i, j);
}
void Field::draw()
{
	system("color 90");
	system("cls");

	moveCursorTo(31, 1);
	purOnBlue.print("Score: ");
	moveCursorTo(40, 1);
	purOnBlue.print(playerScore);
	
	
	for (int i = 0; i < 3;++i)
		for (int j = 0; j < 3;++j)
			field[i][j].draw();

	selected.draw(true);
}

void Field::makeMove()
{
	state = State::compMove;

	Cell move(1, 1);

	while (field[move.x][move.y].state != Cell::State::empty)
		move = Cell(rand() % 3, rand() % 3);

	field[move.x][move.y].state = Cell::State::zero;
	Sleep(200);
	field[move.x][move.y].draw();
}

bool Field::checkGameOver(bool & state)
{
	bool win = false;

	/*for (int i = 0; i < 3; ++i)
	{
		if ((field[i][0] == field[i][1] && field[i][0] == field[i][2]) ||
			(field[1][i] == field[1][i] && field[1][i] == field[2][i]) ||
			(field[0][0] == field[1][1] && field[1][1] == field[2][2]) ||
			(field[2][0] == field[1][1] && field[1][1] == field[0][2]))
		{
			win = true;
		}
	}*/


	if ((field[0][0] == field[0][1] && field[0][1] == field[0][2]) ||
		(field[1][0] == field[1][1] && field[1][1] == field[1][2]) ||
		(field[2][0] == field[2][1] && field[2][1] == field[2][2]) ||

		(field[0][0] == field[1][0] && field[1][0] == field[2][0]) ||
		(field[0][1] == field[1][1] && field[1][1] == field[2][1]) ||
		(field[0][2] == field[1][2] && field[1][2] == field[2][2]) ||

		(field[0][0] == field[1][1] && field[1][1] == field[2][2]) ||
		(field[2][0] == field[1][1] && field[1][1] == field[0][2]))
	{
		win = true;
	}
		
	state = win;

	if (win && this->state == State::playersMove)
	{
		playerScore++;
		clearField();
	}
	else if(win && this->state == State::compMove){
		whiteOnBlue.printOnCenter(20, "You lose!  ");
		Sleep(1500);
	}



	//check for tie
	int count = 0;
	if (!(win))
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (!(field[i][j].state == Cell::State::empty))
				{
					++count;
				}
			}
		}
	}
	//if tie
	if (count == 9)
	{
		clearField();
		draw();
	}

	return win;
}

void Field::clearField()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			field[i][j].state = Cell::State::empty;
		}
	}
	//draw();
}


View * Field::handle()
{
	View* nextView = this;

	bool gameOver = false;
	while (!gameOver)
	{
		switch (_getwch())
		{
		case 72:
			field[selected.x][selected.y].draw();
			--selected.y;

			if (selected.y < 0) { selected.y = 2; }
			field[selected.x][selected.y].draw(true);
			break;
		case 75:
			field[selected.x][selected.y].draw();
			--selected.x;

			if (selected.x < 0) { selected.x = 2; }
			field[selected.x][selected.y].draw(true);
			break;
		case 77:
			field[selected.x][selected.y].draw();
			++selected.x;

			if (selected.x > 2) { selected.x = 0; }
			field[selected.x][selected.y].draw(true);
			break;
		case 80:
			field[selected.x][selected.y].draw();
			++selected.y;

			if (selected.y >2) { selected.y = 0; }
			field[selected.x][selected.y].draw(true);
			break;
		case 13:
			if (field[selected.x][selected.y].state == Cell::State::empty)
			{
				state = State::playersMove;
				field[selected.x][selected.y].state = Cell::State::cross;
				field[selected.x][selected.y].draw();
				if (!checkGameOver(gameOver))
				{
					makeMove();
					field[selected.x][selected.y].draw(true);
					checkGameOver(gameOver);
				}
			}
		}
	}
	if (state == State::compMove) { nextView = new Result(playerScore); }

	return nextView;
};