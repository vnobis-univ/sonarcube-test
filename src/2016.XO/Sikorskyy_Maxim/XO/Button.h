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

Button getButton(Button* Buttons, int size);

bool convertToButton(Button& button);

bool matches(Button button, Button* Buttons, int size);