#include "ViewClasses.h"


string HighScoresView::getSpace() //function defines the distance between "key words", which is needed to allocate them presizely between 20 & 60 x's
{
	int size = translater.getName("Player").length() +
		translater.getName("Score").length() +
		translater.getName("Letters").length() +
		translater.getName("Difficulty").length() +
		translater.getName("Sex").length();
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

	setCursor(6, 4);
	string str = getSpace();
	Printer(Color::dGreen).print(translater.getName("Player") +
		str + translater.getName("Score") +
		str + translater.getName("Letters") +
		str + translater.getName("Difficulty") +
		str + translater.getName("Sex"));
	int x;
	for (int i = 0; i < 5; ++i)
	{
		x = 6;
		setCursor(x, 7 + i);
		Printer(Color::dRed).print(saver[i].name); // prints the players' data in accordance to "key word"
		x += str.length() + translater.getName("Player").length(); //the formula calculates the firt coordinate of the next key word
		setCursor(x, 7 + i);
		Printer(Color::dRed).print(to_string(saver[i].scores));
		x += str.length() + translater.getName("Score").length();
		setCursor(x, 7 + i);
		Printer(Color::dRed).print(to_string(saver[i].letters));
		x += str.length() + translater.getName("Letters").length();
		setCursor(x, 7 + i);
		Printer(Color::dRed).print(diffModes[(int)saver[i].mode]);
		x += str.length() + translater.getName("Difficulty").length();
		setCursor(x, 7 + i);
		Printer(Color::dRed).print(sexes[(int)saver[i].sex]);
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