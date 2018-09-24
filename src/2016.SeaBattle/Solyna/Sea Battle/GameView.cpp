#include "GameView.h"

#include "ResultView.h"
int score = 0;

View * GameView::nextView()
{
	return nullptr;
}

void GameView::drawPreviousShips()
{
	for (int i = 0; i < numberOfSelectedShip; ++i)
	{
		arrayOfShips[i].draw(arrayOfShips[i].getCoordinateX(), arrayOfShips[i].getCoordinateY());
	}
}

void GameView::nearOrMiss(Field & field, int startOfField, CellStatus stat)


{
	for (int i = 0; i < selectedShip.getSize(); ++i)
	{
		if (selectedShip.getOrientation() == Orientation::Horizontal)
		{
			field.getCell((selectedShip.getCoordinateX() + i * sizeOfCell -startOfField) / sizeOfCell, ((selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell)).setStatus(CellStatus::HasShip);
			if (selectedShip.getCoordinateX() ==startOfField && selectedShip.getCoordinateY() == startOfFieldsY)
			{
				field.getCell((selectedShip.getCoordinateX() + i* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(stat);
				field.getCell((selectedShip.getCoordinateX() + (selectedShip.getSize() /*+ 1*/)* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(stat);
				field.getCell((selectedShip.getCoordinateX() + (selectedShip.getSize()/* + 1*/)* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(stat);
			}
			else
				if (selectedShip.getCoordinateX() ==startOfField + sizeOfCell* sizeOfField - sizeOfCell * selectedShip.getSize() && selectedShip.getCoordinateY() == startOfFieldsY)
				{
					field.getCell((selectedShip.getCoordinateX() + i* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(stat);
					field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(stat);
					field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(stat);
				}
				else
					if (selectedShip.getCoordinateX() ==startOfField  && selectedShip.getCoordinateY() == startOfFieldsY + sizeOfCell*(sizeOfField - 1))
					{
						field.getCell((selectedShip.getCoordinateX() + i* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
						field.getCell((selectedShip.getCoordinateX() + sizeOfCell * selectedShip.getSize() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(stat);
						field.getCell((selectedShip.getCoordinateX() + sizeOfCell * selectedShip.getSize() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);

					}
					else
						if (selectedShip.getCoordinateX() ==startOfField + sizeOfCell* sizeOfField - sizeOfCell * selectedShip.getSize() && selectedShip.getCoordinateY() == startOfFieldsY + sizeOfCell*(sizeOfField - 1))
						{
							field.getCell((selectedShip.getCoordinateX() + i* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
							field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(stat);
							field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
						}
						else
							if (selectedShip.getCoordinateX() ==startOfField)
							{
								field.getCell((selectedShip.getCoordinateX() + i* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
								field.getCell((selectedShip.getCoordinateX() + i* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(stat);
								field.getCell((selectedShip.getCoordinateX() + (selectedShip.getSize())* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(stat);
								field.getCell((selectedShip.getCoordinateX() + (selectedShip.getSize())* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(stat);
								field.getCell((selectedShip.getCoordinateX() + (selectedShip.getSize())* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
							}
							else
								if (selectedShip.getCoordinateX() ==startOfField + sizeOfCell* sizeOfField - sizeOfCell * selectedShip.getSize())
								{
									field.getCell((selectedShip.getCoordinateX() + i* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
									field.getCell((selectedShip.getCoordinateX() + i* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(stat);
									field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(stat);
									field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(stat);
									field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);

								}
								else
									if (selectedShip.getCoordinateY() == startOfFieldsY)
									{
										field.getCell((selectedShip.getCoordinateX() + i* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(stat);
										field.getCell((selectedShip.getCoordinateX() + (selectedShip.getSize())* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(stat);
										field.getCell((selectedShip.getCoordinateX() + (selectedShip.getSize())* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(stat);
										field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(stat);
										field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(stat);
									}
									else
										if (selectedShip.getCoordinateY() == startOfFieldsY + sizeOfCell*(sizeOfField - 1))
										{
											field.getCell((selectedShip.getCoordinateX() + i* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() + sizeOfCell * selectedShip.getSize() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() + sizeOfCell * selectedShip.getSize() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
										}
										else
										{
											field.getCell((selectedShip.getCoordinateX() + i* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() + i* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() + (selectedShip.getSize())* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() + (selectedShip.getSize())* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() + (selectedShip.getSize())* sizeOfCell -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
										}
		}
		else
		{
			field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell, ((selectedShip.getCoordinateY() + i * sizeOfCell - startOfFieldsY) / sizeOfCell)).setStatus(CellStatus::HasShip);
			if (selectedShip.getCoordinateX() ==startOfField && selectedShip.getCoordinateY() == startOfFieldsY)
			{
				field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell + 1, (selectedShip.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
				field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() + (selectedShip.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
				field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell + 1, (selectedShip.getCoordinateY() + (selectedShip.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
			}
			else
				if (selectedShip.getCoordinateX() ==startOfField + sizeOfCell* (sizeOfField - 1) && selectedShip.getCoordinateY() == startOfFieldsY)
				{
					field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
					field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() + (selectedShip.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
					field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() + (selectedShip.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
				}
				else
					if (selectedShip.getCoordinateX() ==startOfField  && selectedShip.getCoordinateY() == startOfFieldsY + sizeOfCell* sizeOfField - selectedShip.getSize()* sizeOfCell)
					{
						field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell + 1, (selectedShip.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
						field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
						field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell + 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
					}
					else
						if (selectedShip.getCoordinateX() ==startOfField + sizeOfCell* (sizeOfField - 1) && selectedShip.getCoordinateY() == startOfFieldsY + sizeOfCell* sizeOfField - selectedShip.getSize()* sizeOfCell)
						{
							field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
							field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
							field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
						}
						else
							if (selectedShip.getCoordinateX() ==startOfField)
							{
								field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell + 1, (selectedShip.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
								field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() + (selectedShip.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
								field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell + 1, (selectedShip.getCoordinateY() + (selectedShip.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
								field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
								field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell + 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
							}
							else
								if (selectedShip.getCoordinateX() ==startOfField + sizeOfCell* (sizeOfField - 1))
								{
									field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
									field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() + (selectedShip.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
									field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() + (selectedShip.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
									field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
									field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
								}
								else
									if (selectedShip.getCoordinateY() == startOfFieldsY)
									{
										field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell + 1, (selectedShip.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
										field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() + (selectedShip.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
										field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell + 1, (selectedShip.getCoordinateY() + (selectedShip.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
										field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
										field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() + (selectedShip.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
									}
									else
										if (selectedShip.getCoordinateY() == startOfFieldsY + sizeOfCell* sizeOfField - selectedShip.getSize()* sizeOfCell)
										{
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell + 1, (selectedShip.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell + 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
										}
										else
										{
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell + 1, (selectedShip.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell + 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell + 1, (selectedShip.getCoordinateY() + (selectedShip.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell, (selectedShip.getCoordinateY() + (selectedShip.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
											field.getCell((selectedShip.getCoordinateX() -startOfField) / sizeOfCell - 1, (selectedShip.getCoordinateY() + (selectedShip.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(stat);
										}
		}
	}
}

void GameView::oponentField()
{
	srand(time(NULL));
	for (int i = 0; i < sizeOfField; ++i)
	{
		selectedShip = arrayOfOponentsShips[i];
		Orientation orient = Orientation(rand() % 2);
		if (orient == Orientation::Horizontal)
		{
			int ii = rand() % (sizeOfField - arrayOfOponentsShips[i].getSize());
			int jj = rand() % sizeOfField;
			bool success = true;
			int iii = ii;
			for (int j = 0; j < arrayOfOponentsShips[i].getSize(); ++j)
			{
				if(oponentsField.getCell(iii, jj).getStatus() != CellStatus :: Empty)
				{
					success = false;
					break;
				}
				else
				{
					++iii;
				}
			}
			if (success)
			{
				selectedShip.setOrientation(orient);
				selectedShip.setCoordinateX(startOfOponentsFieldX + ii*sizeOfCell);
				selectedShip.setCoordinateY(startOfFieldsY + jj*sizeOfCell);
				arrayOfOponentsShips[i] = selectedShip;
				nearOrMiss(oponentsField, startOfOponentsFieldX, CellStatus::NearShip);
			}
			else
			{
				i = i - 1;
			}
		}
		else
		{
			int ii = rand() % sizeOfField;
			int jj = rand() % (sizeOfField - arrayOfOponentsShips[i].getSize());
			bool success = true;
			int jjj = jj;
			for (int j = 0; j < arrayOfOponentsShips[i].getSize(); ++j)
			{
				if (oponentsField.getCell(ii, jjj).getStatus() != CellStatus::Empty)
				{
					success = false;
					break;
				}
				else
				{
					++jjj;
				}
			}
			if (success)
			{
				selectedShip.setOrientation(orient);
				selectedShip.setCoordinateX(startOfOponentsFieldX + ii*sizeOfCell);
				selectedShip.setCoordinateY(startOfFieldsY + jj*sizeOfCell);
				arrayOfOponentsShips[i] = selectedShip;
				nearOrMiss(oponentsField, startOfOponentsFieldX, CellStatus::NearShip);
			}
			else
			{
				i = i - 1;
			}
		}
		
	}
}

void GameView::drawCross(int x, int y)
{
	HDC hdc = GetDC(GetConsoleWindow());
	HPEN Pen(CreatePen(PS_SOLID, 2, RGB(204, 0, 0)));
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, Pen);
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + sizeOfCell, y + sizeOfCell);
	MoveToEx(hdc, x + sizeOfCell, y, NULL);
	LineTo(hdc, x, y + sizeOfCell);
}

void GameView::drawDot(int x, int y)
{
	HDC hdc = GetDC(GetConsoleWindow());
	HPEN Pen(CreatePen(PS_SOLID, 6, RGB(0, 0, 204)));
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, Pen);
	MoveToEx(hdc, x + sizeOfCell/2, y + sizeOfCell/2, NULL);
	LineTo(hdc, x + sizeOfCell / 2 , y + sizeOfCell/ 2);

}

void GameView::drawOponentsShips()
{
	for (int i = 0; i < sizeOfField; ++i)
	{
		if (arrayOfOponentsShips[i].getVisibility() == Visibility::Visible)
		{
			arrayOfOponentsShips[i].draw(arrayOfOponentsShips[i].getCoordinateX(), arrayOfOponentsShips[i].getCoordinateY());
		}
	}
}

void GameView::killingTheShip()
{
	drawCross(placeOfSelectedCellX, placeOfSelectedCellY);
	oponentsField.getCell((placeOfSelectedCellX - startOfOponentsFieldX) / sizeOfCell, (placeOfSelectedCellY - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Hit);
	bool out = false;
	int numberOfShip = 0;
	for (int i = 0; i < sizeOfField; ++i)
	{
		if (out)
		{
			break;
		}

		for (int k = 0; k < arrayOfOponentsShips[i].getSize(); ++k)
		{
			if (arrayOfOponentsShips[i].getOrientation() == Orientation::Horizontal)
			{
				if (arrayOfOponentsShips[i].getCoordinateX() + sizeOfCell * k == placeOfSelectedCellX &&
					arrayOfOponentsShips[i].getCoordinateY() == placeOfSelectedCellY)
				{
					arrayOfOponentsShips[i].getCell(k).setStatus(CellStatus::Hit);
					out = true;
					numberOfShip = i;
					break;
				}
				if (out)
				{
					break;
				}
			}
			else
			{
				if (arrayOfOponentsShips[i].getCoordinateY() + sizeOfCell * k == placeOfSelectedCellY &&
					arrayOfOponentsShips[i].getCoordinateX() == placeOfSelectedCellX)
				{
					arrayOfOponentsShips[i].getCell(k).setStatus(CellStatus::Hit);
					out = true;
					numberOfShip = i;
					break;
				}
				if (out)
				{
					break;
				}
			}
		}
		if (out)
		{
			break;
		}
	}
	bool success = true;
	for (int i = 0; i < arrayOfOponentsShips[numberOfShip].getSize(); ++i)
	{
		if (arrayOfOponentsShips[numberOfShip].getCell(i).getStatus() != CellStatus::Hit)
		{
			success = false;
			break;
		}
	}
	if (success)
	{
		arrayOfOponentsShips[numberOfShip].setVisibility(Visibility::Visible);
		arrayOfOponentsShips[numberOfShip].changeColor();
		drowMissed(arrayOfOponentsShips[numberOfShip], oponentsField, startOfOponentsFieldX);
		drawOponentsShips();
	}
}

void GameView::myShipsKilling(int &x, int & y)
{
	drawCross(startOfMyfieldX + sizeOfCell* x, startOfFieldsY + sizeOfCell*y);
	x = rand() % sizeOfField;
	y = rand() % sizeOfField;
	myField.getCell(x, y).setStatus(CellStatus::Hit);
	bool out = false;
	int numberOfShip = 0;
	for (int i = 0; i < sizeOfField; ++i)
	{
		if (out)
		{
			break;
		}

		for (int k = 0; k < arrayOfShips[i].getSize(); ++k)
		{
			if (arrayOfShips[i].getOrientation() == Orientation::Horizontal)
			{
				if (arrayOfShips[i].getCoordinateX() + sizeOfCell * k == x &&
					arrayOfShips[i].getCoordinateY() == y)
				{
					arrayOfShips[i].getCell(k).setStatus(CellStatus::Hit);
					out = true;
					numberOfShip = i;
					break;
				}
				if (out)
				{
					break;
				}
			}
			else
			{
				if (arrayOfShips[i].getCoordinateY() + sizeOfCell * k == y &&
					arrayOfShips[i].getCoordinateX() == x)
				{
					arrayOfShips[i].getCell(k).setStatus(CellStatus::Hit);
					out = true;
					numberOfShip = i;
					break;
				}
				if (out)
				{
					break;
				}
			}
		}
		if (out)
		{
			break;
		}
	}
	bool success = true;
	for (int i = 0; i < arrayOfShips[numberOfShip].getSize(); ++i)
	{
		if (arrayOfShips[numberOfShip].getCell(i).getStatus() != CellStatus::Hit)
		{
			success = false;
			break;
		}
	}
	if (success)
	{
		arrayOfShips[numberOfShip].setStatus(ShipStatus::Killed);
		drowMissed(arrayOfShips[numberOfShip], myField, startOfMyfieldX);
	}
}

void GameView::drowMissed(Ship ship, Field & field , int startOfField)
{
	for (int i = 0; i < ship.getSize(); ++i)
	{
		if (ship.getOrientation() == Orientation::Horizontal)
		{
			if (ship.getCoordinateX() == startOfField && ship.getCoordinateY() == startOfFieldsY)
			{
				field.getCell((ship.getCoordinateX() + i* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(CellStatus::Missed);
				field.getCell((ship.getCoordinateX() + (ship.getSize() /*+ 1*/)* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
				field.getCell((ship.getCoordinateX() + (ship.getSize()/* + 1*/)* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(CellStatus::Missed);
			}
			else
				if (ship.getCoordinateX() == startOfField + sizeOfCell* sizeOfField - sizeOfCell * ship.getSize() && ship.getCoordinateY() == startOfFieldsY)
				{
					field.getCell((ship.getCoordinateX() + i* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(CellStatus::Missed);
					field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
					field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(CellStatus::Missed);
				}
				else
					if (ship.getCoordinateX() == startOfField  && ship.getCoordinateY() == startOfFieldsY + sizeOfCell*(sizeOfField - 1))
					{
						field.getCell((ship.getCoordinateX() + i* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
						field.getCell((ship.getCoordinateX() + sizeOfCell * ship.getSize() - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
						field.getCell((ship.getCoordinateX() + sizeOfCell * ship.getSize() - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);

					}
					else
						if (ship.getCoordinateX() == startOfField + sizeOfCell* sizeOfField - sizeOfCell * ship.getSize() && ship.getCoordinateY() == startOfFieldsY + sizeOfCell*(sizeOfField - 1))
						{
							field.getCell((ship.getCoordinateX() + i* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
							field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
							field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
						}
						else
							if (ship.getCoordinateX() == startOfField)
							{
								field.getCell((ship.getCoordinateX() + i* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
								field.getCell((ship.getCoordinateX() + i* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(CellStatus::Missed);
								field.getCell((ship.getCoordinateX() + (ship.getSize())* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
								field.getCell((ship.getCoordinateX() + (ship.getSize())* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(CellStatus::Missed);
								field.getCell((ship.getCoordinateX() + (ship.getSize())* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
							}
							else
								if (ship.getCoordinateX() == startOfField + sizeOfCell* sizeOfField - sizeOfCell * ship.getSize())
								{
									field.getCell((ship.getCoordinateX() + i* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
									field.getCell((ship.getCoordinateX() + i* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(CellStatus::Missed);
									field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
									field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(CellStatus::Missed);
									field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);

								}
								else
									if (ship.getCoordinateY() == startOfFieldsY)
									{
										field.getCell((ship.getCoordinateX() + i* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(CellStatus::Missed);
										field.getCell((ship.getCoordinateX() + (ship.getSize())* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
										field.getCell((ship.getCoordinateX() + (ship.getSize())* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(CellStatus::Missed);
										field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
										field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(CellStatus::Missed);
									}
									else
										if (ship.getCoordinateY() == startOfFieldsY + sizeOfCell*(sizeOfField - 1))
										{
											field.getCell((ship.getCoordinateX() + i* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() + sizeOfCell * ship.getSize() - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() + sizeOfCell * ship.getSize() - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
										}
										else
										{
											field.getCell((ship.getCoordinateX() + i* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() + i* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() + (ship.getSize())* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() + (ship.getSize())* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() + (ship.getSize())* sizeOfCell - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell + 1).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
										}
		}
		else
		{
			if (ship.getCoordinateX() == startOfField && ship.getCoordinateY() == startOfFieldsY)
			{
				field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell + 1, (ship.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
				field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell, (ship.getCoordinateY() + (ship.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
				field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell + 1, (ship.getCoordinateY() + (ship.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
			}
			else
				if (ship.getCoordinateX() == startOfField + sizeOfCell* (sizeOfField - 1) && ship.getCoordinateY() == startOfFieldsY)
				{
					field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
					field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell, (ship.getCoordinateY() + (ship.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
					field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() + (ship.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
				}
				else
					if (ship.getCoordinateX() == startOfField  && ship.getCoordinateY() == startOfFieldsY + sizeOfCell* sizeOfField - ship.getSize()* sizeOfCell)
					{
						field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell + 1, (ship.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
						field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
						field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell + 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
					}
					else
						if (ship.getCoordinateX() == startOfField + sizeOfCell* (sizeOfField - 1) && ship.getCoordinateY() == startOfFieldsY + sizeOfCell* sizeOfField - ship.getSize()* sizeOfCell)
						{
							field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
							field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
							field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
						}
						else
							if (ship.getCoordinateX() == startOfField)
							{
								field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell + 1, (ship.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
								field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell, (ship.getCoordinateY() + (ship.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
								field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell + 1, (ship.getCoordinateY() + (ship.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
								field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
								field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell + 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
							}
							else
								if (ship.getCoordinateX() == startOfField + sizeOfCell* (sizeOfField - 1))
								{
									field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
									field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell, (ship.getCoordinateY() + (ship.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
									field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() + (ship.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
									field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
									field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
								}
								else
									if (ship.getCoordinateY() == startOfFieldsY)
									{
										field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell + 1, (ship.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
										field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell, (ship.getCoordinateY() + (ship.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
										field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell + 1, (ship.getCoordinateY() + (ship.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
										field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
										field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell, (ship.getCoordinateY() + (ship.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
									}
									else
										if (ship.getCoordinateY() == startOfFieldsY + sizeOfCell* sizeOfField - ship.getSize()* sizeOfCell)
										{
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell + 1, (ship.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell + 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
										}
										else
										{
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell + 1, (ship.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell + 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() + i* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() - startOfFieldsY) / sizeOfCell - 1).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell + 1, (ship.getCoordinateY() + (ship.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell, (ship.getCoordinateY() + (ship.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
											field.getCell((ship.getCoordinateX() - startOfField) / sizeOfCell - 1, (ship.getCoordinateY() + (ship.getSize())* sizeOfCell - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
										}
		}
	}
}

bool GameView::myWIn()
{
	for (int i = 0; i < sizeOfField; ++i)
	{
		if (arrayOfOponentsShips[i].getVisibility() == Visibility::Invisible)
		{
			return false;
		}
	}
	return true;
}

bool GameView::oponentsWIn()
{
	for (int i = 0; i < sizeOfField; ++i)
	{
		if (arrayOfShips[i].getStatus() == ShipStatus::NotKilled)
		{
			return false;
		}
	}
	return true;
}

GameView::GameView(Languages _lang, TypeOfGame _type) :
	View(_lang, _type),
	myField(),
	oponentsField(),
	numberOfSelectedShip(0),
	placeOfSelectedCellX(startOfOponentsFieldX),
	placeOfSelectedCellY(startOfFieldsY)
{

	arrayOfShips[0] = Ship(4, Visibility::Visible, 216, 191, 216);
	arrayOfOponentsShips[0] = Ship(4, Visibility::Invisible, 216, 191, 216);
	for (int i = 1; i < 3; ++i)
	{
		arrayOfShips[i] = Ship(3, Visibility::Visible, 216, 191, 216);
		arrayOfOponentsShips[i] = Ship(3, Visibility::Invisible, 216, 191, 216);
	}
	for (int i = 3; i < 6; ++i)
	{
		arrayOfShips[i] = Ship(2, Visibility::Visible, 216, 191, 216);
		arrayOfOponentsShips[i] = Ship(2, Visibility::Invisible, 216, 191, 216);
	}
	for (int i = 6; i < sizeOfField;++i)
	{
		arrayOfShips[i] = Ship(1, Visibility::Visible, 216, 191, 216);
		arrayOfOponentsShips[i] = Ship(1, Visibility::Invisible, 216, 191, 216);
	}
	selectedShip = arrayOfShips[0];
	oponentsShip = arrayOfOponentsShips[0];
	selectedShip.setCoordinateX(startOfMyfieldX);
	selectedShip.setCoordinateY(startOfFieldsY);
	selectedCell = oponentsField.getCell(0, 0);
}

void GameView::draw()
{
	clean();
	myField.draw(startOfMyfieldX, startOfFieldsY);
	selectedShip.draw(selectedShip.getCoordinateX(),selectedShip.getCoordinateY());
	oponentsField.draw(startOfOponentsFieldX, startOfFieldsY);
	if (lang == Languages::English)
	{
		Printer p(mainTextColor, mainBackgroundColor);
		Printer p1(textColor, mainBackgroundColor);
		printAtCenterOfLine(2, "Enjoy your game :)", p, consoleWidth);
		printAtCenterOfLine(4, "Score ", p1, consoleWidth);
		cout << score;
		setCursoreAtPosition(15, 5);
		p.print("Your field");
		setCursoreAtPosition(52, 5);
		p.print("Oponent's field");
		printAtCenterOfLine(28, "Press SPACE to turn the ship", p1, consoleWidth);
	}
	else
	{
		Printer p(mainTextColor, mainBackgroundColor);
		Printer p1(textColor, mainBackgroundColor);
		printAtCenterOfLine(2, "Приємної гри :)", p, consoleWidth);
		printAtCenterOfLine(4, "Paхунок ", p1, consoleWidth);
		cout << score;
		setCursoreAtPosition(16, 5);
		p.print("Твоє поле");
		setCursoreAtPosition(53, 5);
		p.print("Поле суперника");
		printAtCenterOfLine(28, "Натисніть SPACE, щоб перевернути кораблик", p1, consoleWidth);
	}
}

View * GameView::handle()
{
	//int key = _getch();
	while (true)
	{
		int key = _getch();
		if (key == 224)//if arrow key was pre+ssed
		{
			key = _getch();
		}
		switch (key)
		{
		case(72): // up
		{
			if (selectedShip.getCoordinateY() != startOfFieldsY)
			{
				selectedShip.backToColor();
				selectedShip.draw(selectedShip.getCoordinateX(), selectedShip.getCoordinateY());
				selectedShip.setCoordinateY(selectedShip.getCoordinateY() - sizeOfCell);
				selectedShip.toMainColor();
				drawPreviousShips();
				selectedShip.draw(selectedShip.getCoordinateX(), selectedShip.getCoordinateY());
			}
		}
		break;
		case(80): // down
		{
			if (selectedShip.getOrientation() == Orientation::Horizontal)
			{
				if (selectedShip.getCoordinateY() != startOfFieldsY + sizeOfCell *(sizeOfField-1))
				{
					selectedShip.backToColor();
					selectedShip.draw(selectedShip.getCoordinateX(), selectedShip.getCoordinateY());
					selectedShip.setCoordinateY(selectedShip.getCoordinateY() + sizeOfCell);
					selectedShip.toMainColor();
					drawPreviousShips();
					selectedShip.draw(selectedShip.getCoordinateX(), selectedShip.getCoordinateY());
				}
			}
			else
			{
				if (selectedShip.getCoordinateY() != startOfFieldsY + sizeOfCell *sizeOfField - selectedShip.getSize() * sizeOfCell)
				{
					selectedShip.backToColor();
					selectedShip.draw(selectedShip.getCoordinateX(), selectedShip.getCoordinateY());
					selectedShip.setCoordinateY(selectedShip.getCoordinateY() + sizeOfCell);
					selectedShip.toMainColor();
					drawPreviousShips();
					selectedShip.draw(selectedShip.getCoordinateX(), selectedShip.getCoordinateY());
				}
			}
		}
		break;
		case(75): //left
		{
			if (selectedShip.getCoordinateX() != startOfMyfieldX)
			{
				selectedShip.backToColor();
				selectedShip.draw(selectedShip.getCoordinateX(), selectedShip.getCoordinateY());
				selectedShip.setCoordinateX(selectedShip.getCoordinateX() - sizeOfCell);
				selectedShip.toMainColor();
				drawPreviousShips();
				selectedShip.draw(selectedShip.getCoordinateX(), selectedShip.getCoordinateY());
			}
		}
		break;
		case(77): // right
		{
			if (selectedShip.getOrientation() == Orientation::Vertical)
			{
				if (selectedShip.getCoordinateX() != startOfMyfieldX + sizeOfCell *(sizeOfField - 1))
				{
					selectedShip.backToColor();
					selectedShip.draw(selectedShip.getCoordinateX(), selectedShip.getCoordinateY());
					selectedShip.setCoordinateX(selectedShip.getCoordinateX() + sizeOfCell);
					selectedShip.toMainColor();
					drawPreviousShips();
					selectedShip.draw(selectedShip.getCoordinateX(), selectedShip.getCoordinateY());
				}
			}
			else
			{
				if (selectedShip.getCoordinateX() != startOfMyfieldX + sizeOfCell *sizeOfField - selectedShip.getSize() * sizeOfCell)
				{

					selectedShip.backToColor();
					selectedShip.draw(selectedShip.getCoordinateX(), selectedShip.getCoordinateY());
					selectedShip.setCoordinateX(selectedShip.getCoordinateX() + sizeOfCell);
					selectedShip.toMainColor();
					drawPreviousShips();
					selectedShip.draw(selectedShip.getCoordinateX(), selectedShip.getCoordinateY());
				}
			}
		}
		break;
		case(32): //space
		{
			selectedShip.backToColor();
			selectedShip.draw(selectedShip.getCoordinateX(), selectedShip.getCoordinateY());
			selectedShip.turning();
			selectedShip.toMainColor();
			drawPreviousShips();
			selectedShip.draw(selectedShip.getCoordinateX(), selectedShip.getCoordinateY());
		}
		break;
		case(13): // enter
		{
			bool success = true;
			for (int i = 0; i < selectedShip.getSize(); ++i)
			{
				if (selectedShip.getOrientation() == Orientation::Horizontal)
				{
					if (myField.getCell((selectedShip.getCoordinateX() + i * sizeOfCell - startOfMyfieldX) / sizeOfCell, ((selectedShip.getCoordinateY() - startOfFieldsY) / sizeOfCell)).getStatus() != CellStatus::Empty)
					{
						success = false;
						break;
					}
				}
				else
				{
					if (myField.getCell((selectedShip.getCoordinateX() - startOfMyfieldX) / sizeOfCell, ((selectedShip.getCoordinateY() + i * sizeOfCell - startOfFieldsY) / sizeOfCell)).getStatus() != CellStatus::Empty)
					{
						success = false;
						break;
					}
				}
			}
			if (success)
			{
				nearOrMiss(myField, startOfMyfieldX, CellStatus::NearShip);
				selectedShip.changeColor();
				arrayOfShips[numberOfSelectedShip] = selectedShip;
				++numberOfSelectedShip;
				if (numberOfSelectedShip == 10)
				{
					drawPreviousShips();
					oponentField();
					selectedCell.changeColor();
					selectedCell.drawCell(startOfOponentsFieldX, startOfFieldsY);
				}
				else
				{
					selectedShip = arrayOfShips[numberOfSelectedShip];
					drawPreviousShips();
					selectedShip.setCoordinateX(startOfMyfieldX);
					selectedShip.setCoordinateY(startOfFieldsY);
					selectedShip.draw(startOfMyfieldX, startOfFieldsY);
				}
			}
		}
		break;
		}
		if (numberOfSelectedShip == 10)
		{
			Printer p(textColor, mainBackgroundColor);
			if (lang == Languages::English)
			{
				printAtCenterOfLine(28, "   Choose the cell of oponent's field and press ENTER   ", p, consoleWidth);
			}
			else
			{
				printAtCenterOfLine(28, "   Виберіть клітинку на полі суперника і натисніть ENTER   ", p, consoleWidth);
			}
			break;
		}
	}
	while (true)
	{
		int key = _getch();
		if (key == 224)
		{
			key = _getch();
		}
		switch (key)
		{
		case(72): //up
		{
			if (placeOfSelectedCellY != startOfFieldsY)
			{
				selectedCell.backToColor();
				selectedCell.drawCell(placeOfSelectedCellX, placeOfSelectedCellY);
				drawOponentsShips();
				selectedCell.changeColor();
				placeOfSelectedCellY -= sizeOfCell;
				selectedCell.drawCell(placeOfSelectedCellX, placeOfSelectedCellY);
			}
		}
		break;
		case(80):  // down
		{
			if (placeOfSelectedCellY != startOfFieldsY + (sizeOfField - 1)*sizeOfCell)
			{
				selectedCell.backToColor();
				selectedCell.drawCell(placeOfSelectedCellX, placeOfSelectedCellY);
				drawOponentsShips();
				selectedCell.changeColor();
				placeOfSelectedCellY += sizeOfCell;
				selectedCell.drawCell(placeOfSelectedCellX, placeOfSelectedCellY);
			}
		}
		break;
		case(75): // left
		{
			if (placeOfSelectedCellX != startOfOponentsFieldX)
			{
				selectedCell.backToColor();
				selectedCell.drawCell(placeOfSelectedCellX, placeOfSelectedCellY);
				drawOponentsShips();
				selectedCell.changeColor();
				placeOfSelectedCellX -= sizeOfCell;
				selectedCell.drawCell(placeOfSelectedCellX, placeOfSelectedCellY);
			}
		}
		break;
		case(77): //right
		{
			if (placeOfSelectedCellX != startOfOponentsFieldX + sizeOfCell* (sizeOfField - 1))
			{
				selectedCell.backToColor();
				selectedCell.drawCell(placeOfSelectedCellX, placeOfSelectedCellY);
				drawOponentsShips();
				selectedCell.changeColor();
				placeOfSelectedCellX += sizeOfCell;
				selectedCell.drawCell(placeOfSelectedCellX, placeOfSelectedCellY);
			}

		}
		break;
		case(13): // enter
		{
			if (oponentsField.getCell((placeOfSelectedCellX - startOfOponentsFieldX) / sizeOfCell, (placeOfSelectedCellY - startOfFieldsY) / sizeOfCell).getStatus() != CellStatus::Hit &&
				oponentsField.getCell((placeOfSelectedCellX - startOfOponentsFieldX) / sizeOfCell, (placeOfSelectedCellY - startOfFieldsY) / sizeOfCell).getStatus() != CellStatus::Missed)
			{
				if (oponentsField.getCell((placeOfSelectedCellX - startOfOponentsFieldX) / sizeOfCell, (placeOfSelectedCellY - startOfFieldsY) / sizeOfCell).getStatus() == CellStatus::HasShip)
				{
					score += 10;
					Printer p1(textColor, mainBackgroundColor);
					if (lang == Languages::English)
					{
						printAtCenterOfLine(4, "Score ", p1, consoleWidth);
						cout << score;
					}
					else
					{
						printAtCenterOfLine(4, "Рахунок ", p1, consoleWidth);
						cout << score;
					}
					killingTheShip();
					if (myWIn())
					{
						Printer p(textColor, mainBackgroundColor);
						if (lang == Languages::English)
						{
							printAtCenterOfLine(28, "                   You won !!!                    ", p, consoleWidth);
							printAtCenterOfLine(29, "Press ENTER to continue playing and ESC to stop", p, consoleWidth);
						}
						else
						{
							printAtCenterOfLine(28, "                    Ви перемогли !!!                    ", p, consoleWidth);
							printAtCenterOfLine(29, "Натисніть ENTER для продовження гри або ESC - для пипинення", p, consoleWidth);
						}
						key = _getch();
						while (key)
						{
							if (key == 13)
							{
								clean();
								return new GameView(lang, type);
							}
							else if (key == 27)
							{
								clean();
								return new ResultView(lang, type);
							}
							key = _getch();
						}
					}
				}
				else
				{
					drawDot(placeOfSelectedCellX, placeOfSelectedCellY);
					oponentsField.getCell((placeOfSelectedCellX - startOfOponentsFieldX) / sizeOfCell, (placeOfSelectedCellY - startOfFieldsY) / sizeOfCell).setStatus(CellStatus::Missed);
					srand(time(NULL));
					int i = rand() % sizeOfField;
					int j = rand() % sizeOfField;
					while (myField.getCell(i, j).getStatus() == CellStatus::Hit || myField.getCell(i, j).getStatus() == CellStatus::Missed)
					{
						i = rand() % sizeOfField;
						j = rand() % sizeOfField;
					}
					Sleep(300);
					while (myField.getCell(i, j).getStatus() == CellStatus::HasShip)
					{
						myShipsKilling(i, j);
						if (oponentsWIn())
						{
							Printer p(textColor, mainBackgroundColor);
							if (lang == Languages::English)
							{
								printAtCenterOfLine(28, "                   You lost ):                    ", p, consoleWidth);
								printAtCenterOfLine(29, "          Press ENTER to continue          ", p, consoleWidth);
							}
							else
							{
								printAtCenterOfLine(28, "                    Ви програли ):                    ", p, consoleWidth);
								printAtCenterOfLine(29, "          Натисніть ENTER для продовження          ", p, consoleWidth);
							}
							key = _getch();
							while (key)
							{
								if (key == 13)
								{
									clean();
									return new ResultView(lang, type);
								}
								key = _getch();
							}
						}
						i = rand() % sizeOfField;
						j = rand() % sizeOfField;
					}
					drawDot(startOfMyfieldX + sizeOfCell* i, startOfFieldsY + sizeOfCell*j);
					myField.getCell(i, j).setStatus(CellStatus::Missed);
					
				}
			}
		}
		}

	}
	return nullptr;
}
