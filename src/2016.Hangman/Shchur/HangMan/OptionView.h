#pragma once
#include "View.h"
#include "StartView.h"

class OptionView : public View
{
	string firstEn[2] = { "Lokalization", "Complexity" };
	string firstUa[2] = { "���� ����", "���������" };
	string lokalizationEn[2] = { "English", "Ukrainian" };
	string lokalizationUa[2] = { "���������", "���������" };
	string complexityEn[3] = { "Easy", "Medium", "Hard" };
	string complexityUa[3] = { "�����", "�������", "�����" };
	Lokalization language;
	Complexity complexity;
	short positionV;
	short positionH;
public:
	OptionView();
	OptionView(Lokalization, Complexity);
	void draw();
	View* handle();
	void drawMenu(Lokalization);
	Complexity getComplexity();
};