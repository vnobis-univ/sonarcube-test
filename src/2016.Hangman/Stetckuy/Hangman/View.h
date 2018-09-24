#pragma once

#include <Windows.h> // for COLORREF
#include <vector> // for markUpText
#include <string> // for markUpText
#include "ConsoleProperties.h"  // for getLanguage

using namespace std;

class View
{
protected:
	vector<string> markUpText;
	Language windowLanguage;
public:
	virtual void draw() = 0;
	virtual View* handle() = 0;

	void drawBackground(int, int, int, int, COLORREF);

	Language getLanguage() const;
	void setLanguage(Language);

	void configure();
	void clear();

	virtual ~View() {}
};