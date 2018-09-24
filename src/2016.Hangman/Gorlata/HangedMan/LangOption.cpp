#include "LangOption.h"
#include "MenuView.h"

void LangOption::printLangOption()
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
		lightPurpleOnBlack.printOnCenter(6, " * PLEASE, SELECT LANGUAGE * ");
		for (int i = 0; i < 2; ++i)
		{
			selected != i ? greenOnBlack.printOnCenter(3 * i + 10, english[i]) : lightAquaOnBlack.printOnCenter(3 * i + 10, "~ " + english[i] + " ~");
		}
		lightPurpleOnBlack.printOnCenter(20, " * PRESS ESC To Return To MENU * ");
	}
	else
	{
		lightPurpleOnBlack.printOnCenter(6, " * ÁÓÄÜ ËÀÑÊÀ, ÎÁÅÐ²ÒÜ ÌÎÂÓ * ");
		for (int i = 0; i < 2; ++i)
		{
			selected != i ? greenOnBlack.printOnCenter(3 * i + 10, ukrainian[i]) : lightAquaOnBlack.printOnCenter(3 * i + 10, "~ " + ukrainian[i] + " ~");
		}
		lightPurpleOnBlack.printOnCenter(20, " * ÍÀÒÈÑÍ²ÒÜ ESC ÄËß ÏÎÂÅÐÍÅÍÍß Â ÌÅÍÞ * ");
	}
}

LangOption::LangOption(Language m_lang) :
	View(m_lang),
	selected(0)
	{};

void LangOption::draw()
{
	printLangOption();
}

View * LangOption::handle()
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
		case 13:  // to chose the language 
			userChoose = true;
			if (selected == 0)
			{
				nextView = new LangOption();
			}
			else
			{
				nextView = new LangOption(Language::UKR);
			}
			break;
		case 27:   // ESC to return to menu
			userChoose = true;
			nextView = new MenuView(lang);
		}
	}
	return nextView;
}
