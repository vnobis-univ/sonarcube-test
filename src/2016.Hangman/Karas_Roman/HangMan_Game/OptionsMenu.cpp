#include "OptionsMenu.h"


OptionsMenu::OptionsMenu() :IsSelected(0), level(0){}

int OptionsMenu::GetSelected()
{
	return IsSelected;
}
int OptionsMenu::GetLevel()
{
	return level;
}

void OptionsMenu::drawUKR()
{
	switch (IsSelected)
	{
	case 0:
	{
			  SetColor(3, 1);
			  printInTheCentre("    опнярхи   ", 8);
			  SetColor(3, 0);
			  printInTheCentre("   яепедмIи   ", 10);
			  SetColor(3, 0);
			  printInTheCentre("    бюфйхи    ", 12);
			  SetColor(3, 0);
			  printInTheCentre("  онбепмсрхяъ ", 14);
			  SetColor(3, 4);
	}         break;

	case 1:
	{
			  SetColor(3, 0);
			  printInTheCentre("    опнярхи   ", 8);
			  SetColor(3, 1);
			  printInTheCentre("   яепедмIи   ", 10);
			  SetColor(3, 0);
			  printInTheCentre("    бюфйхи    ", 12);
			  SetColor(3, 0);
			  printInTheCentre("  онбепмсрхяъ ", 14);
			  SetColor(3, 4);
			  break;
	}
	case 2:
	{
			  SetColor(3, 0);
			  printInTheCentre("    опнярхи   ", 8);
			  SetColor(3, 0);
			  printInTheCentre("   яепедмIи   ", 10);
			  SetColor(3, 1);
			  printInTheCentre("    бюфйхи    ", 12);
			  SetColor(3, 0);
			  printInTheCentre("  онбепмсрхяъ ", 14);
			  SetColor(3, 4);
			  break;
	}
	case 3:
	{
			  SetColor(3, 0);
			  printInTheCentre("    опнярхи   ", 8);
			  SetColor(3, 0);
			  printInTheCentre("   яепедмIи   ", 10);
			  SetColor(3, 0);
			  printInTheCentre("    бюфйхи    ", 12);
			  SetColor(3, 1);
			  printInTheCentre("  онбепмсрхяъ ", 14);
			  SetColor(3, 4);
			  break;
	}
	}
}


void OptionsMenu::drawENG()
{
	switch (IsSelected)
	{
	case 0:
	{
				SetColor(3, 1);
				printInTheCentre("     EASY     ", 8);
				SetColor(3, 0);
				printInTheCentre("    MEDIUM    ", 10);
				SetColor(3, 0);
				printInTheCentre("     HARD     ", 12);
				SetColor(3, 0);
				printInTheCentre("     BACK     ", 14);
				SetColor(3, 4);
	}         break;

	case 1:
	{
				SetColor(3, 0);
				printInTheCentre("     EASY     ", 8);
				SetColor(3, 1);
				printInTheCentre("    MEDIUM    ", 10);
				SetColor(3, 0);
				printInTheCentre("     HARD     ", 12);
				SetColor(3, 0);
				printInTheCentre("     BACK     ", 14);
				SetColor(3, 4);
				break;
	}
	case 2:
	{
				SetColor(3, 0);
				printInTheCentre("     EASY     ", 8);
				SetColor(3, 0);
				printInTheCentre("    MEDIUM    ", 10);
				SetColor(3, 1);
				printInTheCentre("     HARD     ", 12);
				SetColor(3, 0);
				printInTheCentre("     BACK     ", 14);
				SetColor(3, 4);
				break;
	}
	case 3:
	{
				SetColor(3, 0);
				printInTheCentre("     EASY     ", 8);
				SetColor(3, 0);
				printInTheCentre("    MEDIUM    ", 10);
				SetColor(3, 0);
				printInTheCentre("     HARD     ", 12);
				SetColor(3, 1);
				printInTheCentre("     BACK     ", 14);
				SetColor(3, 4);
				break;
	}
	}
}

void OptionsMenu::draw(bool ukr)
{
	clean();
	if (ukr)
	{
		drawUKR();
	}
	else
	{
		drawENG();
	}
	char input = ' ';
	while (input != 13)
	{
		if (input == 13) break;
		input = _getch();
		switch (input)
		{
		case 72: IsSelected -= 1; break;
		case 80: IsSelected += 1; break;
		}
		IsSelected = IsSelected % 4;
		if (IsSelected < 0) IsSelected += 4;
		clean();
		if (ukr)
		{
			drawUKR();
		}
		else
		{
			drawENG();
		}

	}
	if (IsSelected == 0)
	{
		level = 0;
	}
	else if (IsSelected == 1)
	{
		level = 1;
	}
	else if (IsSelected == 2)
	{
		level = 2;
	}
	
}