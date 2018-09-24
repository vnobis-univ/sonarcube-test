#include "MenuView.h"
#include "GameView.h"
#include "HScoresView.h"
#include "OptionsView.h"
#include "ConsoleUtils.h"
#include "OptionSelector.h"
#include "HangedManDrawer.h"

const int optionsNum = 4;
const int andditionsNum = 2;

MenuView::MenuView(Difficulty d) : View(d), options(vector<string>(optionsNum)), info(vector<string>(andditionsNum)) {}

void MenuView::printOptions(int current)
{
	for (int i = 0; i < options.size(); ++i) 
	{
		i != current ? white.MidLinePrint(2 * (i + 4), options[i]) :
			yellow.MidLinePrint(2 * (i + 4), options[i]);
	}
}

void MenuView::printInfo()
{
	lPurpleOnPurple.MidLinePrint(2, info[0]);
	white.MidLinePrint(27, info[1]);
}

void MenuView::draw()
{
	printOptions();
	printInfo();

	HangedManDrawer man2(this, whitePen, purplePen, 580, 85, 1.4);
	HangedManDrawer man(this, whitePen, purplePen, 150, 85, 1.4);

	man.drawAll(), man2.drawAll(), man2.hang(0);
}

View* MenuView::handle() {

	View* nextView = this;
	OptionSelector selected(0, 0, 3);

	while (_getwch() != 13) { //while != enter

		switch (_getwch()) {
		case 72:
			--selected;
			break;
		case 80:
			++selected;
			break;
		}

		printOptions(selected);
	}

	
	switch (selected) //enter -> choosing next View
	{
	case 0:
		typeid(*this) == typeid(EngMenu) ? nextView = new EngGameView(lvl) : nextView = new UkrGameView(lvl);
		break;
	case 1:
		typeid(*this) == typeid(EngMenu) ? nextView = new EngOptions(lvl) : nextView = new UkrOptions(lvl);
		break;
	case 2:
		typeid(*this) == typeid(EngMenu) ? nextView = new EngHScore(lvl) : nextView = new UkrHScore(lvl);
		break;
	case 3: exit(0);
		break;
	}

	return nextView;
}

EngMenu::EngMenu(Difficulty d) :MenuView(d) {

	options[0] = "START";
	options[1] = "OPTIONS";
	options[2] = "HIGH SCORES";
	options[3] = "EXIT";
	info[0] = "  WELCOME TO HANGMAN !";
	info[1] = "(c)all rights reserved, 2016";
}

UkrMenu::UkrMenu(Difficulty d) : MenuView(d) {

	options[0] = " œŒ◊¿“»";
	options[1] = " œ¿–¿Ã≈“–»";
	options[2] = "¬≤ƒ¬¿∆Õ≤ √–¿¬÷≤";
	options[3] = "¬»’≤ƒ";
	info[0] = "  ¬≤“¿™ÃŒ Õ¿ ÿ»¡≈Õ»÷≤ !";
	info[1] = "(c) ‚Ò≥ Ô‡‚‡ Á‡ıË˘ÂÌÓ, 2016";
}