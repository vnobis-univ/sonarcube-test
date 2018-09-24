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
	GamerUser gamer1;
	GamerComputer gamer2;
	bool toExit = false; //is used to allow redrawing only two out of 9 tiles, but not a whole field; that fixes problems with lagging console
	bool toMakeStep = false;
	View* view = this;
	while (!toExit)
	{
		Button but = getButton(FieldView::possibleButtons, FieldView::size);
		int hor = selectedCell.x; //hor - horizonatl
		int vert = selectedCell.y; //ver - vertical
		switch (but)
		{
		case Button::UP:
			vert--;
			break;
		case Button::DOWN:
			vert++;
			break;
		case Button::LEFT:
			hor--;
			break;
		case Button::RIGHT:
			hor++;
			break;
		case Button::ENTER:
		{
							  if (!arr[selectedCell.x][selectedCell.y].isChosen())
							  {
								  gamer1.add(selectedCell);
								  arr[selectedCell.x][selectedCell.y].setChosenX(true);
								  ++counter; 
								  toMakeStep = true;
							  }
							  if (gamer1.isWinner() ||
								  (!gamer1.isWinner() && !gamer2.isWinner() && counter == 9))
							  {
								  draw();
								  hor = 0;
								  vert = 0;
								  score += gamer1.isWinner() ? 1 : 0;
								  printAtMiddle(gamer1.isWinner() ? "YOU WON!!!" : "THIS IS TIE", 0, pPurpleBlack);
								  printAtMiddle("Press enter to continue", 1, pPurpleBlack);
								  wait();
								  setPures();
								  counter = 0;
								  toExit = true;
								  break;
							  }
							  if (toMakeStep)
							  {
								  toMakeStep = false;
								  Cell compCell = gamer2.computersChoice(&arr[0][0]);
								  arr[compCell.x][compCell.y].setChosenO(true);
								  arr[compCell.x][compCell.y].draw(compCell.x, compCell.y);
								  ++counter;
								  if (gamer2.isWinner())
								  {
									  clear();
									  draw();
									  printAtMiddle("YOU LOST!!!", 0, pPurpleBlack);
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
		if (hor >= 0 && hor < 3)
		{
			arr[selectedCell.x][selectedCell.y].draw(selectedCell.x, selectedCell.y);
			selectedCell.x = hor;
			arr[selectedCell.x][selectedCell.y].draw(selectedCell.x, selectedCell.y, true);
		}
		if (vert >= 0 && vert < 3)
		{
			arr[selectedCell.x][selectedCell.y].draw(selectedCell.x, selectedCell.y);
			selectedCell.y = vert;
			arr[selectedCell.x][selectedCell.y].draw(selectedCell.x, selectedCell.y, true);
		}
	}
	clear();
	return view;
}

View* FieldView::enoughScores()
{
	View * view = new StartView();
	printAtMiddle("PRESS ENTER TO CONINUE", 1, pPurpleBlack);
	wait();
	view = new ResultView(score, saver.isHighEnough(score) ? true : false);
	counter = 0;
	score = 0;
	return view;
}

void FieldView::draw()
{
	SelectObject(dc, penOrange);
	SelectObject(dc, brushGray);

	Rectangle(dc, 100, 50, 700, 420);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			arr[i][j].draw(i, j);
		}
	}
	arr[selectedCell.x][selectedCell.y].draw(selectedCell.x, selectedCell.y, true);
	printAtMiddle("Score: " + to_string(score), 3, Printer(Color::lWhite, Color::lBlack));
}

void FieldView::setPures()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			arr[i][j].setPure();
		}
	}
}

FieldView::~FieldView()
{
	delete[] possibleButtons;
}