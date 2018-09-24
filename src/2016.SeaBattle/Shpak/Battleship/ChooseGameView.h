#pragma once
#include "View.h"
#include <vector>
#include <string>

class ChooseGameView : public View
{
	enum class GameOptions;

	std::vector<std::string> vecOfOptions;
	std::vector<std::string> vecOfOnlineOptions;
	GameOptions currentOption;

public:
	ChooseGameView();

	void draw();

	View* handle();

private:
	void drawGameOptions(std::vector<std::string>);

	GameOptions handleChoosing(std::vector<std::string>);

private:
	enum class GameOptions 
	{
		firstGameOption,
		secondGameOption
	};
};

