#pragma once

#include "Cell.h"

class FieldView : public View
{
	Cell selectedCell;
public:
	FieldView();

	void draw();
};

