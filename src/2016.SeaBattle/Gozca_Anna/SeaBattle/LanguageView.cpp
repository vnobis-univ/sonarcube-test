#include "LanguageView.h"
#include "StartView.h"

LanguageView::LanguageView()  {}

LanguageView::LanguageView(Language lang): selected(0), language(lang)
{
	if (language == Language::ENGLISH)
	{
		options[0] = "ENGLISH";
		options[1] = "UKRAINIAN";
		options[2] = "RETURN TO MENU";
	}
	else
	{
		options[0] = "Англійська";
		options[1] = "Українська";
		options[2] = "Повернутися в меню";
	}
}

void LanguageView::printLogo()
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

void LanguageView::draw()
{
	if (language == Language::ENGLISH)
	{
		printAtCenter(8, "CHOOSE LANGUAGE, PLEASE", redTextYellowBG);
	}
	else
	{
		printAtCenter(8, "Виберіть мову, будь ласка", redTextYellowBG);
	}
	for (size_t i = 0; i < 3; i++)
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

View * LanguageView::handle()
{
	View * nextView = this;
	switch (_getwch())
	{
	case KEY_UP:
	{
		--selected;
		if (selected < 0)
		{
			selected = 2;
		}
	}
	break;
	case KEY_DOWN:
	{
		++selected;
		if (selected > 2)
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
			language = Language::ENGLISH;
			nextView = new LanguageView(Language::ENGLISH);
		}
		break;
		case 1:
		{
			language = Language::UKRAINIAN;
			setlocale(LC_ALL, "Ukrainian");
			SetConsoleCP(1251);
			SetConsoleOutputCP(1251);
			nextView = new LanguageView(Language::UKRAINIAN);
		}
		break;
		case 2:
		{
			nextView = new StartView(language);
		}
		break;
		}
	}
	}
	return nextView;
}