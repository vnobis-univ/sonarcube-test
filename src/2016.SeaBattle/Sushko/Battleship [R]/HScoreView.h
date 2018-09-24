#pragma once
#include "View.h"
#include "HScoreFileManager.h"

class HScoreView : public View {

	void printInfo(int& coordX, int& coordY);
	void printScores(int& coordX, int& coordY);
protected:
	HScoreView();

	HScoreManager manager;
	vector<string> info;

	virtual void draw();
	virtual View* handle();
};

class EngHScore : public HScoreView {
public:
	EngHScore();
};

class UkrHScore : public HScoreView {
public:
	UkrHScore();
};