#include <iostream>
#include "ConsoleUtils.h"
#include "HScoresView.h"
#include "MenuView.h"

using namespace std;

HScoreView::HScoreView(Difficulty _lvl) : View(_lvl), info(vector<string>(8)), manager(HScoreManager()) {}

void HScoreView::printInfo(int& coordX, int& coordY) {

	yellow.MidLinePrint(27, info[4]);
	lPurpleOnPurple.MidLinePrint(1, info[0]);
	yellow.setColor();

	moveTo(coordX, coordY), cout << info[1];
	moveTo(coordX + 19, coordY), cout << info[2];
	moveTo(coordX + 38, coordY), cout << info[3];
}

void HScoreView::printScores(int& coordX, int& coordY) {

	for (int j = 2; j >= 0; --j) {

		vector<HScore> temp = manager.getHScore((Difficulty)j);

		for (auto& i : temp) {
			coordY += 2;
			moveTo(coordX, coordY), j == 2 ? cout << info[5] : (j == 1 ? cout << info[6] : cout << info[7]);
			moveTo(coordX + 19, coordY), cout << i.name;
			moveTo(coordX + 38, coordY), cout << i.score;
		}
	}
}

void HScoreView::draw() 
{
	int coordX = 35, coordY = 4;

	printInfo(coordX, coordY);
	white.setColor();
	printScores(coordX, coordY);
}

View* HScoreView::handle()
{
	View* nextView = this;
	while (_getwch() != 27) {}

	typeid(*this) == typeid(EngHScore) ? nextView = new EngMenu(lvl) : nextView = new UkrMenu(lvl);
	return nextView;
}

EngHScore::EngHScore(Difficulty _lvl) : HScoreView(_lvl)
{
	info[0] = "HightScores";
	info[1] = "Difficulty:";
	info[2] = "Name:";
	info[3] = "Score:";
	info[4] = "Press ESC to return to main menu";
	info[5] = "HARD";
	info[6] = "NORMAL";
	info[7] = "EASY";
}

UkrHScore::UkrHScore(Difficulty _lvl) : HScoreView(_lvl)
{
	info[0] = "Â³äâàæí³ ãðàâö³";
	info[1] = "Ñêëàäí³ñòü:";
	info[2] = "²ì'ÿ:";
	info[3] = "Äîñÿãíåííÿ:";
	info[4] = "Íàòèñí³ñòü ESC äëÿ ïîâåðíåííÿ â ìåíþ";
	info[5] = "ÂÀÆÊÈÉ";
	info[6] = "ÍÎÐÌÀËÜÍÈÉ";
	info[7] = "ËÅÃÊÈÉ";
}
