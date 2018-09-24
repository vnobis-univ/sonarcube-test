#include "FieldView.h"

Status** FieldView::setScheme(short x, short y, short size, Status **tempScheme)
{
	if (position == "horizontal")
	{
		for (size_t i = 0; i < size; i++)
		{
			tempScheme[x + i][y] = Status::Ship;
		}
		if (x == 0)//left
		{
			tempScheme[x + size][y] = Status::Cant;
			for (size_t i = 0; i <= size; i++)
			{
				if (y == 0)//up corner
				{
					tempScheme[i][y + 1] = Status::Cant;
				}
				else if (y == 9)//down corner
				{
					tempScheme[i][y - 1] = Status::Cant;
				}
				else
				{
					tempScheme[i][y - 1] = Status::Cant;
					tempScheme[i][y + 1] = Status::Cant;
				}
			}
		}
		else if (x + size == 10)//right
		{
			tempScheme[x - 1][y] = Status::Cant;
			for (size_t i = x - 1; i < x + size; i++)
			{
				if (y == 0)//up corner
					tempScheme[i][y + 1] = Status::Cant;
				else if (y == 9)//down corner
					tempScheme[i][y - 1] = Status::Cant;
				else
				{
					tempScheme[i][y - 1] = Status::Cant;
					tempScheme[i][y + 1] = Status::Cant;
				}
			}
		}
		else if (x + size < 10)
		{
			tempScheme[x - 1][y] = Status::Cant;
			tempScheme[x + size][y] = Status::Cant;
			for (size_t i = x - 1; i <= x + size; i++)
			{
				if (y == 0)//up
					tempScheme[i][y + 1] = Status::Cant;
				else if (y == 9)//down
					tempScheme[i][y - 1] = Status::Cant;
				else
				{
					tempScheme[i][y + 1] = Status::Cant;
					tempScheme[i][y - 1] = Status::Cant;
				}
			}

		}
	}
	else if (position == "vertical")
	{
		for (size_t i = 0; i < size; i++)
		{
			tempScheme[x][y + i] = Status::Ship;
		}
		if (y == 0)//up
		{
			tempScheme[x][y + size] = Status::Cant;
			for (size_t i = 0; i <= size; i++)
			{
				if (x == 0)//left corner
				{
					tempScheme[x + 1][y + i] = Status::Cant;
				}
				else if (x == 9)//down corner
				{
					tempScheme[x - 1][y + i] = Status::Cant;
				}
				else
				{
					tempScheme[x - 1][y + i] = Status::Cant;
					tempScheme[x + 1][y + i] = Status::Cant;
				}
			}
		}
		else if (y + size == 10)//down
		{
			tempScheme[x][y - 1] = Status::Cant;
			for (size_t i = y - 1; i < y + size; i++)
			{
				if (x == 0)//up corner
					tempScheme[x + 1][i] = Status::Cant;
				else if (x == 9)//down corner
					tempScheme[x - 1][i] = Status::Cant;
				else
				{
					tempScheme[x + 1][i] = Status::Cant;
					tempScheme[x - 1][i] = Status::Cant;
				}
			}
		}
		else if (y + size < 10)
		{
			tempScheme[x][y - 1] = Status::Cant;
			tempScheme[x][y + size] = Status::Cant;
			for (size_t i = y - 1; i <= y + size; i++)
			{
				if (x == 0)//up
					tempScheme[x + 1][i] = Status::Cant;
				else if (x == 9)//down
					tempScheme[x - 1][i] = Status::Cant;
				else
				{
					tempScheme[x + 1][i] = Status::Cant;
					tempScheme[x - 1][i] = Status::Cant;
				}
			}

		}

	}
	return tempScheme;
}