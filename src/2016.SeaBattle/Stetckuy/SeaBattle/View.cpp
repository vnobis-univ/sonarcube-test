#pragma once

#include "View.h"
#include "Printer.h"

using namespace std;

void View::drawBackground(int left, int top, int width, int height, COLORREF background) // draws background of the game
{
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SelectObject(hdc, GetStockObject(DC_PEN));

	SetDCBrushColor(hdc, background);
	SetDCPenColor(hdc, background);

	GetClientRect(hwnd, &rect);
	Rectangle(hdc, left, top, left + width, top + height);
}

void View::clear()
{
	system("cls");

	drawBackground(0, 0, CONSOLE_WIDTH*FONT_WIDTH, CONSOLE_HEIGHT*FONT_HEIGHT, RGB(0, 100, 200));
}

Language View::getLanguage() const
{
	return windowLanguage;
}

void View::setLanguage(Language lan)
{
	windowLanguage = lan;
}

void View::configure() // configures the languare og the markUpText according to the language chosen by user
{
	if (options.language != windowLanguage) // if languages are different
	{
		if (options.language == Language::UKRAINIAN) // if current language chosen by user is Ukrainian
		{
			for (size_t i = 0; i < markUpText.size(); ++i) // translates all English phrases into Ukrainian
			{
				for (size_t j = 0; j < options.englMarkUp.size(); ++j)
				{

					if (markUpText[i] == options.englMarkUp[j]) // finds position of phrase and "translates" it
					{
						markUpText[i] = options.ukrMarkUp[j];
						break;
					}

				}
			}

			for (size_t i = 0; i < menuItems.size(); ++i)
			{
				for (size_t j = 0; j < options.englMarkUp.size(); ++j)
				{

					if (menuItems[i].text == options.englMarkUp[j])
					{
						menuItems[i].text = options.ukrMarkUp[j];
						break;
					}

				}
			}
		}
		else // and vice versa
		{
			for (size_t i = 0; i < markUpText.size(); ++i)
			{
				for (size_t j = 0; j < options.ukrMarkUp.size(); ++j)
				{

					if (markUpText[i] == options.ukrMarkUp[j])
					{
						markUpText[i] = options.englMarkUp[j];
						break;
					}

				}
			}

			for (size_t i = 0; i < menuItems.size(); ++i)
			{
				for (size_t j = 0; j < options.ukrMarkUp.size(); ++j)
				{

					if (menuItems[i].text == options.ukrMarkUp[j])
					{
						menuItems[i].text = options.englMarkUp[j];
						break;
					}

				}
			}
		}

		windowLanguage = options.language; // sets proper window language
	}
}