#include "HightScoresView.h"

istream & operator>>(istream & is, hightScore & obj)
{
	return is >> obj.name >> obj.score;
}
