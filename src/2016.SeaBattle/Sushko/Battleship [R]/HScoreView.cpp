#include "HScoreView.h"
#include "ExternUtils.h"
#include "StartView.h"
#include <iostream>
using namespace std;

HScoreView::HScoreView(): info(vector<string>(8)), manager(HScoreManager()) {} 

void HScoreView::printInfo(int& coordX, int& coordY) {

	lightAqua.midLinePrint(27, info[3]);
	lightAqua.midLinePrint(1, info[0]);

	yellow.setColor();

	moveTo(coordX, coordY), cout << info[1];
	moveTo(coordX + 22, coordY), cout << info[2];
}

void HScoreView::printScores(int& coordX, int& coordY) {

	for (auto& i : manager.getScores()) {
		coordY += 2;
		moveTo(coordX, coordY), cout << i.name;
		moveTo(coordX + 25, coordY), cout << i.score;
	}
}

void HScoreView::draw() {

	int coordX = 45, coordY = 4;

	printInfo(coordX, coordY);
	white.setColor();
	printScores(coordX, coordY);
}

View* HScoreView::handle() {

	View* nextView = this;
	while (_getwch() != 27) {}

	typeid(*this) == typeid(EngHScore) ? nextView = new EngStartView() : nextView = new UkrStartView();
	return nextView;
}

EngHScore::EngHScore()  {

	info[0] = "HightScores";
	info[1] = "Sailor:";
	info[2] = "Score:";
	info[3] = "Press ESC to return to main menu";

}

UkrHScore::UkrHScore() {

	info[0] = "Рекорди";
	info[1] = "Гравець:";
	info[2] = "Досягенння:";
	info[3] = "ESC для повернення в головне меню";
}