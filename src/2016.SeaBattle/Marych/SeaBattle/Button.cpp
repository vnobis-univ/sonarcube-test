#include "Button.h"

#include <conio.h>


bool convertKeyToButton(Button& button)
{
	bool isSuccess = true;
	int ch = _getch();

	if (ch == 224)
	{
		ch = _getch();
	}
	switch (ch)
	{
	case 13:
		button = Button::ENTER;
		break;
	case 27:
		button = Button::ESC;
		break;
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
	case 114://letter 'r'
		button = Button::ROTATE;
		break;
	default:
		isSuccess = false;
	}
	return isSuccess;
}

bool isAllowed(Button button, Button* allowedActionsArray, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (allowedActionsArray[i] == button)
		{
			return true;
		}
	}
	return false;
}

Button getNavigationAction(Button* allowedActionsArray, int size)
{
	while (true)
	{
		Button inputButton;
		if (convertKeyToButton(inputButton) && isAllowed(inputButton, allowedActionsArray, size))
		{
			return inputButton;
		}
	}
}