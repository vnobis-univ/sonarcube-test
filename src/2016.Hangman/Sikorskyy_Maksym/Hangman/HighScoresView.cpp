#include "ViewClasses.h"


string HighScoresView::getSpace() //function defines the distance between "key words", which is needed to allocate them presizely between 20 & 60 x's
{
	int size = transform.getName("Player").length() +
		transform.getName("Score").length() +
		transform.getName("Letters").length() +
		transform.getName("Difficulty").length();
	size = (68 - size) / 4;
	string space;
	for (int i = 0; i < size; ++i)
	{
		space += " ";
	}
	return space;
}

void HighScoresView::draw()
{
	drawFrame();
	printerRect(0, 0, 80, 25, Printer(Color::lAqua, Color::lBlue));
	setCursor(6, 4);
	string str = getSpace();
	Printer(Color::lYellow, Color::lBlue).print(transform.getName("Player") +
		str + transform.getName("Score") +
		str + transform.getName("Letters") +
		str + transform.getName("Difficulty"));
	int x;
	for (int i = 0; i < 5; ++i)
	{
		x = 6;
		setCursor(x, 7 + i);
		Printer(Color::lWhite,Color::lBlue).print(saver[i].name); 
		x += str.length() + transform.getName("Player").length(); 
		setCursor(x, 7 + i);
		Printer(Color::lWhite, Color::lBlue).print(to_string(saver[i].scores));
		x += str.length() + transform.getName("Score").length();
		setCursor(x, 7 + i);
		Printer(Color::lWhite, Color::lBlue).print(to_string(saver[i].letters));
		x += str.length() + transform.getName("Letters").length();
		setCursor(x, 7 + i);
		Printer(Color::lWhite, Color::lBlue).print(diffModes[(int)saver[i].mode]);
		x += str.length() + transform.getName("Difficulty").length();
		setCursor(x, 7 + i);
		
	}
}
View* HighScoresView::handleInput()
{
	View* view = this;
	Button but = getButton(possibleButtons, 1);
	view = new StartView();
	return view;
}

HighScoresView::~HighScoresView()
{
	delete[] possibleButtons;
}