#include "StartView.h"
#include "FieldView.h"

StartView::StartView(): language(Lokalization::En), complexity(Complexity::Easy), position(0){}
StartView::StartView(Lokalization opt, Complexity comp): language(opt), complexity(comp), position(0){}
Printer menu(ConsoleColor::Black, ConsoleColor::LightGreen);
Printer menuSelected(ConsoleColor::Black, ConsoleColor::White);

void StartView::draw()
{
	system("cls");
	View::draw();
	printMenu();
	drawCopyright();
}

void StartView::printMenu()
{
	for (int i = 0; i < 4; ++i)
	{
		int place = 3 * i + 5;
		if (language == Lokalization::En)
		{
			i == position ? printTextOnTheCenter(place, optionEn[i], menuSelected) : printTextOnTheCenter(place, optionEn[i], menu);
		}
		else
		{
			i == position ? printTextOnTheCenter(place, optionUa[i], menuSelected) : printTextOnTheCenter(place, optionUa[i], menu);
		}
	}
}

void StartView::drawCopyright()
{
	if (language == Lokalization::En)
	{
		printTextOnTheCenter(consoleHeight - 2, "All rights reserved", menu);
	}
	else
	{
		printTextOnTheCenter(consoleHeight - 2, "Всі права захищені", menu);
	}
}

View * StartView::handle()
{
	View* nextView = this;
	bool choose = false;
	while (!choose)
	{
		switch (_getch())
		{
		case 80://Down
			++position;
			if (position > 3)
			{
				position = 3;
			}
			printMenu();
			break;
		case 72://Up
			--position;
			if (position < 0)
			{
				position = 0;
			}
			printMenu();
			break;
		case 13://Enter
			if (position == 0)
			{
				nextView = new FieldView(language, complexity);
				choose = true;
				break;
			}
			else if (position == 1)
			{
				nextView = new HighscoresView(language, complexity);
				choose = true;
				break;
			}
			else if (position == 2)
			{
				nextView = new OptionView(language, complexity);
				choose = true;
				break;
			}
			else
			{
				exit(0);
			}

		case 27://Esc
			exit(0);
		}
	}
	return nextView;
}