#pragma once

#include <Windows.h> // for COLORREF
#include <vector> // for markUpText
#include <string> // for markUpText
#include "ConsoleProperties.h"  // for Language

using namespace std;

class View
{
protected:
	Language windowLanguage;
	vector<string> markUpText;
	vector<MenuItem> menuItems;

	Language getLanguage() const;
	void setLanguage(Language);

	void drawBackground(int, int, int, int, COLORREF);
	void configure();
public:

	virtual void draw() = 0;
	virtual View* handle() = 0;
	void clear();

	virtual ~View() {}
};