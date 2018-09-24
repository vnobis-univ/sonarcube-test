#include "StartView.h"
#include "LanguageView.h"
#include "GameView.h"
#include "HighScoreView.h"

StartView::StartView() :selected(0), language(Language::ENGLISH)
{
	options[0] = "START";
	options[1] = "HIGHSCORES"; 
	options[2] = "LANGUAGE";
	options[3] = "EXIT";
}

StartView::StartView(Language lang) : selected(0), language(lang)
{
	if (language == Language::ENGLISH)
	{
		options[0] = "START";
		options[1] = "HIGHSCORES";
		options[2] = "LANGUAGE";
		options[3] = "EXIT";
	}
	else
	{
		options[0] = "Грати";
		options[1] = "Рекорди";
		options[2] = "Мова";
		options[3] = "Вихід";
	}
}

void StartView::printLogo()
{
	string gameLine;
	if (language == Language::ENGLISH)
	{
		gameLine = "SEA BATTLE";
	}
	else
	{
		gameLine = "Морський бій";
	}
	printAtCenter(0, gameLine, redTextYellowBG);
}

void StartView::draw()
{
	for (size_t i = 0; i < 4; i++)
	{
		if (i == selected)
		{
			printAtCenter(10 + 2 * i, "[-" + options[i] + "-]", redTextWhiteBG);
		}
		else
		{
			printAtCenter(10 + 2 * i, options[i], redTextYellowBG);
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
		--selected;
		if (selected < 0)
		{
			selected = 3;
		}
	}
	break;
	case KEY_DOWN:
	{
		++selected;
		if (selected > 3)
		{
			selected = 0;
		}
	}
	break;
	case KEY_ENTER:
	{
		switch (selected)
		{
		case 0:
		{
			nextView = new GameView(language);
		}
		break;
		case 1:
		{
			readPlayersList(language);
			nextView = new HighScoreView(language);
		}
		break;
		case 2:
		{
			nextView = new LanguageView(language);
		}
		
		break;
		case 3:
		{
			exit(0);
		}		
		break;
	}
	break;
	default:
	{
		return this;
	}
	}
	}
	return nextView;
}