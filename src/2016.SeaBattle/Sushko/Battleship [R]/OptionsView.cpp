#include <iostream>
#include "StartView.h"
#include "OptionsView.h"
#include "OptionSelector.h"
#include "ExternUtils.h"
#include "ConsoleUtils.h"
using namespace std;

const int langNum = 2;
const int infoNum = 4;

OptionsView::OptionsView() : language(vector<string>(langNum)), info(vector<string>(infoNum)) {}

void OptionsView::printLangOptions(int margin, int line, int curr) {

	for (int i = 0; i < language.size(); ++i) {

		i == curr ? yellow.setColor() : white.setColor();

		moveTo(margin, line);
		cout << language[i];
		margin += language[i].length() + 5;
	}
}

void OptionsView::draw() {

	white.midLinePrint(9, info[3]);
	lightAqua.midLinePrint(2, info[2]);
	lightAqua.midLinePrint(27, info[0]);
	lightAqua.midLinePrint(24, info[1]);

	printLangOptions(50, 12, 0);
}

View* OptionsView::handle() {

	View* nextView = this;

	OptionSelector current(0, 0, 1);

	bool nextChosen = false;
	while (!nextChosen) {

		switch (_getwch()) {

		case 75: // <-
			--current;
			break;
		case 77: // ->
		    ++current;
			break;
		case 13: //enter -> switch language
			nextChosen = true;
			current == 0 ? nextView = new EngOptions() : nextView = new UkrOptions();
			break;
		case 27:  //ESC ->  return to startView
			nextChosen = true;
			typeid(*this) == typeid(EngOptions) ? nextView = new EngStartView() : nextView = new UkrStartView();
			break;
		}
		printLangOptions(50, 12, current);
	}

	return nextView;
}

EngOptions::EngOptions(){

	language[0] = "English";
	language[1] = "Ukrainian";

	info[0] = "(c)all rights reserved, 2016";
	info[1] = "Press ESC to return to main menu";
	info[2] = "OPTIONS:";
	info[3] = " LANGUAGE:";
}

UkrOptions::UkrOptions() {
	language[0] = "Англійська   ";
	language[1] = "Українська";

	info[0] = "(c) всі права захищено, 2016";
	info[1] = "Натисніть ESC для повернення в головне меню";
	info[2] = "ОПЦІЇ: ";
	info[3] = " МОВА:";
}