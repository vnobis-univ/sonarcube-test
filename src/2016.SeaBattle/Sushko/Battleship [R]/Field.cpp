#include <iostream>
#include "Field.h"
#include "ExternUtils.h"
#include "ConsoleUtils.h"
#include "ShipManager.h"
using namespace std;

Cell::Cell(int _x, int _y, CELL_STATE st) : x(_x), y(_y), state(st) {}

CELL_STATE Cell::getState() const{
	return state;
}

void Cell::setState(CELL_STATE st) {
	state = st;
}

void Cell::draw(COORD edge,HPEN pen){

	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);

	MoveToEx(hdc, edge.X + x*cellSize, edge.Y + y*cellSize, NULL);
	LineTo(hdc, edge.X + x*cellSize, edge.Y + y*cellSize + cellSize);
	LineTo(hdc, edge.X + x*cellSize + cellSize, edge.Y + y*cellSize + cellSize);
	LineTo(hdc, edge.X + x*cellSize + cellSize, edge.Y + y*cellSize);
	LineTo(hdc, edge.X + x*cellSize, edge.Y + y*cellSize);
}

void Cell::drawX(COORD edge, HPEN pen) {

	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);

	drawLine({ (short)(edge.X + x*cellSize + 1),(short)(edge.Y + y*cellSize + 1) }, 
			 { (short)edge.X + (short)((x + 1)*cellSize - 1),(short)edge.Y + (short)((y + 1)*cellSize - 1) });
	drawLine({ (short)(edge.X + ((short)x + 1)*cellSize - 1),(short)(edge.Y + y*cellSize + 1) }, 
			 { (short)(edge.X + x*cellSize + 1),(short)(edge.Y + ((short)y + 1)*cellSize - 1) });
}

void Cell::drawDot(COORD edge, HPEN pen)
{
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);

	SetDCBrushColor(hdc, RGB(255, 1, 1));
	SelectObject(hdc, GetStockObject(DC_BRUSH)); 
	
	Ellipse(hdc, (edge.X + x*cellSize) + 9, (edge.Y + y*cellSize) +9,
		edge.X + (x + 1)*cellSize - 9, edge.Y + (y + 1)*cellSize - 9);
}

void Field::drawCells(bool update)
{
	if (!update) {
		for (int i = 0; i < 10;++i)
			for (int j = 0; j < 10; ++j)
				if (field[i][j].getState() == CELL_STATE::EMPTY)
					field[i][j].draw(edge, blue);
	}

	for (int i = 0; i < 10;++i) {
		for (int j = 0; j < 10; ++j) {
			if (field[i][j].getState() == CELL_STATE::SHIP) {
				field[i][j].draw(edge, darkAqua);
			}
		}
	}
}

void Field::drawLatinNumbers()
{
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, whitePen);
	for (int i = 0, j =5; i < 10; i++, j+=24) {
		drawLine({ edge.X - 22, edge.Y + (short)j }, { edge.X - 10, edge.Y + (short)j });
		drawLine({ edge.X - 22, edge.Y + 13 + (short)j }, { edge.X - 10, edge.Y + 13 + (short)j });
	}

	drawLine({ edge.X - 17, edge.Y + 8 }, { edge.X - 17,  edge.Y + 16 });
	drawLine({ edge.X - 19, edge.Y + 32 }, { edge.X - 19,  edge.Y + 40 });
	drawLine({ edge.X - 15, edge.Y + 32 }, { edge.X - 15,  edge.Y + 40 });
	drawLine({ edge.X - 21, edge.Y + 56 }, { edge.X - 21,  edge.Y + 64 });
	drawLine({ edge.X - 17, edge.Y + 56 }, { edge.X - 17,  edge.Y + 64 });
	drawLine({ edge.X - 13, edge.Y + 56 }, { edge.X - 13,  edge.Y + 64 });
	drawLine({ edge.X - 21, edge.Y + 80 }, { edge.X - 21,  edge.Y + 88 });
	drawLine({ edge.X - 19+1, edge.Y + 80 }, { edge.X - 15,  edge.Y + 88 });

	drawLine({ edge.X - 15,  edge.Y + 88 }, { edge.X - 11-1, edge.Y + 79 });
	drawLine({ edge.X - 21+2, edge.Y + 104 }, { edge.X - 17+1,  edge.Y + 112 });
	drawLine({ edge.X - 17+1,  edge.Y + 112 }, { edge.X - 13, edge.Y + 103 });
	drawLine({ edge.X - 12, edge.Y + 128 }, { edge.X - 12,  edge.Y + 136});
	drawLine({ edge.X - 21, edge.Y + 128 }, { edge.X - 18,  edge.Y + 136 });
	drawLine({ edge.X - 18,  edge.Y + 136 }, { edge.X - 15, edge.Y + 127 });
	drawLine({ edge.X - 12, edge.Y + 128+24 }, { edge.X - 12,  edge.Y + 136+24 });
	drawLine({ edge.X - 14, edge.Y + 128 + 24 }, { edge.X - 14,  edge.Y + 136 + 24 });

	drawLine({ edge.X - 21, edge.Y + 128+24 }, { edge.X - 19,  edge.Y + 136+24 });
	drawLine({ edge.X - 19,  edge.Y + 136+24 }, { edge.X - 16, edge.Y + 127+24 });//  /
	drawLine({ edge.X - 24, edge.Y + 173 }, { edge.X - 9, edge.Y + 173 });
	drawLine({ edge.X - 24, edge.Y + 13 + 173 }, { edge.X - 9, edge.Y + 13 + 173 });
	drawLine({ edge.X - 12, edge.Y + 128 + 24*2 }, { edge.X - 12,  edge.Y + 136 + 24*2 });
	drawLine({ edge.X - 14, edge.Y + 128 + 24 * 2 }, { edge.X - 14,  edge.Y + 136 + 24 * 2 });
	drawLine({ edge.X - 16, edge.Y + 128 + 24*2 }, { edge.X - 16,  edge.Y + 136 + 24*2 });
	drawLine({ edge.X - 23, edge.Y + 128 + 24*2 }, { edge.X - 21,  edge.Y + 136 + 24*2 });

	drawLine({ edge.X - 21,  edge.Y + 136 + 24*2 }, { edge.X - 18, edge.Y + 127 + 24*2 });
	drawLine({ edge.X - 24, edge.Y + 173+24 }, { edge.X - 9, edge.Y + 173+24 });
	drawLine({ edge.X - 24, edge.Y + 13 + 173+24 }, { edge.X - 9, edge.Y + 13 + 173+24 });
	drawLine({ edge.X - 12, edge.Y + 128 + 24 * 3 }, { edge.X - 12,  edge.Y + 136 + 24 * 3 });
	drawLine({ edge.X - 22, edge.Y + 104 + 24 * 4 }, { edge.X - 14,  edge.Y + 112 + 24 * 4 });
	drawLine({ edge.X - 15, edge.Y + 104 + 24 * 4 }, { edge.X - 23,  edge.Y + 112 + 24 * 4 });
	drawLine({ edge.X - 20, edge.Y + 104+24*5 }, { edge.X - 12,  edge.Y + 112+24*5 });
	drawLine({ edge.X - 13, edge.Y + 104 + 24 * 5 }, { edge.X - 21,  edge.Y + 112 + 24 * 5 });
}

Field::Field(COORD _topLeftEdge) : edge(_topLeftEdge), ships(vector<Ship>()) {

	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10;++j)
			field[i][j] = Cell(i, j);
}

void Field::draw() {

	drawCells();

 	white.setColor();
	for (char i = 'A'; i < 'A' + 10; i++) {
		cout << i << ' ' << ' ';
	}

	drawLatinNumbers();
}

void Field::deployShips() {

	ShipManager shipDeployer(this);
	shipDeployer.deployShips();
}

