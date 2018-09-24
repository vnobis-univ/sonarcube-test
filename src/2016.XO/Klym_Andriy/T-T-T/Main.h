#pragma once
#include <Windows.h>


using namespace std;

class Head
{
protected:
	void Draw();
public:
	void Clean();
	int cur;
	Head();
};