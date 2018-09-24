#include "ResultView.h"
#include "ConsoleUtils.h"
#include "ResultView.h"
#include "StartView.h"
#include "HScoreView.h"
#include "ExternUtils.h"
#include <conio.h>

ResultView::ResultView(int m_score) :info(vector<string>(5)), score(m_score),
achieved(false), manager(HScoreManager()) {

	vector<HScore> scores = manager.getScores();
	achieved = scores[scores.size() - 1].score < score;
}


void ResultView::draw() {
	achieved ? white.midLinePrint(3, info[0]) : white.midLinePrint(3, info[1]);
}

View* ResultView::handle() {

	View* nextView = this;

	if (achieved) {
		string name = consoleInput({55,5}, 8,-128,127);
		manager.update(HScore(name,score));

		typeid(*this) == typeid(EngResult) ? nextView = new EngHScore() : nextView = new UkrHScore();
	}
	else {
		white.midLinePrint(5, info[2]);
		_getch();
		typeid(*this) == typeid(EngResult) ? nextView = new EngStartView() : nextView = new UkrStartView();
	}

	return nextView;
}

EngResult::EngResult(int m_score) : ResultView(m_score)  {
	info[0] = "CONGRATULATIONS! ENTER YOUR NAME: ";
	info[1] = "We are so sory... Try again!";
	info[2] = "Press any key to return to main menu";
	info[3] = "EMPTY FIELD!";
}

UkrResult::UkrResult(int m_score) : ResultView(m_score) {
	info[0] = "Вітаємо! Введіть своє ім'є :";
	info[1] = "Нам шкода.. спробуйте ще";
	info[2] = "Натисність будь-яку клавішу для повернення в головне меню";
	info[3] = "ПОРОЖНЄ ПОЛЕ ВВОДУ";
}
