#pragma once
#include "Buttons.h"
#include "Printer.h"
#include "ConsoleTools.h"
#include "SavingWinners.h"
#include "Dictionary.h"
#include "Translating.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <Windows.h>



class View
{
public:
	virtual void draw() = 0;
	virtual View* handleInput() = 0;
	void clear()
	{
		system("cls");

		SelectObject(dc, penBlack);
		SelectObject(dc, brushBlack);

		Rectangle(dc, 0, 0, width, height);
	}
};

enum class SelectedOption{ Start, HighScores, Options, Exit };

class StartView : public View
{
private:
	SelectedOption opt;
	View* getNextView(SelectedOption selectedOption);
	Button* possibleButtons = new Button[3]{
		Button::UP,
		Button::DOWN,
		Button::ENTER
	};
	void drawBackground();
	void drawInscriptions();
public:
	StartView(SelectedOption opt = SelectedOption::Start);
	void draw();
	View* handleInput();
	~StartView();
};


extern string langs[2];
extern string modes[3];

struct Position
{
	int x;
	int y;
	Position() : x(0), y(0){}
};

class OptionsView : public View
{
private:
	Position selected;
	bool** bArr;
	Button* possibleButtons = new Button[6]{
		Button::UP,
		Button::DOWN,
		Button::LEFT,
		Button::RIGHT,
		Button::ESC,
		Button::ENTER
	};
	void drawBackground();
	string getSpace(int a);
	void drawSections();
public:
	OptionsView();
	void draw();
	View* handleInput();
	~OptionsView();
};

class ResultView : public View
{
	int scores;
	int letters;
	bool isHigh;
public:
	ResultView(int scores, int letters);
	void draw();
	View* handleInput();
};


class HighScoresView: public View
{
private:
	Button* possibleButtons = new Button[1]{
		Button::ESC
	};
	string getSpace();
public:
	void draw();
	View* handleInput();
	~HighScoresView();
};


