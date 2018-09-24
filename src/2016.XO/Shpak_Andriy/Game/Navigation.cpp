#include <conio.h>
#include "Navigation.h"

bool getWhichButton(Button& button)
{
	int number = _getch();
	
	if (number == 224)
		number = _getch();

	switch (number)
	{
	case 72:
		button = Button::UP;
		break;
	case 75:
		button = Button::LEFT;
		break;
	case 77:
		button = Button::RIGHT;
		break;
	case 80:
		button = Button::DOWN;
		break;
	case 13:
		button = Button::ENTER;
		break;
	case 120:
		button = Button::X;
		break;
	default:
		return false;
	}

	return true;
}
