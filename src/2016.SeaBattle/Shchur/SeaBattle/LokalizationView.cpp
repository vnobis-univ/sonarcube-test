#include "LokalizationView.h"

LokalizationView::LokalizationView(): language(Lokalization::En), position(0){}

LokalizationView::LokalizationView(Lokalization lang) : language(lang), position(0){}

void LokalizationView::draw()
{
	system("cls");
	View::draw();
	printMenu();
}
Printer viewPenLok(ConsoleColor::White, ConsoleColor::Red);
Printer selectedPenLok(ConsoleColor::White, ConsoleColor::Brown);
Printer usualPenLok(ConsoleColor::White, ConsoleColor::Blue);

void LokalizationView::printMenu()
{
	system("cls");
	printTextOnTheCenter(0, "*  Battleship Hero  *", viewPenLok);
	language == Lokalization::En ? printTextOnTheCenter(5, "Select language", viewPenLok) : printTextOnTheCenter(5, "Вибір мови", viewPenLok);
	for (int i = 0; i < 2; ++i)
	{
		int place = 5 * i + 10;
		if (language == Lokalization::En)
		{
			i == position ? printTextOnTheCenter(place, optionsEn[i], selectedPenLok) : printTextOnTheCenter(place, optionsEn[i], usualPenLok);
		}	
		else
		{
			i == position ? printTextOnTheCenter(place, optionsUa[i], selectedPenLok) : printTextOnTheCenter(place, optionsUa[i], usualPenLok);
		}
	}
}

View * LokalizationView::handle()
{
	View* nextView = this;
	bool isChosen = false;
	while (!isChosen)
	{
		switch (_getch())
		{
		case Down:
			++position;
			if (position > 1)
			{
				position = 1;
			}
			printMenu();
			break;
		case Up:
			--position;
			if (position < 0)
			{
				position = 0;
			}
			printMenu();
			break;
		case ESCAPE:
			nextView = new StartView(language);
			isChosen = true;
			break;
		case Enter:
			if (position == 0)
			{
				language = Lokalization::En;
			}
			else
			{
				language = Lokalization::Ua;
			}
			printMenu();
			break;
		}
	}
	return nextView;
}
