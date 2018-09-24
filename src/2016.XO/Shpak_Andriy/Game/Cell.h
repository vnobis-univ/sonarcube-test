#pragma once
#include <string>

enum class cellOptions
{
	empty,
	cross,
	zero
};

class Cell 
{
	cellOptions cellState;

public:	
	Cell();

	std::string* getHowToDrawCell(int) const;

	void setCellState(cellOptions);

	cellOptions getCellState() const;
};