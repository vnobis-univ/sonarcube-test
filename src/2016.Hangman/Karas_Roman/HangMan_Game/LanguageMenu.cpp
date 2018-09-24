#include "LanguageMenu.h"

#include "MainMenu.h"

LanguageMenu::LanguageMenu() :
IsSelected(0)
{
}

void LanguageMenu::drawMenu()
{
	switch (IsSelected)
	{
	case 0:
	{
				SetColor(3, 1);
				printInTheCentre("     ENGLISH     ", 12);
				SetColor(3, 0);
				printInTheCentre("    ” –¿ØÕ—‹ ¿   ", 14);
				SetColor(3, 4);
	}         break;

	case 1:
	{
				SetColor(3, 0);
				printInTheCentre("     ENGLISH     ", 12);
				SetColor(3, 1);
				printInTheCentre("    ” –¿ØÕ—‹ ¿   ", 14);
				SetColor(3, 4);
				break;
	}
	}

}
void LanguageMenu::draw()
{
	clean();
	drawMenu();
	char input = ' ';
	while (input != 13) //Enter Key
	{
		if (input == 13) break;
		input = _getch();
		switch (input)
		{
		case 72: IsSelected -= 1; break;
		case 80: IsSelected += 1; break;
		}
		IsSelected = IsSelected % 2;
		if (IsSelected < 0) IsSelected += 1;
		clean();
		drawMenu();

	}
	if (IsSelected == 0)
	{
		MainMenu menu;
		menu.draw(false);

	}
	else if (IsSelected == 1)
	{
		MainMenu menu;
		menu.draw(true);
	}
}