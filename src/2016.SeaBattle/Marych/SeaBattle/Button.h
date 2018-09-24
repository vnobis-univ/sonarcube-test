#pragma once

enum class Button
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	ENTER,
	ESC,
	ROTATE//to rotate a ship, just a letter 'r'
};

Button getNavigationAction(Button* allowedActionsArray, int size);