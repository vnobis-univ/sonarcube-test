#pragma once

struct OptionSelector
{
	int current;
	int maxVal;
	int minVal;

	OptionSelector(int curr, int _min, int _max);
	bool operator ==(const int) const;
	operator int();

	OptionSelector& operator++();
	OptionSelector& operator--();
};
