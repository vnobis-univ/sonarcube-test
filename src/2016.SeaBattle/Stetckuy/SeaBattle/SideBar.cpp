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
	numOfCells = 0;

	windowLanguage = Language::ENGLISH;

	markUpText.push_back("Score:");
	markUpText.push_back("Hit cells:");
}

void SideBar::draw()
{
	configure();

	setCursorAt(left/FONT_WIDTH, top/FONT_HEIGHT);

	drawBackground(left, top, width, height, RGB(0,0,100));

	// print score
	setCursorAt(left/FONT_WIDTH + 1, top/FONT_HEIGHT + 1);
	stats.print(markUpText[0] + string(25 - markUpText[0].size() - toString(score).size(), ' ')
																			 + toString(score));

	// print hit cells
	setCursorAt(left / FONT_WIDTH + 1, top / FONT_HEIGHT + 3);

	stats.print(markUpText[1] + string(25 - markUpText[1].size() - toString(numOfCells).size(), ' ')
																			 + toString(numOfCells));
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