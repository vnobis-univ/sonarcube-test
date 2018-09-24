#include "ViewClasses.h"


string HighScoresView::getSpace() 
{
	int size = translater.getName("Player").length() +
		translater.getName("Score").length();
	size = (68 - size) / 2;
	string space;
	for (int i = 0; i < size; ++i)
	{
		space += " ";
	}
	return space;
}

void HighScoresView::draw()
{
	printerRect(0, 0, 80, 2, Printer(Color::lAqua, Color::dBlue));
	printAtCenter(translater.getName("HIGHSCORES") + "   ", 1, Printer(Color::dWhite, Color::dBlue));

	setCursor(6, 4);
	string str = getSpace();
	Printer(Color::dYellow).print(translater.getName("Player") +
		str + translater.getName("Score"));
		
	int x;
	for (int i = 0; i < 5; ++i)
	{
		x = 6;
		setCursor(x, 7 + i);
		Printer(Color::dWhite).print(saver[i].name); 
		x += str.length() + translater.getName("Player").length(); 
		setCursor(x, 7 + i);
		Printer(Color::dRed).print(to_string(saver[i].scores));
		x += str.length() + translater.getName("Score").length();
		setCursor(x, 7 + i);
		cout << endl;
	
	}
	printerRect(5, 19, 75, 21, Printer(Color::lAqua, Color::dBlue));
	printAtCenter(translater.getName("Press ESC to back"), 20, Printer(Color::lBlack, Color::dBlue));
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