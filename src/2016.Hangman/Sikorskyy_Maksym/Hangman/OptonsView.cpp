#include "ViewClasses.h"

int counter2 = 0;

string langs[2] = { "Ukrainian", "English" };
string difmodes[3] = { "Easy", "Medium", "Hard" };


void OptionsView::drawBackground()
{
	if (counter2 == 0)
	{
		setConsoleVisability(false);
		
		printerRect(0, 0, 80, 25, Printer(Color::lAqua, Color::lBlue));
		printAtCenter(transform.getName("Press ESC to back"), 20, Printer(Color::lBlack, Color::lBlue));

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
			realSize += transform.getName(difmodes[i]).length();
			break;
		case 1:
			realSize += transform.getName(langs[i]).length();
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

void OptionsView::drawSections()
{
	
	
	printAtCenter("  " + transform.getName("DIFFICULTY  ") + "  ", 5, pGrayBlue);
	
	setCursor(14, 7);
	for (int i = 0; i < 3; ++i)
	{
		bArr[0][i] == 1 ? Printer(Color::lYellow, Color::lBlue).print("* " + transform.getName(difmodes[i]) + " *" + getSpace(0)) :
			Printer(currMode == DifficultyModes(i) ? Color::dWhite : Color::lWhite, Color::lBlue).print("  " + transform.getName(difmodes[i]) + "  " + getSpace(0));
	}

	printAtCenter("  " + transform.getName("LANGUAGE  ") + "  ", 9, pGrayBlue);
	setCursor(14, 11);
	for (int i = 0; i < 2; ++i)
	{
		bArr[1][i] == 1 ? Printer(Color::lYellow, Color::lBlue).print("* " + transform.getName(langs[i]) + " *" + getSpace(1)) :
			Printer(currLang == Language(i) ? Color::dWhite : Color::lWhite, Color::lBlue).print("  " + transform.getName(langs[i]) + "  " + getSpace(1));
	}

	setCursor(14, 15);
	printAtCenter(transform.getName("Press ESC to back"), 20, Printer(Color::lBlack, Color::dBlue));
	
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
	drawSections();
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
							  currMode = (DifficultyModes)hor;
							  dict.loadWords();
						  }
						  if (ver == 1)
						  {
							  currLang = (Language)hor;
							  dict.loadWords();
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