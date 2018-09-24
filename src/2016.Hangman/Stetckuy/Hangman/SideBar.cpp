#pragma once

#include "SideBar.h"

using namespace std;


SideBar::SideBar(int _life, int _left, int _top, int _width, int _height)
	: life(_life),
	left(_left),
	top(_top),
	width(_width),
	height(_height)
{
	score = 0;
	numOfLetters = 0;
	numOfVictories = 0;

	markUpText.push_back("Life: ");
	markUpText.push_back("Score: ");
	markUpText.push_back("Guessed letters: ");
}

void SideBar::draw()
{
	configure();

	setCursorAt(left/FONT_WIDTH, top/FONT_HEIGHT);

	drawBackground(left, top, width, height, RGB(0,0,100));

	setCursorAt(left / FONT_WIDTH + 1, top / FONT_HEIGHT + 1);

	if (life >= 0) // doesn't print "negative" life
	{
		stats.print(markUpText[0] + string(25 - markUpText[0].size() - toString(life).size(),' ')
																				+ toString(life));
	}
	else
	{
		stats.print(markUpText[0] + string(25 - markUpText[0].size() - toString("0").size(), ' ') 
																				+ toString("0"));
	}

	setCursorAt(left/FONT_WIDTH + 1, top/FONT_HEIGHT + 3);
	stats.print(markUpText[1] + string(25 - markUpText[1].size() - toString(score).size(), ' ')
																			+ toString(score));

	setCursorAt(left / FONT_WIDTH + 1, top / FONT_HEIGHT + 5);
	stats.print(markUpText[2] + string(25 - markUpText[2].size() - toString(numOfLetters).size(), ' ') 
																			+ toString(numOfLetters));
}

View* SideBar::handle()
{
	return nullptr;
}

void SideBar::setLeft(int leftCoord)
{
	left = leftCoord;
}

void SideBar::setTop(int topCoord)
{
	top = topCoord;
}

void SideBar::setWidth(int widthCoord)
{
	width = widthCoord;
}

void SideBar::setHeight(int heightCoord)
{
	height = heightCoord;
}

int SideBar::getLeft() const
{
	return left;
}

int SideBar::getTop() const
{
	return top;
}

int SideBar::getHeight() const
{
	return height;
}

int SideBar::getWidth() const
{
	return width;
}