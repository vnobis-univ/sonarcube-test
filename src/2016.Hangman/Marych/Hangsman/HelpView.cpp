#include "Printer.h"
#include "HelpView.h"
#include "Console.h"
#include <conio.h>
#include "ChooseComplexView.h"
#include "FieldView.h"

Printer selectedMenu4(Color::LIGHT_RED, Color::BLACK);
void HelpView::print()
{
	if (language == "Eng")
	{
		printAtCenterOfLine(10, "Please enter CAPS LOCK", defaultPrinter);
		printAtCenterOfLine(12, "Please look at your language at your PC", defaultPrinter);
		printAtCenterOfLine(13, "Language must be ENGLISH", defaultPrinter);
		printAtCenterOfLine(25, "Continue", selectedMenu4);
	}
	else if (language == "Ukr")
	{
		printAtCenterOfLine(10, "������i�� CAPS LOCK", defaultPrinter);
		printAtCenterOfLine(12, "�����i��� ���� ��������� �� ��", defaultPrinter);
		printAtCenterOfLine(13, "��������� ������� ���� �����������", defaultPrinter);
		printAtCenterOfLine(25, "����������", selectedMenu4);
	}
}
void HelpView::draw()
{
	View::draw();
	print();
}

View* HelpView::handle()
{
	View* nextView = this;
	bool choose = false;
	while (!choose)
	{
		switch (_getch())
		{
		case 27:
			nextView = new ChooseComplexView;
			choose = true;
			break;
		case 13:
			nextView = new FieldView;
			choose = true;
			break;
		}
	}
	return nextView;
}
