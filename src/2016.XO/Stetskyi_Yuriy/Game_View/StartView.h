#pragma once

class StartView : public View
{

	struct MenuItem
	{
		string text;
		bool chosen;

		MenuItem(string _text= "") :
			text(_text),
			chosen(false)
		{
		}
	};


	Options selectedOption;
	MenuItem menu[3]; // not const (field "bool chosen" is changing)

	void displayMenu();

public:
	StartView() : selectedOption(Options::START)
	{
		menu[0] = MenuItem(" START GAME  ");
		menu[1] = MenuItem(" HIGH SCORES ");
		menu[2] = MenuItem("    EXIT     ");
		menu[0].chosen = true;
	}

	void draw();

	~StartView()
	{
	}
};
