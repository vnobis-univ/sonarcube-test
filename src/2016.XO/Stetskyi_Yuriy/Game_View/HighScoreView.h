#pragma once

class HighScoreView : public View
{
public:
	HighScoreView()
	{
	}

	void draw();

	void setScores(string, int);
};
