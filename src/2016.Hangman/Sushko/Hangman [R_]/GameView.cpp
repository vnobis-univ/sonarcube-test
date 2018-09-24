#include "GameView.h"
#include "HangedManDrawer.h"
#include "ResultView.h"
#include "MenuView.h"
#include <conio.h>
using namespace std;

const int infoCount = 9;

GameView::GameView(Difficulty _lvl) :View(_lvl), score(0), info(vector<string>(infoCount)) {}

GameView::~GameView() { delete wordGetter; }

void GameView::updateInfo(int HP, int score, wordHandler word)
{
	moveTo(84, 4), yellow.Print(info[2] + to_string(score));
	moveTo(84, 6), yellow.Print(info[3] + to_string(HP) + " ");
	white.MidLinePrint(6, word.getProgress());
	white.MidLinePrint(4, info[0]);
	cout << alphabet;
}

void GameView::draw()
{
	white.MidLinePrint(27, info[7]);
	cout << alphabet;
	white.MidLinePrint(4, "LOADING......");
}

View* GameView::handle()
{
	View* nextView = this;
	wordHandler word;
	HangedManDrawer man(this, whitePen, purplePen, 140, 70, 1.2);

	try {
		word = wordGetter->getWord();
		string init = word.getUngessed();

		int HP = 11, fails = 0;
		updateInfo(HP, score, word);

		bool confirmedExit = false;
		while (!word.isGuessed() && !confirmedExit && HP > 0)
		{
			string prev = word.getProgress();

			char symbol = toupper(_getch());
			if (alphabet.validateKeypress(symbol)) {
				alphabet.setUsed(symbol);

				while (word.guessedChar(symbol)) {
					white.MidLinePrint(6, word.getProgress());
				}

				if (word.getProgress() == prev) {
					HP--;
					man.drawByStep(fails++);
				}
			}

			if ((int)symbol == 27) {
				confirmedExit = confirmExit(info[4]);

				if (confirmedExit) {
					typeid(*this) == typeid(EngGameView) ? nextView = new EngMenu(lvl) : nextView = new UkrMenu(lvl);
				}
			}

			updateInfo(HP, score, word);
		}
		
		if (!confirmedExit) {

			HP > 0 ? lightRed.MidLinePrint(15, info[5]) : lightRed.MidLinePrint(15, info[6]);

			if (HP > 0) {
				score++;
			}
			else {
				typeid(*this) == typeid(EngGameView) ? nextView = new EngResult(score, lvl) : nextView = new UkrResult(score, lvl);
				man.hang();
				white.MidLinePrint(8, init);
			}
			systemPauseAt(45, 25, info[8]);
			alphabet.reset();
		}
	}
	catch (CInternetException* e) {
		yellow.MidLinePrint(4, "NO INTERNET CONNECTION, LOADING FROM FILE");
		delete wordGetter;
		wordGetter = new FileWordGetter((Difficulty)(-1));
		systemPauseAt(45, 10, info[8]);
	}
	return nextView;
}

EngGameView::EngGameView(Difficulty _lvl) : GameView(_lvl) {

	alphabet = Alphabet(Lang::ENG);
	wordGetter = new InetWordGetter(_lvl);

	info[0] = "GUESS THE WORD:";
	info[2] = "Score: ";
	info[3] = "Attemps left : ";
	info[4] = "  PRESS ESC AGAIN TO COFIRM EXIT OR ANY KEY TO CONTINUE  ";
	info[5] = "YOU SURVIVED!";
	info[6] = "YOU LOSE :(";
	info[7] = "(c)all rights reserved, 2016";
	info[8] = "Press any key to continue ";
}

UkrGameView::UkrGameView(Difficulty _lvl) : GameView(_lvl) {

	alphabet = Alphabet(Lang::UKR);
	wordGetter = new FileWordGetter(_lvl);

	info[0] = "Слово, щоб вгадувати:";
	info[2] = "Здобуто : ";
	info[3] = "Доступно хиб: ";
	info[4] = "  ДЛЯ ПІДТВЕРДЖЕННЯ ВИХОДУ, НАТИСНІТЬ ESC ПОВТОРНО  ";
	info[5] = "ПЕРЕМОГА!";
	info[6] = "ПРОГРАШ :(";
	info[7] = "(c) всі права захищено, 2016";
	info[8] = "Натисніть для продовження";
}
