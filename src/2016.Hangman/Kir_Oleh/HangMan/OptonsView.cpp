#include "ViewClasses.h"

int counter2 = 0;

string langs[2] = { "Ukrainian", "English" };
string modes[3] = { "Easy", "Medium", "Hard" };


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
	int qnt = a == 0 ? 3 : 2;
	int realSize = 4 * qnt;
	for (int i = 0; i < qnt; ++i)
	{
		switch (a)
		{
		case 0:
			realSize += translater.getName(modes[i]).length();
			break;
		case 1:
			realSize += translater.getName(langs[i]).length();
			break;
		case 2:
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
	printAtMiddle("  " + translater.getName("DIFFICULTY  ") + "  ", 5, pGrayBlue);
	setCursor(14, 7);
	for (int i = 0; i < 3; ++i)
	{
		bArr[0][i] == 1 ? Printer(Color::dPurple, Color::lBlue).print("->" + translater.getName(modes[i]) + "<-" + getSpace(0)) :
			Printer(currDifficulty.getDifficulty() == DifficultyModes(i) ? Color::lGreen : Color::lWhite, Color::lBlue).print("  " + translater.getName(modes[i]) + "  " + getSpace(0));
	}

	printAtMiddle("  " + translater.getName("LANGUAGE  ") + "  ", 9, pGrayBlue);
	setCursor(14, 11);
	for (int i = 0; i < 2; ++i)
	{
		bArr[1][i] == 1 ? Printer(Color::dPurple, Color::lBlue).print("->" + translater.getName(langs[i]) + "<-" + getSpace(1)) :
			Printer(currLang == Language(i) ? Color::lGreen : Color::lWhite, Color::lBlue).print("  " + translater.getName(langs[i]) + "  " + getSpace(1));
	}

	printAtMiddle("  " + translater.getName("SEX   ") + "  ", 13, pGrayBlue);
	setCursor(14, 15);
	for (int i = 0; i < 2; ++i)
	{
		bArr[2][i] == 1 ? Printer(Color::dPurple, Color::lBlue).print("->" + translater.getName(sexes[i]) + "<-" + getSpace(2)) :
			Printer(currSex == Sex(i) ? Color::lGreen : Color::lWhite, Color::lBlue).print("  " + translater.getName(sexes[i]) + "  " + getSpace(2));
	}
	printerRect(20, 20, 60, 20, Printer(Color::lAqua, Color::dBlue));
	printAtMiddle(translater.getName("Press ESC to back"), 20, Printer(Color::lBlack, Color::dBlue));
}

OptionsView::OptionsView()
{
	bArr = new bool*[3];
	bArr[0] = new bool[3];
	for (int i = 0; i < 3; ++i)
	{
		bArr[0][i] = 0;
	}
	bArr[1] = new bool[2];
	for (int i = 0; i < 2; ++i)
	{
		bArr[0][i] = 0;
	}
	bArr[2] = new bool[2];
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
							  currDifficulty.setDifficulty((DifficultyModes)hor);
							  dict.loadWords();
						  }
						  if (ver == 1)
						  {
							  currLang = (Language)hor;
							  dict.loadWords();
						  }
						  if (ver == 2)
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
	if (ver >= 0 && ver < 3 && ver != selected.y)
	{
		bArr[selected.y][selected.x] = false;
		selected.y = ver/* == 1? 1: 0*/;
		selected.x = 0;
		hor = 0;
		bArr[selected.y][selected.x] = true;
	}
	if (hor >= 0 && hor < 3 && hor != selected.x)
	{
		bArr[selected.y][selected.x] = false;
		switch (ver)
		{
		case 0:
			selected.x = hor;
			break;
		case 1:
			selected.x = hor == 2? 1: hor;
			break;
		case 2:
			selected.x = hor == 2 ? 1 : hor;
			break;
		}
		//selected.x = ver == 0 ? hor: hor == 2? 1: hor;
		bArr[selected.y][selected.x] = true;
	}
	return view;
}

OptionsView::~OptionsView()
{
	delete[] possibleButtons;
	for (int i = 0; i < 3; i++)
	{
		delete[] bArr[i];
	}
}