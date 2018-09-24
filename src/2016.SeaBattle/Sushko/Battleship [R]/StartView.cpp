#include "StartView.h"
#include "ExternUtils.h"
#include "OptionsView.h"
#include "OptionSelector.h"
#include "HScoreView.h"
#include "RoomsView.h"
const int optionsNum = 4;
const int andditionsNum = 2;

StartView::StartView(): options(vector<string>(optionsNum)), info(vector<string>(andditionsNum)) {}

void StartView::printOptions(int current) {
	for (int i = 0; i < options.size(); ++i){
		i != current ? white.midLinePrint(2 * (i + 4), options[i]) :
			yellow.midLinePrint(2 * (i + 4), options[i]);
	}
}

void StartView::printInfo() {
	lightAqua.midLinePrint(2, info[0]);
	lightAqua.midLinePrint(27, info[1]);
}

void StartView::draw() {
	printOptions();
	printInfo();
}

View* StartView::handle() {

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
		typeid(*this) == typeid(EngStartView) ? nextView = new EngRoomsView() : nextView = new UkrRoomsView();
		break;
	case 1:
		typeid(*this) == typeid(EngStartView) ? nextView = new EngOptions() : nextView = new UkrOptions();
		break;
	case 2:
		typeid(*this) == typeid(EngStartView) ? nextView = new EngHScore() : nextView = new UkrHScore();
		break;
	case 3: exit(0);
		break;
	}

	return nextView;

	return nextView;
}

EngStartView::EngStartView(){
	options[0] = "START";
	options[1] = "OPTIONS";
	options[2] = "HIGH SCORES";
	options[3] = "EXIT  ";
	info[0] = "  WELCOME TO BATTLESHIP!  ";
	info[1] = "(c)all rights reserved, 2016";
}

UkrStartView::UkrStartView(){
	options[0] = "ÑÒÀÐÒ";
	options[1] = "ÎÏÖ²¯";
	options[2] = "ÐÅÊÎÐÄÈ";
	options[3] = "ÂÈÕ²Ä";
	info[0] = "  Â²ÒÀªÌÎ Â ÌÎÐÑÜÊÎÌÓ ÁÎ¯!  ";
	info[1] = "(c)âñ³ ïðàâà çàõèùåíî, 2016";
}
