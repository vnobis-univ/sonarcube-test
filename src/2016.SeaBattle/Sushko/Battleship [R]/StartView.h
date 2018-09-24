#pragma once
#include <string>
#include <vector>
#include "View.h"

using std::vector; using std::string;

class StartView : public View 
{
	void printOptions(int current = 0);
	void printInfo();
protected:
	vector<string> options;
	vector<string> info;

	virtual void draw();
	virtual View* handle();
public:
	StartView();
};

class EngStartView : public StartView {
public:
	EngStartView();
};

class UkrStartView : public StartView {
public:
	UkrStartView();
};
