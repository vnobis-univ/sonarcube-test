#pragma once
#include <iostream>
#include <Windows.h>
class View
{
public:
	View();
	void clean() ;
	virtual void draw() = 0;
	virtual View * handle() = 0;
};