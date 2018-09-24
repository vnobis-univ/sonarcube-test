#pragma once
#include "functions.h"
#include <conio.h>
#include <Windows.h>

enum class TypeOfGame
{
	Computer,
	Online
};

enum class Languages
{
	English,
	Ukrainian
};

class View
{
protected:
	TypeOfGame type;
	Languages lang;
public:
	View(Languages _lang, TypeOfGame _type);
	virtual void draw() = 0;
	virtual View* handle() = 0;
	void clean();
};


