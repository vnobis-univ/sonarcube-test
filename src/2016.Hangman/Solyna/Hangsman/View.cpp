#include "View.h"


View::View(Languages l, Difficulty d): lang(l), dif(d)
{
	
	if (lang == English)
	{
		system("Title Hang Man");
	}
	else
	{
		system("Title ��������");
		
	}
}

void View::clean()
{
	system("cls");
}
