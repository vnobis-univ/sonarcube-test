#include "Ship.h"



Ship::Ship():
	size(1), visibility(Visibility ::Visible), coordinateX(0), coordinateY(0), red(0), green(0), blue(0)
{
}

Ship::Ship(int _size, Visibility _visibility, int _red, int _green, int _blue):
	size(_size), 
	visibility(_visibility), 
	coordinateX(0), 
	coordinateY(0), 
	red(_red), 
	green(_green), 
	blue(_blue), 
	orientation(Orientation::Horizontal),
	status(ShipStatus::NotKilled)
{
	arrayOfCells = new Cell[size];
}

void Ship::draw(int _coordinateX, int _coordinateY)
{
	coordinateX = _coordinateX;
	coordinateY = _coordinateY;
	if (orientation == Orientation::Horizontal)
	{
		HDC hdc = GetDC(GetConsoleWindow());
		HPEN Pen(CreatePen(PS_SOLID, 2, RGB(red, green, blue)));
		HGDIOBJ currentPen = (HPEN)SelectObject(hdc, Pen);
		MoveToEx(hdc, coordinateX, coordinateY, NULL);
		LineTo(hdc, coordinateX + size * sizeOfCell, coordinateY);
		LineTo(hdc, coordinateX + size * sizeOfCell, coordinateY + sizeOfCell);
		LineTo(hdc, coordinateX, coordinateY + sizeOfCell);
		LineTo(hdc, coordinateX, coordinateY);
	}
	else
	{
		HDC hdc = GetDC(GetConsoleWindow());
		HPEN Pen(CreatePen(PS_SOLID, 2, RGB(red, green, blue)));
		HGDIOBJ currentPen = (HPEN)SelectObject(hdc, Pen);
		MoveToEx(hdc, coordinateX, coordinateY, NULL);
		LineTo(hdc, coordinateX + sizeOfCell, coordinateY);
		LineTo(hdc, coordinateX + sizeOfCell, coordinateY + size * sizeOfCell);
		LineTo(hdc, coordinateX, coordinateY + size* sizeOfCell);
		LineTo(hdc, coordinateX, coordinateY);
	}
}

void Ship::setCoordinateX(int _coordinateX)
{
	coordinateX = _coordinateX;
}

void Ship::setCoordinateY(int _coordinateY)
{
	coordinateY = _coordinateY;
}

void Ship::setVisibility(Visibility visib)
{
	visibility = visib;
}

void Ship::setOrientation(Orientation orient)
{
	orientation = orient;
}

void Ship::setStatus(ShipStatus stat)
{
	status = stat;
}

int Ship::getCoordinateX()
{
	return coordinateX;
}

int Ship::getCoordinateY()
{
	return coordinateY;
}

int Ship::getSize()
{
	return size;
}

ShipStatus Ship::getStatus()
{
	return status;
}

Visibility Ship::getVisibility()
{
	return visibility;
}

void Ship::changeColor()
{
	red = 0;
	green = 204;
	blue = 204;
}

void Ship::backToColor()
{
	red = 204;
	green = 0;
	blue = 102;
}

void Ship::toMainColor()
{
	red = 216;
	green = 191; 
	blue = 216;
}

Cell & Ship::getCell(int i)
{
	return arrayOfCells[i];
}


Orientation Ship::getOrientation()
{
	return orientation;
}

void Ship::turning()
{
	if (orientation == Orientation::Horizontal)
	{
		orientation = Orientation::Vertical;
		if (coordinateX < sizeOfField*sizeOfCell / 2 + startOfMyfieldX &&
			coordinateY < sizeOfField * sizeOfCell / 2 + startOfFieldsY)
		{
			draw(coordinateX, coordinateY);
		}
		else if (coordinateX >= sizeOfField*sizeOfCell / 2 + startOfMyfieldX &&
			coordinateY < sizeOfField * sizeOfCell / 2 + startOfFieldsY)
		{
			coordinateX += sizeOfCell * (size - 1);
			draw(coordinateX, coordinateY);
		}
		else if (coordinateX <= sizeOfField*sizeOfCell / 2 + startOfMyfieldX &&
			coordinateY > sizeOfField * sizeOfCell / 2 + startOfFieldsY)
		{
			coordinateY -= sizeOfCell * (size - 1);
			draw(coordinateX, coordinateY);
		}
		else
		{
			coordinateY -= sizeOfCell * (size - 1);
			coordinateX += sizeOfCell * (size - 1);
			draw(coordinateX, coordinateY);
		}
	}
	else
	{
		orientation = Orientation::Horizontal;
		if (coordinateX <= sizeOfField*sizeOfCell / 2 + startOfMyfieldX &&
			coordinateY <= sizeOfField * sizeOfCell / 2 + startOfFieldsY)
		{
			draw(coordinateX, coordinateY);
		}
		else if (coordinateX >= sizeOfField*sizeOfCell / 2 + startOfMyfieldX &&
			coordinateY <= sizeOfField * sizeOfCell / 2 + startOfFieldsY)
		{
			coordinateX -= sizeOfCell * (size - 1);
			draw(coordinateX, coordinateY);
		}
		else if (coordinateX <= sizeOfField*sizeOfCell / 2 + startOfMyfieldX &&
			coordinateY > sizeOfField * sizeOfCell / 2 + startOfFieldsY)
		{
			coordinateY += sizeOfCell * (size - 1);
			draw(coordinateX, coordinateY);
		}
		else
		{
			coordinateY += sizeOfCell * (size - 1);
			coordinateX -= sizeOfCell * (size - 1);
			draw(coordinateX, coordinateY);
		}
	}
}

