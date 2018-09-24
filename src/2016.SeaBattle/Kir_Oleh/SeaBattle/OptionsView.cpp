#include "ViewClasses.h"

int counter2 = 0;

string langs[2] = { "Ukrainian", "English" };


void OptionsView::drawBackground()
{
	if (counter2 == 0)
	{
		setConsoleVisability(false);

		printerRect(5, 0, 75, 2, Printer(Color::lAqua, Color::dBlue));

		printerRect(0, 3, 80, 18, Printer(Color::lAqua, Color::lBlue));

		printerRect(5, 19, 75, 21, Printer(Color::lAqua, Color::dBlue));
		printAtMiddle(translater.getName("Press ESC to back"), 20, Printer(Color::lBlack, Color::dBlue));

		setConsoleVisability(true);

		++counter2;
	}
}

string OptionsView::getSpace(int a)
{
	int qnt = 2;
	int realSize = 4 * qnt;
	for (int i = 0; i < qnt; ++i)
	{
		switch (a)
		{
		case 0:
			realSize += translater.getName(langs[i]).length();
			break;
		case 1:
			realSize += translater.getName(sexes[i]).length();
			break;
		}

	}
	int distance = (50 - realSize) / (qnt - 1);
	string str;
	for (int i = 0; i < distance; ++i)
	{
		str += " ";
	}
	return str;
}

void OptionsView::drawScribbles()
{
	printerRect(30, 1, 50, 1, Printer(Color::lAqua, Color::dBlue));
	printAtMiddle(translater.getName("OPTIONS") + "   ", 1, Printer(Color::lBlack, Color::dBlue));

	printAtMiddle("  " + translater.getName("LANGUAGE  ") + "  ", 8, pGrayBlue);
	setCursor(14, 10);
	for (int i = 0; i < 2; ++i)
	{
		bArr[0][i] == 1 ? Printer(Color::dPurple, Color::lBlue).print("->" + translater.getName(langs[i]) + "<-" + getSpace(0)) :
			Printer(currLang == Language(i) ? Color::lGreen : Color::lWhite, Color::lBlue).print("  " + translater.getName(langs[i]) + "  " + getSpace(0));
	}

	printAtMiddle("  " + translater.getName("SEX   ") + "  ", 14, pGrayBlue);
	setCursor(14, 16);
	for (int i = 0; i < 2; ++i)
	{
		bArr[1][i] == 1 ? Printer(Color::dPurple, Color::lBlue).print("->" + translater.getName(sexes[i]) + "<-" + getSpace(1)) :
			Printer(currSex == Sex(i) ? Color::lGreen : Color::lWhite, Color::lBlue).print("  " + translater.getName(sexes[i]) + "  " + getSpace(1));
	}
	printerRect(20, 20, 60, 20, Printer(Color::lAqua, Color::dBlue));
	printAtMiddle(translater.getName("Press ESC to back"), 20, Printer(Color::lBlack, Color::dBlue));
}

OptionsView::OptionsView()
{
	bArr = new bool*[2];
	bArr[0] = new bool[2];
	for (int i = 0; i < 2; ++i)
	{
		bArr[0][i] = 0;
	}
	bArr[1] = new bool[2];
	for (int i = 0; i < 2; ++i)
	{
		bArr[0][i] = 0;
	}
	bArr[0][0] = 1;
}

void OptionsView::draw()
{
	drawBackground();
	drawScribbles();
}

View* OptionsView::handleInput()
{
	View* view = this;
	int hor = selected.x;
	int ver = selected.y;

	Button but = getButton(possibleButtons, 6);
	switch (but)
	{
	case Button::UP:
		ver--;
		break;
	case Button::DOWN:
		ver++;
		break;
	case Button::RIGHT:
		hor++;
		break;
	case Button::LEFT:
		hor--;
		break;
	case Button::ENTER:
	{
						  if (ver == 0)
						  {
							  currLang = (Language)hor;
						  }
						  if (ver == 1)
						  {
							  currSex = (Sex)hor;
						  }
	}
		break;
	case Button::ESC:
		view = new StartView();
		counter2 = 0;
		break;
	}
	if (ver >= 0 && ver < 2 && ver != selected.y)
	{
		bArr[selected.y][selected.x] = false;
		selected.y = ver;
		selected.x = 0;
		hor = 0;
		bArr[selected.y][selected.x] = true;
	}
	if (hor >= 0 && hor < 2 && hor != selected.x)
	{
		bArr[selected.y][selected.x] = false;
		selected.x = hor;
		bArr[selected.y][selected.x] = true;
	}
	return view;
}

OptionsView::~OptionsView()
{
	delete[] possibleButtons;
	for (int i = 0; i < 2; i++)
	{
		delete[] bArr[i];
	}
}