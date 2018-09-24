#include "Complexity.h"

Printer complex(ConsoleColor::LightGray, ConsoleColor::DarkGray);
Printer selectedComplex(ConsoleColor::LightGray, ConsoleColor::Red);

void ComplexityView::draw()
{
	View::draw();
	printTextOnTheCenter(2, "Please choose a complexity:", selectedComplex);
	printMenu();
}

View* ComplexityView::handle()
{
	View* nextview = this;
	bool choose = false;
	while (!choose)
	{
		switch (_getch())
		{
		case 80://down
			++position;
			if (position > 2)
			{
				position = 2;
			}
			printMenu();
			break;
		case 72://up
			--position;
			if (position < 0)
			{
				position = 0;
			}
			printMenu();
			break;
		case 27://esc
			nextview = new StartView();
			choose = true;
			break;
		case 13://enter
			if (position == 0)
			{
				nextview = new FieldView(0, options[0]);
			}
			else if (position == 1)
			{
				nextview = new FieldView(0, options[1]);
			}
			else
			{
				nextview = new FieldView(0, options[2]);
			}
			choose = true;
			system("cls");
			break;
		}
	}
	return nextview;
}

void ComplexityView::printMenu()
{
	for (int i = 0; i < 3; ++i)
	{
		i == position ? printTextOnTheCenter(2 * i + 4, options[i], selectedComplex) : printTextOnTheCenter(2 * i + 4, options[i], complex);
	}
}
