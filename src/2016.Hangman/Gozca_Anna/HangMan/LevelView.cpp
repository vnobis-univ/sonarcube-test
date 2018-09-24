#include "LevelView.h"

LevelView::LevelView() : numOfSelectedLevel(0)
{
	levels[0] = "EASY";
	levels[1] = "MEDIUM";
	levels[2] = "HARD";
}

void typeName();
void LevelView::draw()
{
	typeName();
	for (size_t i = 0; i < 3; i++)
	{
		if (i == numOfSelectedLevel)
		{
			printAtCenter(10 + 2 * i, "[-" + levels[i] + "-]", blueTextWhiteBG);
		}
		else
		{
			printAtCenter(10 + 2 * i, levels[i], blueTextGrayBG);
		}
	}	
	printAtCenter(24, "[-PRESS ESC TO RETURN TO MENU-]", blueTextGrayBG);
}

View * LevelView::handle()
{
	View* nextView = this;
	switch (_getwch())
	{
	case KEY_UP:
	{
		--numOfSelectedLevel;
		if (numOfSelectedLevel < 0)
		{
			numOfSelectedLevel = 2;
		}
		draw();
	}
	break;
	case KEY_DOWN:
	{
		++numOfSelectedLevel;
		if (numOfSelectedLevel == 3)
		{
			numOfSelectedLevel = 0;
		}
		draw();
	}
	break;
	case KEY_ENTER:
	{
		if (numOfSelectedLevel == 0)
		{
			nextView = new GameView(Levels::EASY);
		}
		else if (numOfSelectedLevel == 1)
		{
			nextView = new GameView(Levels::MEDIUM);
		}
		else
		{
			nextView = new GameView(Levels::HARD);
		}
	}
	break;
	case KEY_ESCAPE:
	{
		nextView = new StartView;
	}
	break;
	default:
	{
		nextView = this;
	}
	}
	return nextView;
}

