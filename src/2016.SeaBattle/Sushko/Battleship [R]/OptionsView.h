#pragma once

#include "View.h"
#include <string>
#include <vector>

using std::string; using std::vector;

class OptionsView : public View {

	void printLangOptions(int margin, int line, int curr = 0);
protected:

	OptionsView();

	vector<string> language;
	vector<string> info;

	virtual void draw();
	virtual View* handle();
};

class EngOptions : public OptionsView {
public:
	EngOptions();
};

class UkrOptions : public OptionsView {
public:
	UkrOptions();
};
