#include "OpenWindow.h"


void OpenWindow::draw()
{
	SetColor(1, 4);
	printInTheCentre("HANGMAN", 3);
	SetColor(6, 4);
	printInTheCentre("�I�����", 4);
	SetColor(1, 4);
	printInTheCentre("Press any key to continue", 13);
	SetColor(6, 4);
	printInTheCentre("������i�� ���i���� ����i��", 14);
	SetColor(1, 4);
	printInTheCentre("Prepared by Roman Karas, PMi-11", 54);
	SetColor(6, 4);
	printInTheCentre("�i�������� ����� ������, ��i-11", 55);
	SetColor(1, 4);
	printInTheCentre("Teacher: Vitalii Nobis - the best teacher)", 57);
	SetColor(6, 4);
	printInTheCentre("��������: ���i� �i���i� �����i����� - ��������� ��������)", 58);
	if (_getch())
	{
		LanguageMenu menu;
		menu.draw();
	}
}
