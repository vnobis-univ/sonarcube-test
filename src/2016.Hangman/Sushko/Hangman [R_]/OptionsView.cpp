#include <iostream>
#include "MenuView.h"
#include "OptionsView.h"
#include "OptionSelector.h"
#include "ConsoleUtils.h"

using namespace std;

const int optionsNum = 2;
const int additNum = 2;
const int infoNum = 3;

OptionsView::OptionsView(Difficulty l) : View(l), options(vector<string>(optionsNum)), additions(vector<string>(2)),
difficulty(vector<string>(3)), language(vector<string>(2)), info(vector<string>(infoNum)) {}

void OptionsView::printOptions(int current)
{
	for (int i = 0; i < options.size(); ++i)
	{
		i == current ? yellow.MidLinePrint(8 + i * 8, options[i]) :
			white.MidLinePrint(8 + i * 8, options[i]);
	}
}

void OptionsView::printSubOptions(vector<string> vec, int margin, int line, int curr, bool show) {

	for (int i = 0; i < vec.size(); ++i)
	{
		if (show) 
			i == curr ? yellow.setColor() : white.setColor();
		else 
			purple.setColor();

		moveTo(margin, line);
		cout << vec[i];
		margin += vec[i].length() + 5;
	}
}

void OptionsView::updateSubObtions(int selected, int currLang, int currLVL)
{
	if (selected == 0) 
		printSubOptions(language, 48, 10, currLang), printSubOptions(difficulty, 46, 18, 0, false);
	else 
		printSubOptions(language, 48, 10, 0, false), printSubOptions(difficulty, 46, 18, currLVL);
}


void OptionsView::draw() 
{
	printOptions(), printSubOptions(language, 48, 10, 0);
	lPurpleOnPurple.MidLinePrint(2, info[2]);
	white.MidLinePrint(27, info[0]);
	white.MidLinePrint(24, info[1]);
}

View* OptionsView::handle()
{
	View* nextView = this;

	OptionSelector selected(0, 0, 1), currLang(0, 0, 1), currLVL(int(lvl), 0, 2);

	bool nextChosen = false;
	while (!nextChosen)
	{
		switch (_getwch())
		{
		case 72: //down
			--selected;
			break;
		case 80: //up
			++selected;
			break;
		case 75: //left
			selected == 0 ? --currLang : --currLVL;
			break;
		case 77: //right
			selected == 0 ? ++currLang : ++currLVL;
			break;
		case 13: //enter -> choosing next View
			if (selected == 0) {
				nextChosen = true;
				currLang == 0 ? nextView = new EngOptions(lvl) : nextView = new UkrOptions(lvl);
			}
			else 
				lvl = (Difficulty)currLVL.current;
			break;
		case 27:
			typeid(*this) == typeid(EngOptions) ? nextView = new EngMenu(lvl) : nextView = new UkrMenu(lvl);
			nextChosen = true;
			break;
		}

		printOptions(selected);
		updateSubObtions(selected, currLang, currLVL);
	}

	return nextView;
}

EngOptions::EngOptions(Difficulty level) : OptionsView(level)
{
	options[0] = "LANGUAGE:";
	options[1] = "DIFFICULTY LEVEL:";
	language[0] = "English";
	language[1] = "Ukrainian";
	difficulty[0] = "Easy";
	difficulty[1] = "Medium";
	difficulty[2] = "Hard";
	info[0] = "(c)all rights reserved, 2016";
	info[1] = "Press ESC to return to main menu";
	info[2] = "OPTIONS:";
}

UkrOptions::UkrOptions(Difficulty level) : OptionsView(level)
{
	options[0] = "МОВА:";
	options[1] = "СКЛАДНІСТЬ:";
	language[0] = "Англійська";
	language[1] = "Українська";
	difficulty[0] = "Легко";
	difficulty[1] = "Звично";
	difficulty[2] = "Матан";
	info[0] = "(c) всі права захищено, 2016";
	info[1] = "Натисність ESC для повернення в меню";
	info[2] = "ОПЦІЇ:";
}