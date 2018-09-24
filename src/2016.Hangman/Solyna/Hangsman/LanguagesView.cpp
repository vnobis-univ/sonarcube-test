#include "LanguagesView.h"


LanguagesView::LanguagesView(Languages l,Difficulty d): View(l, d)
{
	arrayOfOptions = new string[amountOfOptions];
	if(lang == English)
	{
		arrayOfOptions[0] = "English";
		arrayOfOptions[1] = "Ukrainian";
		arrayOfOptions[2] = "Return to main menu";
	}
	else
	{
		arrayOfOptions[0] = "Англійська";
		arrayOfOptions[1] = "Українська";
		arrayOfOptions[2] = "Повернутись до головного меню";
	}
	selectedOption = arrayOfOptions[0];
}

int LanguagesView::positionOfselectedOption()
{
	for(size_t i = 0; i < amountOfOptions; ++i)
	{
		if(arrayOfOptions[i] == selectedOption)
		{
			return i;
		}
	}
}

View * LanguagesView::nextView()
{
	View * nextV ;
	if (selectedOption == arrayOfOptions[1])
	{
		if (lang == English)
		{
			lang = Ukrainian;
			nextV = new LanguagesView(lang,dif);
		}
		else
		{
			nextV = this;
		}
		
	}
	else if(selectedOption == arrayOfOptions[0])
	{
		if (lang == Ukrainian)
		{
			lang = English;
			nextV = new LanguagesView(lang,dif);
			draw();
		}
		else
		{
			nextV = this;
		}
	}
	else
	{
		nextV = new StartView(lang,dif);
	}
	return nextV;
}

void LanguagesView:: draw()
{
	clean();
	for(size_t i = 0; i < amountOfOptions; ++i)
	{
		if(arrayOfOptions[i] == selectedOption)
		{
			SetConsoleCP(1251); 
			SetConsoleOutputCP(1251);
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

View * LanguagesView::handle()
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
			break;
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


