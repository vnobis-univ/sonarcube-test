#pragma once
#include "View.h"
#include "Alphabet.h"
#include "wordHandler.h"
#include "wordGetter.h"

class GameView : public View {
	int score;

protected:
	GameView(Difficulty _lvl);
	~GameView();

	WordGetter* wordGetter;

	vector<string> info;
	Alphabet alphabet;

	void updateInfo(int HP, int score, wordHandler word);
	virtual void draw();
	virtual View* handle();
};

class UkrGameView : public GameView {
public:
	UkrGameView(Difficulty _lvl);
};

class EngGameView : public GameView {
public:
	EngGameView(Difficulty _lvl);
};
