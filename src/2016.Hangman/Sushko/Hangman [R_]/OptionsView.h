#pragma once
#include "View.h"
#include <string>
#include <vector>

using std::string; using std::vector;

class OptionsView : public View 
{
	void printOptions(int current = 0);
	void printSubOptions(vector<string> vec, int margin, int line, int curr = 0, bool show = true);
	void updateSubObtions(int selected, int currLang, int currLvl);
protected:

	OptionsView(Difficulty lvl);

	vector<string> options;
	vector<string> additions;

	vector<string> language;
	vector<string> difficulty;
	vector<string> info;

	virtual void draw();
	virtual View* handle();
};

class EngOptions : public OptionsView {
public:
	EngOptions(Difficulty level);
};

class UkrOptions : public OptionsView {
public:
	UkrOptions(Difficulty level);
};
