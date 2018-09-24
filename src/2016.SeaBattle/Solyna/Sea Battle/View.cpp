#include "View.h"

View::View(Languages _lang, TypeOfGame _type) : lang(_lang), type(_type)
{

	if (lang == Languages::English)
	{
		system("Title Sea Battle");
	}
	else
	{
		system("Title Морський бій");

	}
}

void View::clean()
{
	system("cls");
}
