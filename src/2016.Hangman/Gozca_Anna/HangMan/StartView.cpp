#include "StartView.h"
#include "LevelView.h"
#include "HighScoreView.h"

StartView::StartView(): selected(0)
{
	option[0] = "START";
	option[1] = "HIGHSCORES";
	option[2] = "EXIT";
}

void typeName();
void StartView::draw()
{
	typeName();
	for (size_t i = 0; i < 3; i++)
	{
		if (i == selected)
		{
			printAtCenter(10 + 2 * i, "[-" + option[i] + "-]", blueTextWhiteBG);
		}
		else
		{
			printAtCenter(10 + 2 * i, option[i], blueTextGrayBG );
			cout << endl;
		}
	}
}

View * StartView::handle()
{
	View * nextView = this;
	switch (_getwch())
	{
	case KEY_UP:
	{
		selected--;
		if (selected < 0)
		{
			selected = 2;
		}
		draw();
	}
	break;
	case KEY_DOWN:
	{
		selected++;
		if (selected > 2)
		{
			selected = 0;
		}
		draw();
	}
	break;
	case KEY_ENTER:
	{
		switch (selected)
		{
		case 0:
		{
			nextView = new LevelView;
		}
		break;
		case 1:
		{
			readPlayersList();
			nextView = new HighScoreView;
		}
		break;
		case 2:
		{
			exit(0); 
		}
		break;
		}
	}
	break;
	default:
	{
		return this;
	}
	}
	return nextView;
}
