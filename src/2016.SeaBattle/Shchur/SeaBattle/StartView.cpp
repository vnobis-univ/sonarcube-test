#include "StartView.h"

Printer usualPen(ConsoleColor::White, ConsoleColor::Blue);
Printer selectedPen(ConsoleColor::White, ConsoleColor::Brown);

StartView::StartView() : language(Lokalization::En), position(0) {}
StartView::StartView(Lokalization lang): language(lang), position(0) {}

void StartView::draw()
{
	system("cls");
	Printer WhiteHoleStart(ConsoleColor::White, ConsoleColor::White);
	View::draw();
	for (int i = 7; i < consoleHeight - 8; ++i)
	{
		setCursor(0, i);
		for (int j = 0; j < consoleWidth; ++j)
		{
			WhiteHoleStart << " ";
		}
	}
	printMenu();
}

void StartView::printMenu()
{
	for (int i = 0; i < 4; ++i)
	{
		int place = 4 * i + 5;
		if (language == Lokalization::En)
		{
			i == position ? printTextOnTheCenter(place, optionEn[i], selectedPen) : printTextOnTheCenter(place, optionEn[i], usualPen);
		}
		else
		{
			i == position ? printTextOnTheCenter(place, optionUa[i], selectedPen) : printTextOnTheCenter(place, optionUa[i], usualPen);
		}
	}
}

View * StartView::handle()
{
	bool isChosen = false;
	View* nextView = this;
	while (!isChosen)
	{
		switch (_getch())
		{
		case Down:
			++position;
			if (position > 3)
			{
				position = 3;
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
			nextView = NULL;
			isChosen = true;
			break;
			case Enter:
				if (position == 0)
				{
					nextView = new PreFieldView(language);
				}
				else if (position == 1)
				{
					nextView = new HighscoresView(language);
				}
				else if (position == 2)
				{
					nextView = new LokalizationView(language);
				}
				else if (position == 3)
				{
					nextView = NULL;
				}
				isChosen = true;
				break;
		}
	}
	return nextView;
}
