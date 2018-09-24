#include "ResultView.h"
#include "ConsoleUtils.h"
#include "HScoresView.h"
#include "MenuView.h"
#include <conio.h>

ResultView::ResultView(int m_score, Difficulty level) : View(level), info(vector<string>(5)), score(m_score),
achieved(false), manager(HScoreManager()) {

	vector<HScore> scores = manager.getHScore(lvl);
	achieved = scores[scores.size() - 1].score < score;
}

string ResultView::askForName() {

	string name;
	white.setColor();
	moveTo(50,5), showCursor(true);

	int count = 0;

	bool entered = false;
	while (!entered) {

		char key = _getch();
		
		if (count < 10 && int(key) !=8 && int(key) != 13) {
			name += key;
			count++;
		}
	
		if ((int)key == 8 && name.length() > 0) {
			name.pop_back();
			moveTo(50, 4), white.Print(name + " ");
			count--;
		}
		
		if (int(key) == 13) {
			count == 0 ? lightRed.MidLinePrint(8, info[3]) : entered = true;
			if (!entered) {
				name = "anonymous";
				entered = true;
			}
		}
		
		moveTo(50, 4),white.Print(name);
	}

	showCursor(false);
	return name;
}

void ResultView::draw() {
	achieved ? white.MidLinePrint(3, info[0]) : white.MidLinePrint(3, info[1]);
}

View* ResultView::handle() {

	View* nextView = this;

	if (achieved) {
		string name = askForName();
		manager.update(lvl, HScore(name,score));

		typeid(*this) == typeid(EngResult) ? nextView = new EngHScore(lvl) : nextView = new UkrHScore(lvl);
	}
	else {
		white.MidLinePrint(5, info[2]);
		_getch();
		typeid(*this) == typeid(EngResult) ? nextView = new EngMenu(lvl) : nextView = new UkrMenu(lvl);
	}

	return nextView;
}

EngResult::EngResult(int m_score, Difficulty level) : ResultView(m_score, level)  {
	info[0] = "CONGRATULATIONS! ENTER YOUR NAME: ";
	info[1] = "We are so sory... Try again!";
	info[2] = "Press any key to return to main menu";
	info[3] = "EMPTY FIELD!";
}

UkrResult::UkrResult(int m_score, Difficulty level) : ResultView(m_score,level) {
	info[0] = "Вітаємо! Введіть своє ім'є :";
	info[1] = "Нам шкода.. спробуйте ще";
	info[2] = "Натисність будь-яку клавішу для повернення в головне меню";
	info[3] = "ПОРОЖНЄ ПОЛЕ ВВОДУ";
}
