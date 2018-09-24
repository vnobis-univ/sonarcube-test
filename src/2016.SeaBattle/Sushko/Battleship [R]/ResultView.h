#pragma once
#include <iostream>
#include "View.h"
#include "HScoreFileManager.h"

class ResultView : public View {
	int score;
	bool achieved;
	HScoreManager manager;

protected:
	vector<string> info;

	ResultView(int m_score);

	virtual void draw();
	virtual View* handle();
};

class EngResult : public ResultView {
public:
	EngResult(int m_score);
};

class UkrResult: public ResultView {
public:
	UkrResult(int m_score);
};