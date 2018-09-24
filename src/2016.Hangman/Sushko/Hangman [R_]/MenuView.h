#pragma once
#include <string>
#include <vector>
#include "View.h"

using std::vector; using std::string;

class MenuView : public View {
	

	void printOptions(int current = 0);
	void printInfo();
protected:
	vector<string> options;
	vector<string> info;

	virtual void draw();
	virtual View* handle();
public:
	MenuView(Difficulty = Difficulty::Normal);
};

class EngMenu : public MenuView {
public:
	EngMenu(Difficulty = Difficulty::Normal);
};

class UkrMenu : public MenuView {
public:
	UkrMenu(Difficulty = Difficulty::Normal);
};

