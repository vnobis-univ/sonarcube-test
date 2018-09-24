#include "HighScoreView.h"
#include "StartView.h"

HighScoreView::HighScoreView()
{
}

HighScoreView::HighScoreView(Language _language) : language(_language)
{
}

void HighScoreView::printLogo()
{
	string gameLine;
	if (language == Language::ENGLISH)
	{
		gameLine = "SEA BATTLE";
	}
	else
	{
		gameLine = "�������� ��";
	}
	printAtCenter(0, gameLine, redTextYellowBG);
}

void HighScoreView::draw()
{
	if (language == Language::ENGLISH)
	{
		printAtCenter(9, " Player        Score ", redTextWhiteBG);
		printAtCenter(25, "Press ESCAPE to return to menu", redTextWhiteBG);
	}
	else
	{
		printAtCenter(9, " �������        ������� ", redTextWhiteBG);
		printAtCenter(25, "��������� ESCAPE, ��� ����������� � ����", redTextWhiteBG);
	}
	for (size_t i = 0; i < 5; i++)
	{
		moveCursorTo(16, 13 + i);
		redTextWhiteBG << playersList[i].getName();
		moveCursorTo(31, 13 + i);
		redTextWhiteBG << to_string(playersList[i].getScore());
	}
}

View * HighScoreView::handle()
{
	View * nextView = this;
	switch (_getwch())
	{
	case KEY_ESCAPE:
	{
		nextView = new StartView(language);
	}
	break;
	}
	return nextView;
}
