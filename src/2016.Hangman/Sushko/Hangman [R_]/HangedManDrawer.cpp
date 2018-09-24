#include "HangedManDrawer.h"

HangedManDrawer::HangedManDrawer(const View* _view, HPEN d, HPEN e, int x, int y, double sizeK) :
	view(_view), head(x, y), gallows(x - 95, y + 170), draw(d), erase(e), k(sizeK)
{
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, draw);
	MoveToEx(hdc, x, y, NULL);
	SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
}

void HangedManDrawer::drawHead() {
	Ellipse(hdc, (head.x)*k, (head.y)*k, (head.x + 50)*k, (head.y + 50)*k);
}

void HangedManDrawer::drawEyes() {
	Ellipse(hdc, (head.x + 10)*k, (head.y + 28)*k, (head.x + 23)*k, (head.y + 14)*k);
	Ellipse(hdc, (head.x + 26)*k, (head.y + 28)*k, (head.x + 39)*k, (head.y + 14)*k);
}

void HangedManDrawer::drawSmile() {
	Chord(hdc, (head.x + 38)*k, (head.y + 40)*k, (head.x + 12)*k, (head.y + 5)*k, (head.x + 10)*k, (head.y + 39)*k,
		(head.x + 40)*k, (head.y + 38)*k);
}

void HangedManDrawer::drawBody() {
	MoveToEx(hdc, (head.x + 25)*k, (head.y + 50)*k, NULL);
	LineTo(hdc, (head.x + 25)*k, (head.y + 120)*k);
}
void HangedManDrawer::drawLegs() {
	MoveToEx(hdc, (head.x + 25)*k, (head.y + 120)*k, NULL);
	LineTo(hdc, (head.x - 5)*k, (head.y + 160)*k);
	MoveToEx(hdc, (head.x + 25)*k, (head.y + 120)*k, NULL);
	LineTo(hdc, (head.x + 50)*k, (head.y + 160)*k);
}

void HangedManDrawer::drawHands() {
	MoveToEx(hdc, (head.x + 25)*k, (head.y + 80)*k, NULL);
	LineTo(hdc, (head.x + 80)*k, (head.y + 60)*k);
	MoveToEx(hdc, (head.x + 25)*k, (head.y + 80)*k, NULL);
	LineTo(hdc, (head.x + 80 - 110)*k, (head.y + 60)*k);
}

void HangedManDrawer::drawGallows(int step)
{
	switch (step)
	{
	case 0:
		MoveToEx(hdc, (gallows.x - 10)*k, (gallows.y)*k, NULL);
		LineTo(hdc, (gallows.x + 20)*k, (gallows.y)*k);
		break;
	case 1:
		MoveToEx(hdc, (gallows.x)*k, (gallows.y)*k, NULL);
		LineTo(hdc, (gallows.x)*k, (gallows.y - 200)*k);
		break;
	case 2:
		MoveToEx(hdc, (gallows.x)*k, (gallows.y - 180)*k, NULL);
		LineTo(hdc, (gallows.x + 20)*k, (gallows.y - 200)*k);
		break;
	case 3:
		MoveToEx(hdc, (gallows.x)*k, (gallows.y - 200)*k, NULL);
		LineTo(hdc, (gallows.x + 120)*k, (gallows.y - 200)*k);
		break;
	}
}

void HangedManDrawer::drawByStep(int step) {
	switch (step) {
	case 0: drawHead();
		break;
	case 1: drawEyes();
		break;
	case 2: drawSmile();
		break;
	case 3: drawBody();
		break;
	case 4: drawHands();
		break;
	case 5: drawLegs();
		break;
	case 6: drawGallows(0);
		break;
	case 7: drawGallows(1);
		break;
	case 8: drawGallows(2);
		break;
	case 9: drawGallows(3);
		break;
	}
}

void HangedManDrawer::drawAll() { drawHead(), drawEyes(), drawSmile(), drawBody(), drawHands(), drawLegs(); }

void HangedManDrawer::hang(int time)
{
	for (int i = 0; i < 4; ++i) drawGallows(i);
	MoveToEx(hdc, (gallows.x + 120)*k, (gallows.y - 200)*k, NULL);
	LineTo(hdc, (gallows.x + 120)*k, (gallows.y - 170)*k);
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, erase);
	drawHands(), drawSmile();
	currentPen = (HPEN)SelectObject(hdc, draw);

	MoveToEx(hdc, (head.x + 25)*k, (head.y + 80)*k, NULL);
	LineTo(hdc, (head.x + 70)*k, (head.y + 115)*k);
	MoveToEx(hdc, (head.x + 25)*k, (head.y + 80)*k, NULL);
	LineTo(hdc, (head.x + 90 - 110)*k, (head.y + 115)*k);
	MoveToEx(hdc, (head.x + 15)*k, (head.y + 40)*k, NULL);
	LineTo(hdc, (head.x + 35)*k, (head.y + 40)*k);

	Sleep(time);

	currentPen = (HPEN)SelectObject(hdc, erase);
	Ellipse(hdc, (head.x + 10)*k, (head.y + 28)*k, (head.x + 23)*k, (head.y + 14)*k);
	Ellipse(hdc, (head.x + 26)*k, (head.y + 28)*k, (head.x + 39)*k, (head.y + 14)*k);
	currentPen = (HPEN)SelectObject(hdc, draw);

	MoveToEx(hdc, (head.x + 32)*k, (head.y + 28)*k, NULL);
	LineTo(hdc, (head.x + 42)*k, (head.y + 22)*k);
	MoveToEx(hdc, (head.x + 32)*k, (head.y + 22)*k, NULL);
	LineTo(hdc, (head.x + 42)*k, (head.y + 28)*k);
	MoveToEx(hdc, (head.x + 10)*k, (head.y + 28)*k, NULL);
	LineTo(hdc, (head.x + 20)*k, (head.y + 22)*k);
	MoveToEx(hdc, (head.x + 10)*k, (head.y + 22)*k, NULL);
	LineTo(hdc, (head.x + 20)*k, (head.y + 28)*k);
}
