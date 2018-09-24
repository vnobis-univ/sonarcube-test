#pragma once
#include <iostream>

class nextOption
{
	std::string* Selector;
	short curI = 0;
	int k = 0;
public:
	nextOption();
	void Selected();
	void draw();
};

