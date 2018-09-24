#pragma once

enum class Button
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ENTER,
	ESC,
	BACKSPACE
};

Button getButton(Button* possibleButtons, int size);

bool convertToButton(Button& button);

bool doesMatch(Button button, Button* possibleButtons, int size);