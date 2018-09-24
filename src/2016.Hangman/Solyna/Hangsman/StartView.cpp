#include "StartView.h"
#include "functions.h"

#include "LanguagesView.h"
#include "ModesView.h"
StartView::StartView( Languages l,Difficulty d) : View(l,d)
{
	showConsoleCursor(false);
	arrayOfOptions = new string[amountOfOptions];
	if(lang == English)
	{
		arrayOfOptions[0] = "Start";
		arrayOfOptions[1] = "High Scores";
		arrayOfOptions[2] = "Languages";
		arrayOfOptions[3] = "Exit";
	}
	else
	{
		arrayOfOptions[0] = "Почати";
		arrayOfOptions[1] = "Рекорди";
		arrayOfOptions[2] = "Мови";
		arrayOfOptions[3] = "Вихід";
	}
	selectedOption = arrayOfOptions[0];
}


void StartView:: draw()
{
	clean();
	for(size_t i = 0; i < amountOfOptions; ++i)
	{
		if(arrayOfOptions[i] == selectedOption)
		{
			Printer p(AQUA,LIGHT_AQUA);
			printAtCenterOfLine(8 + 2*i ,"* " + arrayOfOptions[i] + " *" ,p, consoleWidth);
		}
		else
		{
			Printer p(LIGHT_BLUE,LIGHT_AQUA);
			printAtCenterOfLine(8 + 2*i, arrayOfOptions[i], p, consoleWidth);
		}
	}
}

View * StartView::nextView()
{
	View * nextV = this;
	if (selectedOption == arrayOfOptions[3])
	{
		nextV = nullptr;
	}
	else if(selectedOption == arrayOfOptions[2])
	{
		nextV = new LanguagesView(lang,dif);
	}
	else if( selectedOption == arrayOfOptions[0])
	{
		nextV = new ModesView(lang,dif);
	}
	else
	{
		setConsoleSize(100, 25);
		nextV = new HighScoresView(lang, dif);
	}
	return nextV;
}

int StartView::positionOfselectedOption()
{
	for(size_t i = 0; i < amountOfOptions; ++i)
	{
		if(arrayOfOptions[i] == selectedOption)
		{
			return i;
		}
	}
}

View * StartView::handle()
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
