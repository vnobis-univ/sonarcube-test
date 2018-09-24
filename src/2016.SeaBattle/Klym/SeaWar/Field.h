#pragma once
#include "Score.h"

class Field: public Score
{
public:
	int sheeps(int pole[10][10]);
	int ras(int mypole[10][10]);
	int comp(int mypole[10][10], int udar , int ud[2], int hod[1]);
	int player(int pole[10][10],int udar);
	int main();


};