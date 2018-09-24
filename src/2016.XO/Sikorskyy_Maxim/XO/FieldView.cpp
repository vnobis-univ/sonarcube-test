#include "Classes.h"

FieldView::FieldView()
{
	score = 0;
	counter = 0;
	
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			arr[i][j] = Field(0, 0);
		}
	}
}

View* FieldView::handleInput()
{
	
	User Player1;
	Computer Player2;
	bool toExit = false; 
	bool toMakeStep = false;
	View* view = this;
	while (!toExit)
	{
		Button buttonReader = getButton(FieldView::possibleButtons, FieldView::size);
		int row = selectedCell.x; 
		int col = selectedCell.y; 
		switch (buttonReader)
		{
		case Button::UP:
			col--;
			break;
		case Button::DOWN:
			col++;
			break;
		case Button::LEFT:
			row--;
			break;
		case Button::RIGHT:
			row++;
			break;
		case Button::ENTER:
		{
							  if (!arr[selectedCell.x][selectedCell.y].isChosen())
							  {
								  Player1.add(selectedCell);
								  arr[selectedCell.x][selectedCell.y].setChosenX(true);
								  ++counter; 
								  toMakeStep = true;
							  }
							  if (Player1.isWinner() ||
								  (!Player1.isWinner() && !Player2.isWinner() && counter == 9))
							  {
								  draw();
								  row = 0;
								  col = 0;
								  score += Player1.isWinner() ? 1 : 0;
								  printAtMiddle(Player1.isWinner() ? "YOU WON!!!" : "THIS IS TIE", 0, Printer(Color::dBlack, Color::dRed));
								  printAtMiddle("Press enter to continue", 1, Printer(Color::dBlack, Color::dRed));
								  wait();
								  clearAll();
								  counter = 0;
								  toExit = true;
								  break;
							  }
							  if (toMakeStep)
							  {
								  toMakeStep = false;
								  Cell compCell = Player2.cpuChoice(&arr[0][0]);
								  arr[compCell.x][compCell.y].setChosenO(true);
								  arr[compCell.x][compCell.y].draw(compCell.x, compCell.y);
								  ++counter;
								  if (Player2.isWinner())
								  {
									  clear();
									  draw();
									  printAtMiddle("GAME OVER", 0, Printer(Color::dBlack, Color::dRed));
									  view = enoughScores();
									  toExit = true;
									  break;
								  }
							  }
		}
			break;
		case Button::ESC:
			view = new StartView();
			toExit = true;
			break;
		}
		if (row >= 0 && row < 3)
		{
			arr[selectedCell.x][selectedCell.y].draw(selectedCell.x, selectedCell.y);
			selectedCell.x = row;
			arr[selectedCell.x][selectedCell.y].draw(selectedCell.x, selectedCell.y, true);
		}
		if (col >= 0 && col < 3)
		{
			arr[selectedCell.x][selectedCell.y].draw(selectedCell.x, selectedCell.y);
			selectedCell.y = col;
			arr[selectedCell.x][selectedCell.y].draw(selectedCell.x, selectedCell.y, true);
		}
	}
	clear();
	return view;
}

View* FieldView::enoughScores()
{
	View * view = new StartView();
	printAtMiddle("PRESS ENTER TO CONINUE", 1, Printer(Color::dBlack, Color::dRed));
	wait();
	view = new ResultView(score, buff.isHigh(score) ? true : false);
	counter = 0;
	score = 0;
	return view;
}

void FieldView::draw()
{
	printRect(0, 0, 60, 21, Printer(Color::lBlack, Color::dYellow));
	printRect(0, 0, 60, 2, Printer(Color::lBlack, Color::dRed));
	printAtMiddle("Tic-tac-toe", 1, Printer(Color::dBlack, Color::dRed));

	SelectObject(dc, penOrange);
	SelectObject(dc, brushGray);

	
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			arr[i][j].draw(i, j);
		}
	}
	arr[selectedCell.x][selectedCell.y].draw(selectedCell.x, selectedCell.y, true);
	printAtMiddle("SCORE: " + to_string(score), 3, Printer(Color::dBlack, Color::dYellow));
}

void FieldView::clearAll()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			arr[i][j].clear();
		}
	}
}

FieldView::~FieldView()
{
	delete[] possibleButtons;
}