#include "ModesView.h"
#include "functions.h"
#include "GameView.h"


ModesView::ModesView(Languages l,Difficulty d): View(l, d)
{
	arrayOfOptions = new string[amountOfOptions];
	if(lang == English)
	{
		arrayOfOptions[0] = "Easy";
		arrayOfOptions[1] = "Medium";
		arrayOfOptions[2] = "Hard";
		arrayOfOptions[3] = "Return to main menu";
	}
	else
	{
		arrayOfOptions[0] = "Легкий";
		arrayOfOptions[1] = "Середній";
		arrayOfOptions[2] = "Складний";
		arrayOfOptions[3] = "Повернутись до головного меню";
	}
	selectedOption = arrayOfOptions[0];
}

void ModesView::draw()
{
	clean();
	for(size_t i = 0; i < amountOfOptions; ++i)
	{
		if(arrayOfOptions[i] == selectedOption)
		{
			Printer p(AQUA,LIGHT_AQUA);
			printAtCenterOfLine(8 + 2*i,"* " + arrayOfOptions[i] + " *",p, consoleWidth);
		}
		else
		{
			Printer p(LIGHT_BLUE,LIGHT_AQUA);
			printAtCenterOfLine(8 + 2*i, arrayOfOptions[i] ,p, consoleWidth);
		}
	}
}
int ModesView::positionOfselectedOption()
{
	for(size_t i = 0; i < amountOfOptions; ++i)
	{
		if(arrayOfOptions[i] ==selectedOption)
		{
			return i;
		}
	}
}

View * ModesView::nextView()
{
	View * nextV = this;
	if (selectedOption == arrayOfOptions[3])
	{
		nextV = new StartView(lang, dif);
	}
	else if(selectedOption == arrayOfOptions[0])
	{
		dif = Easy;
		nextV = new GameView(lang, dif);
	}
	else if(selectedOption == arrayOfOptions[1])
	{
		dif = Medium;
		nextV = new GameView(lang, dif);
	}
	else
	{
		dif = Hard;
		nextV = new GameView(lang,dif);
	}
	return nextV;
}

View * ModesView::handle()
{
	int key = _getch();
	while(key)
	{
		if (key == 224)//if arrow key was pressed
		{
			key = _getch();
		}
		switch(key)
		{
		case(13): // Enter key
			{
				return nextView();
			}
		case(72): // up
			{
				if (positionOfselectedOption() == 0)
				{
					selectedOption = arrayOfOptions[amountOfOptions- 1];
					draw();
				}
				else
				{
					selectedOption = arrayOfOptions[positionOfselectedOption()- 1];
					draw();
				}
			}
			break;
		case(80): // down
			{
				if (positionOfselectedOption() == amountOfOptions - 1)
				{
					selectedOption = arrayOfOptions[0];
					draw();
				}
				else
				{
					selectedOption = arrayOfOptions[positionOfselectedOption() +1];
					draw();
				}
			}
			break;
		}
		key = _getch();
	}
}
