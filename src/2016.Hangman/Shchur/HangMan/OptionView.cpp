#include "OptionView.h"

OptionView::OptionView(): language(Lokalization::En), complexity(Complexity::Easy), positionV(0){}

OptionView::OptionView(Lokalization lang, Complexity comp): language(lang), complexity(comp), positionV(0){}

Printer pan(ConsoleColor::Black, ConsoleColor::LightGreen);
Printer selectedPan(ConsoleColor::Black, ConsoleColor::White);

void OptionView::draw()
{
	system("cls");
	if (language == Lokalization::En)
	{
		printTextOnTheCenter(0, "Options", pan);
		for (int i = 0; i < 2; ++i)
		{
			short pos = 5 * i + 5;
			i == positionV ? printTextOnTheCenter(pos, firstEn[i], selectedPan) : printTextOnTheCenter(pos, firstEn[i], pan);
		}
		printTextOnTheCenter(22, "Press Esc to go back", pan);
	}
	else
	{
		printTextOnTheCenter(0, "Настройки", pan);
		for (int i = 0; i < 2; ++i)
		{
			short pos = 5 * i + 5;
			i == positionV ? printTextOnTheCenter(pos, firstUa[i], selectedPan) : printTextOnTheCenter(pos, firstUa[i], pan);
		}
		printTextOnTheCenter(22, "Натисніть Esc для виходу", pan);
	}
}

View * OptionView::handle()
{
	View* nextView = this;
	bool choise = false;
	bool horizontal = false;
	positionH = 0;
	while (!choise)
	{
		switch (_getch())
		{
		case 80://Down
			if (!horizontal)
			{
				++positionV;
				if (positionV > 1)
				{
					positionV = 1;
				}
				draw();
			}
			break;
		case 72://Up
			if (!horizontal)
			{
				--positionV;
				if (positionV < 0)
				{
					positionV = 0;
				}
				draw();
			}
			break;
		case 75://Left
			if (horizontal)
			{
				--positionH;
				if (positionH < 0)
				{
					positionH = 0;
				}
				drawMenu(language);
			}
			break;
		case 77://Right
			if (horizontal)
			{
				++positionH;
				if (positionH > 1 && positionV == 0)
				{
					positionH = 1;
				}
				else if (positionH > 2 && positionV == 0)
				{
					positionH = 2;
				}
				drawMenu(language);
			}
			break;
		case 27://Esc
			if (!horizontal)
			{
				nextView = new StartView(language, complexity);
				choise = true;
				break;
			}
			else
			{
				horizontal = false;
				choise = true;
				positionH = 0;
				break;
			}
		case 13://Enter
			if (!horizontal)
			{
				positionH = 0;
				drawMenu(language);
				horizontal = true;
			} 
			else
			{
				if (positionV == 0)
				{
					if (positionH == 0)
					{
						language = Lokalization::En;
					}
					else
					{
						language = Lokalization::Ua;
					}
				}
				else
				{
					if (positionH == 0)
					{
						complexity = Complexity::Easy;
					}
					else if (positionH == 1)
					{
						complexity = Complexity::Medium;
					}
					else
					{
						complexity = Complexity::Hard;
					}
				}
				choise = true;
			}
			break;
		}
	}
	return nextView;
}

void OptionView::drawMenu(Lokalization lokal)
{
	if (positionV == 0)
	{
		if (lokal == Lokalization::En)
		{
			if (positionH == 0)
			{
				setCursor(52 / 4, 7);
				selectedPan << lokalizationEn[0];
				setCursor(52 / 1.6, 7);
				pan << lokalizationEn[1];
			}
			else
			{
				setCursor(52 / 4, 7);
				pan << lokalizationEn[0];
				setCursor(52 / 1.6, 7);
				selectedPan << lokalizationEn[1];
			}
		}
		else
		{
			if (positionH == 0)
			{
				setCursor(52 / 4, 7);
				selectedPan << lokalizationUa[0];
				setCursor(52 / 1.6, 7);
				pan << lokalizationUa[1];
			}
			else
			{
				setCursor(52 / 4, 7);
				pan << lokalizationUa[0];
				setCursor(52 / 1.6, 7);
				selectedPan << lokalizationUa[1];
			}
		}
	}
	else
	{
		if (lokal == Lokalization::En)
		{
			if (positionH == 0)
			{
				setCursor(52 / 3.5, 13);
				selectedPan << complexityEn[0];
				setCursor(52 / 2.2, 13);
				pan << complexityEn[1];
				setCursor(52 / 1.5, 13);
				pan << complexityEn[2];
			}
			else if (positionH == 1)
			{
				setCursor(52 / 3.5, 13);
				pan << complexityEn[0];
				setCursor(52 / 2.2, 13);
				selectedPan << complexityEn[1];
				setCursor(52 / 1.5, 13);
				pan << complexityEn[2];
			}
			else
			{
				setCursor(52 / 3.5, 13);
				pan << complexityEn[0];
				setCursor(52 / 2.2, 13);
				pan << complexityEn[1];
				setCursor(52 / 1.5, 13);
				selectedPan << complexityEn[2];
			}
		}
		else
		{
			if (positionH == 0)
			{
				setCursor(52 / 3.5, 13);
				selectedPan << complexityUa[0];
				setCursor(52 / 2.2, 13);
				pan << complexityUa[1];
				setCursor(52 / 1.5, 13);
				pan << complexityUa[2];
			}
			else if (positionH == 1)
			{
				setCursor(52 / 3.5, 13);
				pan << complexityUa[0];
				setCursor(52 / 2.2, 13);
				selectedPan << complexityUa[1];
				setCursor(52 / 1.5, 13);
				pan << complexityUa[2];
			}
			else
			{
				setCursor(52 / 3.5, 13);
				pan << complexityUa[0];
				setCursor(52 / 2.2, 13);
				pan << complexityUa[1];
				setCursor(52 / 1.5, 13);
				selectedPan << complexityUa[2];
			}
		}
	}
}

Complexity OptionView::getComplexity()
{
	return complexity;
}
