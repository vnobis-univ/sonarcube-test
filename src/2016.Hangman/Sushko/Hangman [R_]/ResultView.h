#pragma once
#include <iostream>
#include "View.h"
#include "Alphabet.h"
#include "HScoreFileManager.h"

class ResultView : public View {
	int score;
	bool achieved;
	HScoreManager manager;

	string askForName();
protected:
	vector<string> info;

	ResultView(int m_score, Difficulty level);

	virtual void draw();
	virtual View* handle();
};

class EngResult : public ResultView {
public:
	EngResult(int m_score, Difficulty level);
};

class UkrResult: public ResultView {
public:
	UkrResult(int m_score, Difficulty level);
};