#include "OptionSelector.h"

OptionSelector::OptionSelector(int curr, int _min, int _max):  current(curr), minVal(_min), maxVal(_max) {}

bool OptionSelector::operator ==(const int val) const
{
	return val == current;
}

OptionSelector::operator int()
{
	return current;
}

OptionSelector& OptionSelector::operator++()
{
	++current;
	if (current > maxVal) current = minVal;
	return *this;
}

OptionSelector& OptionSelector::operator--()
{
	--current;
	if (current < minVal) current = maxVal;
	return *this;
}
