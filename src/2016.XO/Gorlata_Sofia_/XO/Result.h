#pragma once
#include <iostream>
#include <string>
#include "View.h"
#include "Utils.h"
#include "Field.h"

class Result: public View
{
private:
	int currentScore;

public:

	Result(int m_current);

	void Result::draw();
	View* Result::handle();

};