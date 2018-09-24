#pragma once
#include "View.h"
#include "Printer.h"
#include <string>
#include <vector>

class MenuView : public View
{
public:
	enum class MenuOptions
	{
		start,
		highscores,
		options,
		exit
	};

private:
	size_t menuOptionsSize;
	std::vector<std::string> vecOfOptions;
	MenuOptions selectedOption;

	static std::string howToShowSelected[2];
	static int whereMenuStarts;
	static int numberOfEmptyLines;

public:
	MenuView();

	void draw();

	View* handle();
	
private:
	View* getNextView() const;

	void drawMenu();

	void handleMove(MenuOptions, MenuOptions);
};

