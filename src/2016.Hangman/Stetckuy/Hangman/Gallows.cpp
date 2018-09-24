#pragma once

#include "Gallows.h"

using namespace std;

Gallows::Gallows(int _x, int _y, int _width, int _height, string convName, COLORREF _background)
	: left(_x),
	top(_y),
	width(_width),
	height(_height),
	convictName(convName),
	currStep(1),
	backgroundColor(_background)
{
	configure();
	speechBottomRight.X = 0;
	speechBottomRight.Y = 0;
	speechTopLeft.X = 0;
	speechTopLeft.Y = 0;
}

void Gallows::drawElement(int elNumber)
{
	SetDCPenColor(hdc, RGB(255, 255, 255));
	GetClientRect(hwnd, &rect);

	POINT* hand1;
	POINT* hand2;
	POINT* messageCloud;

	switch (elNumber)
	{
	case 1: // Beginning state, when nothing is painted

		break;
	case 2: // only basis is painted
		Rectangle(hdc,left + width/ 10, top + 8 * height/ 10, left + 2 * width / 3, top + 8 * height / 10 + 5);
		break;
	case 3: // vertical stick
		Rectangle(hdc,left + width / 3, top + 8 * height / 10,left + width / 3 + 3,top + height / 10);

		MoveToEx(hdc,left + width / 10 + 5,top + 8 * height / 10, NULL); // drawing left support
		LineTo(hdc,left + width / 3 + 2, top + 6 * height / 10);
		MoveToEx(hdc, left + width / 10 + 8, top + 8 * height / 10, NULL);
		LineTo(hdc, left + width / 3 + 2, top + 6 * height / 10 + 3);

		MoveToEx(hdc, left +  2 * width / 3 - 10, top + 8 * height / 10, NULL); // drawing right support
		LineTo(hdc,left + width / 3 + 2, top + 6 * height / 10);
		MoveToEx(hdc,left + 2 * width / 3 - 13, top + 8 * height / 10, NULL);
		LineTo(hdc, left + width / 3 + 2, top + 6 * height / 10 + 3);
		break;
	case 4: // vertical stick
		Rectangle(hdc, left + width / 3 - 3, top + height / 10 + 2, left + 8 * width / 10, top +height / 10 + 4);
		break;
	case 5: // horizontal stick

		MoveToEx(hdc, left + 8 * width / 10 - 5, top + height / 10, NULL);
		LineTo(hdc, left + 8 * width / 10 - 5, top + height / 4);
		Ellipse(hdc, left + 8 * width / 10 - 10, top + height / 4 - 5, left + 8 * width / 10 + 5, top + height / 4 + 15);

		break;
	case 6: // player + stool
		
		SetDCPenColor(hdc, RGB(200, 200, 0));
		SetDCBrushColor(hdc, RGB(200, 200, 0));

		// face
		Ellipse(hdc, left + 8 * width / 10 - 13, top + height / 4 - 5, left + 8 * width / 10 + 8, top + height / 4 + 20);
		
		SetDCBrushColor(hdc, RGB(0, 0, 0));

		// eyes & mouth
		Ellipse(hdc, left + 8 * width / 10 - 11, top + height / 4 + 6, left + 8 * width / 10 - 5, top + height / 4 + 12);
		Ellipse(hdc, left + 8 * width / 10, top + height / 4 + 6, left + 8 * width / 10 + 6, top + height / 4 + 12);
		
		SetDCPenColor(hdc, RGB(0, 0, 0));
		MoveToEx(hdc, left + 8 * width / 10 - 8, top + height / 4 + 15, NULL);
		LineTo(hdc, left + 8 * width / 10 + 3, top + height / 4 + 15);

		// hat

		SetDCPenColor(hdc, RGB(200, 0, 0));
		SetDCBrushColor(hdc, RGB(200, 0, 0));

		Rectangle(hdc, left + 8 * width / 10 - 16, top + height / 4 + 2, left + 8 * width / 10 + 11, top + height / 4 + 6);
		Rectangle(hdc, left + 8 * width / 10 - 14, top + height / 4 - 8, left + 8 * width / 10 + 9, top +height / 4 + 4);
		
		//body
		SetDCPenColor(hdc, RGB(100, 100, 100));
		SetDCBrushColor(hdc, RGB(0, 200, 0));
		Rectangle(hdc, left + 8 * width / 10 - 15, top + height / 4 + 20, left + 8 * width / 10 + 9, top + height / 4 + 70);

		// hands

		hand1 = new POINT[4]; // left hand

		hand1[0].x = left + 8*width/10 - 15;
		hand1[0].y = top + height/4 + 20;

		hand1[1].x = left + 8 * width / 10 - 15;
		hand1[1].y = top + height/4 + 30;

		hand1[2].x = left + 8 * width / 10 - 30;
		hand1[2].y = top + height / 4 + 45;

		hand1[3].x = left + 8 * width / 10 - 30;
		hand1[3].y = top + height / 4 + 35;

		hand2 = new POINT[4]; // right hand

		hand2[0].x = left + 8*width/10 + 9;
		hand2[0].y = top + height/4 + 20;

		hand2[1].x = left + 8 * width / 10 + 9;
		hand2[1].y = top + height / 4 + 30;

		hand2[2].x = left + 8 * width / 10 + 24;
		hand2[2].y = top + height / 4 + 45;

		hand2[3].x = left + 8 * width / 10 + 24;
		hand2[3].y = top + height / 4 + 35;

		Polygon(hdc, hand1, 4);
		Polygon(hdc, hand2, 4);

		SetDCPenColor(hdc, RGB(200, 200, 0));
		SetDCBrushColor(hdc, RGB(200, 200, 0));

		Ellipse(hdc, left + 8 * width / 10 - 35, top + height / 4 + 35,  // left palm
			left + 8 * width / 10 - 25, top + height / 4 + 45);

		Ellipse(hdc, left + 8 * width / 10 + 19, top + height / 4 + 35, // right palm
			left + 8 * width / 10 + 29, top + height / 4 + 45);

		// legs
		SetDCPenColor(hdc, RGB(0, 100, 100));
		SetDCBrushColor(hdc, RGB(170, 150, 100));
		Rectangle(hdc, left + 8 * width / 10 - 15, top + height / 4 + 70, left + 8 * width / 10 - 7, top + height / 4 + 100);
		Rectangle(hdc, left + 8 * width / 10, top + height / 4 + 70, left + 8 * width / 10 + 8, top + height / 4 + 100);

		// stool
		SetDCPenColor(hdc, RGB(255, 255, 255));
		SetDCBrushColor(hdc, RGB(0, 0, 200));

		Rectangle(hdc, left + 8 * width / 10 - 20, top + height / 4 + 100, left + 8 * width / 10 + 14, top + height / 4 + 104);
		Rectangle(hdc, left + 8 * width / 10 - 19, top + height / 4 + 104, left + 8 * width / 10 - 15, top + 8 * height / 10 + 4);
		Rectangle(hdc, left + 8 * width / 10 + 9, top + height / 4 + 104, left + 8 * width / 10 + 13, top + 8 * height / 10 + 4);
		break;
	case 7: // player + stool + last words
		SetDCPenColor(hdc, RGB(0, 0, 0));
		SetDCBrushColor(hdc, RGB(255, 255, 255));

		messageCloud = new POINT[3];

		messageCloud[0].x = left + width / 2 - 20;
		messageCloud[0].y = top + height / 5 + 15;

		messageCloud[1].x = left + width / 2 - 20;
		messageCloud[1].y = top + height / 5 + 30;

		messageCloud[2].x = left + 8 * width / 10 - 13;
		messageCloud[2].y = top + height/4 + 15;

		Polygon(hdc, messageCloud, 3);

		SetDCBrushColor(hdc, RGB(255, 255, 255));

		setCursorAt((left + width/2)/FONT_WIDTH - 2, (top + height/5)/FONT_HEIGHT);
		speechTopLeft = cursor;
		techData.print("love   ");
		setCursorAt((left + width / 2) / FONT_WIDTH - 2, (top + height / 5) / FONT_HEIGHT + 1);
		techData.print(" 'n'   ");
		setCursorAt((left + width / 2) / FONT_WIDTH - 2, (top + height / 5) / FONT_HEIGHT + 2);
		techData.print("peace! ");
		speechBottomRight = cursor;
		break;
	case 8:  // the end
		SetDCPenColor(hdc, RGB(0, 0, 200));
		SetDCBrushColor(hdc, RGB(0, 0, 200));
		Rectangle(hdc, speechTopLeft.X*FONT_WIDTH - 3, speechTopLeft.Y*FONT_HEIGHT,
			speechBottomRight.X*FONT_WIDTH + 3, speechBottomRight.Y*FONT_HEIGHT + FONT_HEIGHT);
		Rectangle(hdc, left + 8 * width / 10 - 20, top + height / 4 + 100, left + 8 * width / 10 + 14, top + 8 * height / 10 + 4);
		break;
	}
}

void Gallows::makeEmpty()
{
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SelectObject(hdc, GetStockObject(DC_PEN));

	SetDCBrushColor(hdc, backgroundColor);
	SetDCPenColor(hdc, RGB(255, 255, 255));

	GetClientRect(hwnd, &rect);
	Rectangle(hdc, left, top, left + width, top + height);
}

void Gallows::configure()
{

	while (!comments.empty())
	{
		comments.pop_back();
	}

	if (options.getLanguage() == Language::ENGLISH)
	{
		comments.push_back(convictName + " leaves jail");
		comments.push_back(convictName + " is on the last way");
		comments.push_back("The convict arrived");
		comments.push_back("Judge reads verdict");
		comments.push_back(convictName + " is on gallows");
		comments.push_back(convictName + " gives last speech");
		comments.push_back("Poor " + convictName + " :(");
	}
	else
	{
		comments.push_back(convictName + " покидає тюрму");
		comments.push_back(convictName + " на шляху до ...");
		comments.push_back("Засуджений прибув");
		comments.push_back("Суддя зачитує вирок");
		comments.push_back(convictName + " на шибениці");
		comments.push_back(convictName + " має останнє слово");
		comments.push_back("The end :(");
	}
}

void Gallows::setStep(int st)
{
	if (st >= 1)
	{
		currStep = st;
	}
}

void Gallows::draw()
{
			makeEmpty();

			for (int i = 1; i <= currStep; ++i)
			{
				drawElement(i);
			}
	
			if (currStep >= 2)
			{
				setCursorAt(left / FONT_WIDTH + 1, (top + 9 * height / 10) / FONT_HEIGHT);
				menuActive.print(comments[currStep - 2]);
			}
}

void Gallows::setName(string name)
{
	convictName = name;

	configure();
}