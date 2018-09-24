#include "LanguageSelection.h"

#include "MenuView.h"

void LanguageSelection::printLangOption()
{
	system("cls");
	// border control

	if (selected == 2)
	{
		selected = 1;
	}
	if (selected == -1)
	{
		selected = 1;
	}


	if (View::lang == Language::ENG)
	{
		blueOnBlack.printOnCenter(6, " & Changing Of The Language & ");
		for (int i = 0; i < 2; ++i)
		{
			selected != i ? lightBlueOnBlack.printOnCenter(3 * i + 10, english[i]) : lightAquaOnBlack.printOnCenter(3 * i + 10, "~ " + english[i] + " ~");
		}
		blueOnBlack.printOnCenter(20, " * PRESS ESC To Return To MENU * ");
	}
	else
	{
		blueOnBlack.printOnCenter(6, " * Çì³íà Ìîâè * ");
		for (int i = 0; i < 2; ++i)
		{
			selected != i ? lightBlueOnBlack.printOnCenter(3 * i + 10, ukrainian[i]) : lightAquaOnBlack.printOnCenter(3 * i + 10, "~ " + ukrainian[i] + " ~");
		}
		blueOnBlack.printOnCenter(20, " * ÍÀÒÈÑÍ²ÒÜ ESC ÄËß ÏÎÂÅÐÍÅÍÍß Â ÌÅÍÞ * ");
	}
}

LanguageSelection::LanguageSelection(Language m_lang) :
	View(m_lang),
	selected(0)
{};

void LanguageSelection::draw()
{
	printLangOption();
}

View * LanguageSelection::handle()
{
	View* nextView = this;
	bool userChoose = false;

	while (!userChoose)
	{
		switch (_getwch())
		{
		case 72:  // move up
			selected--;
			printLangOption();
			break;
		case 80:   // move down
			selected++;
			printLangOption();
			break;
		case 13:  // to chose the language  ( by click on ENTER)
			userChoose = true;
			if (selected == 0)
			{
				nextView = new LanguageSelection();
			}
			else
			{
				nextView = new LanguageSelection(Language::UKR);
			}
			break;
		case 27:   // ESC to return to menu
			userChoose = true;
			nextView = new MenuView(lang);
		}
	}
	return nextView;
}

