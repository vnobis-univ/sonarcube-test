#include "FieldView.h"
#include "Functions.h"
#include "nextOption.h"
#include "MainOption.h"


int FieldView::AutoPosShips(int _pole[10][10])
{
	int k;
	int rand_chislo, rand_chislo1, ts;
	srand(time(NULL));

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			_pole[i][j] = 0;
		}
	}

	do {
		f = 0;
		rand_chislo = rand() % 10;
		rand_chislo1 = rand() % 10;
		ts = 1 + rand() % 4;

		if (ts == 1)
		{
			for (i = 0; i < 3; i++)
			{
				if (rand_chislo == i)
				{
					f = 1;
				}
			}
		}

		if (ts == 2)
		{
			for (i = 7; i < 10; i++)
			{
				if (rand_chislo == i)
				{
					f = 1;
				}
			}
		}

		if (ts == 3)
		{
			for (i = 0; i < 3; i++)
			{
				if (rand_chislo1 == i)
				{
					f = 1;
				}
			}
		}

		if (ts == 4)
		{
			for (i = 7; i < 10; i++)
			{
				if (rand_chislo1 == i)
				{
					f = 1;
				}
			}
		}
	} while (f == 1);

	switch (ts) {
		case 1:
		{
			_pole[rand_chislo][rand_chislo1] = 1;
			_pole[rand_chislo - 1][rand_chislo1] = 1;
			_pole[rand_chislo - 2][rand_chislo1] = 1;
			_pole[rand_chislo - 3][rand_chislo1] = 1;
			break;
		}
		case 2: 
		{
			_pole[rand_chislo][rand_chislo1] = 1;
			_pole[rand_chislo + 1][rand_chislo1] = 1;
			_pole[rand_chislo + 2][rand_chislo1] = 1;
			_pole[rand_chislo + 3][rand_chislo1] = 1;
			break;
		}
		case 3:
		{
			_pole[rand_chislo][rand_chislo1] = 1;
			_pole[rand_chislo][rand_chislo1 - 1] = 1;
			_pole[rand_chislo][rand_chislo1 - 2] = 1;
			_pole[rand_chislo][rand_chislo1 - 3] = 1; 
			break;
		}
		case 4: 
		{
			_pole[rand_chislo][rand_chislo1] = 1;
			_pole[rand_chislo][rand_chislo1 + 1] = 1;
			_pole[rand_chislo][rand_chislo1 + 2] = 1;
			_pole[rand_chislo][rand_chislo1 + 3] = 1;
			break;
		}
	}

	for (k = 0; k < 3; k++)
	{
		do
		{
			f = 0;
			rand_chislo = rand() % 10;
			rand_chislo1 = rand() % 10;

			ts = 1 + rand() % 4;

			if (ts == 1)
			{
				if (rand_chislo != 0)
				{
					for (i = rand_chislo - 2; i < rand_chislo + 2; i++)
					{
						for (j = rand_chislo1 - 1; j <= rand_chislo1 + 1; j++)
						{
							if (_pole[i][j] != 0)
							{
								f = 1;
							}
						}
					}
				}
				else f = 1;
			}

			if (ts == 2)
			{
				if (rand_chislo != 9)
				{
					for (i = rand_chislo - 1; i <= rand_chislo + 2; i++)
					{
						for (j = rand_chislo1 - 1; j <= rand_chislo1 + 1; j++)
						{
							if (_pole[i][j] != 0)
							{
								f = 1;
							}
						}
					}
				}
				else f = 1;
			}

			if (ts == 3) {
				if (rand_chislo1 != 0)
				{
					for (i = rand_chislo - 1; i <= rand_chislo + 1; i++)
					{
						for (j = rand_chislo1 - 2; j <= rand_chislo1 + 1; j++)
						{
							if (_pole[i][j] != 0)
							{
								f = 1;
							}
						}
					}
				}
				else f = 1;
			}

			if (ts == 4)
			{
				if (rand_chislo1 != 9)
				{
					for (i = rand_chislo - 1; i <= rand_chislo + 1; i++)
					{
						for (j = rand_chislo1 - 1; j <= rand_chislo1 + 2; j++)
						{
							if (_pole[i][j] != 0)
							{
								f = 1;
							}
						}
					}
				}
				else f = 1;
			}
		} while (f == 1);

		switch (ts)
		{
		case 1:
		{
			_pole[rand_chislo][rand_chislo1] = 1;
			_pole[rand_chislo - 1][rand_chislo1] = 1;
			break;
		}
		case 2:
		{
			_pole[rand_chislo][rand_chislo1] = 1;
			_pole[rand_chislo + 1][rand_chislo1] = 1;
			break;
		}
		case 3:
		{
			_pole[rand_chislo][rand_chislo1] = 1;
			_pole[rand_chislo][rand_chislo1 - 1] = 1;
			break;
		}
		case 4:
		{
			_pole[rand_chislo][rand_chislo1] = 1;
			_pole[rand_chislo][rand_chislo1 + 1] = 1;
			break;
		}
		}

	}

	for (k = 0; k < 2; k++)
	{
		do
		{
			f = 0;
			rand_chislo = 0 + rand() % 10;
			rand_chislo1 = 0 + rand() % 10;
			ts = 1 + rand() % 4;

			if (ts == 1)
			{
				if (rand_chislo != 0 && rand_chislo != 1)
				{
					for (i = rand_chislo - 3; i < rand_chislo + 2; i++)
					{
						for (j = rand_chislo1 - 1; j <= rand_chislo1 + 1; j++)
						{
							if (_pole[i][j] != 0)
							{
								f = 1;
							}
						}
					}
				}
				else f = 1;
			}

			if (ts == 2)
			{
				if (rand_chislo != 9 && rand_chislo != 8)
				{
					for (i = rand_chislo - 1; i <= rand_chislo + 3; i++)
					{
						for (j = rand_chislo1 - 1; j <= rand_chislo1 + 1; j++)
						{
							if (_pole[i][j] != 0) { f = 1; }
						}
					}
				}
				else f = 1;
			}

			if (ts == 3)
			{
				if (rand_chislo1 != 0 && rand_chislo1 != 1)
				{
					for (i = rand_chislo - 1; i <= rand_chislo + 1; i++)
					{
						for (j = rand_chislo1 - 3; j <= rand_chislo1 + 1; j++)
						{
							if (_pole[i][j] != 0) { f = 1; }
						}
					}
				}
				else f = 1;
			}

			if (ts == 4)
			{
				if (rand_chislo1 != 9 && rand_chislo1 != 8)
				{
					for (i = rand_chislo - 1; i <= rand_chislo + 1; i++)
					{
						for (j = rand_chislo1 - 1; j <= rand_chislo1 + 3; j++)
						{
							if (_pole[i][j] != 0) { f = 1; }
						}
					}
				}
				else f = 1;
			}
		} while (f == 1);

		switch (ts) {
		case 1:
		{
			_pole[rand_chislo][rand_chislo1] = 1;
			_pole[rand_chislo - 1][rand_chislo1] = 1;
			_pole[rand_chislo - 2][rand_chislo1] = 1;
			break;
		}
		case 2:
		{
			_pole[rand_chislo][rand_chislo1] = 1;
			_pole[rand_chislo + 1][rand_chislo1] = 1;
			_pole[rand_chislo + 2][rand_chislo1] = 1;
			break;
		}
		case 3:
		{
			_pole[rand_chislo][rand_chislo1] = 1;
			_pole[rand_chislo][rand_chislo1 - 1] = 1;
			_pole[rand_chislo][rand_chislo1 - 2] = 1;
			break;
		}
		case 4:
		{
			_pole[rand_chislo][rand_chislo1] = 1;
			_pole[rand_chislo][rand_chislo1 + 1] = 1;
			_pole[rand_chislo][rand_chislo1 + 2] = 1;
			break;
		}
		}
	}

	for (i = 0; i < 4; i++)
	{
		do 
		{
			rand_chislo = 0 + rand() % 10;
			rand_chislo1 = 0 + rand() % 10;
		} while (_pole[rand_chislo][rand_chislo1] != 0 || _pole[rand_chislo + 1][rand_chislo1] != 0 || _pole[rand_chislo - 1][rand_chislo1] != 0 || _pole[rand_chislo][rand_chislo1 + 1] != 0 || _pole[rand_chislo][rand_chislo1 - 1] != 0 || _pole[rand_chislo + 1][rand_chislo1 + 1] != 0 || _pole[rand_chislo - 1][rand_chislo1 - 1] != 0 || _pole[rand_chislo + 1][rand_chislo1 - 1] != 0 || _pole[rand_chislo - 1][rand_chislo1 + 1] != 0);

		_pole[rand_chislo][rand_chislo1] = 1;
	}

	return _pole[10][10];
}

int FieldView::ManPosShips(int _my_pole[10][10])
{
	system("cls");
	 {
		setCursoreAtPosition(33, 0);
		cout << "SEA WAR";
		setCursoreAtPosition(9, 0);
		cout << "Computer pole";
		setCursoreAtPosition(51, 0);
		cout << "Player pole";
		SetColor(7, 0);
		setCursoreAtPosition(51, 26);
		cout << "Hit - press Enter";
		setCursoreAtPosition(51, 27);
		cout << "Exit - press ESC";
		setCursoreAtPosition(51, 28);
		cout << "Control - press arrows";
		setCursoreAtPosition(51, 29);
		cout << "Turn - press Space";
		setCursoreAtPosition(1, 27);
		cout << "   Instruction:";
		setCursoreAtPosition(1, 28);
		cout << "Arrange your ships";
		setCursoreAtPosition(1, 29);
		cout << "   on the field.";
	} 
	 for (int i = 0, x = 1; i < 10, x < 31; i++, x = x + 3)
	{
		for (int j = 0, y = 1; j < 10, y < 21; j++, y = y + 2)
		{
			setCursoreAtPosition(x, y);
			if ((j + i) % 2 != 0) 
			{ 
				SetColor(0, 1);
				cout << "   ";
			}
			else 
			{ 
				SetColor(0, 9);
				cout << "   ";
			}
			setCursoreAtPosition(x, y + 1);
			if ((j + i) % 2 != 0) 
			{ 
				SetColor(0, 1);
				cout << "   ";
			}
			else
			{ 
				SetColor(0, 9); 
				cout << "   ";
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			_my_pole[i][j] = 0;
		}
	}

	ui = 0;
	for (u = 1; u < 5; u++)
	{
		if (ui == 0)
		{
			for (i = 0, x = 41; i < 10, x < 71; i++, x = x + 3)
			{
				for (j = 0, y = 1; j < 10, y < 21; j++, y = y + 2)
				{
					setCursoreAtPosition(x, y);
					if (_my_pole[i][j] == 1)
					{
						SetColor(0, 12); cout << "   ";
					}
					else
					{
						if ((j + i) % 2 != 0)
						{
							SetColor(0, 1);
							cout << "   ";
						}
						else
						{
							SetColor(0, 9);
							cout << "   ";
						}
					}
					setCursoreAtPosition(x, y + 1);
					if (_my_pole[i][j] == 1)
					{
						SetColor(0, 12);
						cout << "   ";
					}
					else
					{
						if ((j + i) % 2 != 0)
						{
							SetColor(0, 1);
							cout << "   ";
						}
						else
						{
							SetColor(0, 9);
							cout << "   ";
						}
					}
				}
			}
		}

		switch (u)
		{
		case 1:
		{ 
			x = 41;
			y = nap = 1;
			i = j = 0;
		for (e = x; e < x + 12; e = e + 3)
		{

			setCursoreAtPosition(e, y); SetColor(0, 14); cout << "   ";
			setCursoreAtPosition(e, y + 1); SetColor(0, 14); cout << "   ";
		}
		do {
			f = 0;
			int code = _getch();
			if (code == 224)
			{
				code = _getch();
				switch (code)
				{
				case 72://вверх
				{
					if (y != 1)
					{
						if (nap == 1)
						{
							for (e = x; e < x + 12; e = e + 3)
							{
								i = (e - 40) / 3;
								j = y / 2;
								setCursoreAtPosition(e, y);
								if ((i + j) % 2 != 0)
								{ 
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{ 
									SetColor(0, 9);
									cout << "   ";
								}
								setCursoreAtPosition(e, y + 1); 
								if ((i + j) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   "; 
								}
								else 
								{ 
									SetColor(0, 9);
									cout << "   ";
								}
							}
							y = y - 2;
							for (e = x; e < x + 12; e = e + 3)
							{
								setCursoreAtPosition(e, y);
								SetColor(0, 14);
								cout << "   ";
								setCursoreAtPosition(e, y + 1);
								SetColor(0, 14);
								cout << "   ";
							}
						}
						else
						{
							if (y != 33) 
							{
								for (e = y; e < y + 8; e = e + 2)
								{
									i = (x - 40) / 3;
									j = e / 2;
									setCursoreAtPosition(x, e);
									if ((i + j) % 2 != 0)
									{ 
										SetColor(0, 1);
										cout << "   "; 
									}
									else
									{
										SetColor(0, 9); cout << "   ";
									}
									setCursoreAtPosition(x, e + 1);
									if ((i + j) % 2 != 0)
									{ 
										SetColor(0, 1);
										cout << "   ";
									}
									else 
									{
										SetColor(0, 9);
										cout << "   "; 
									}
								}
								y = y - 2;
								for (e = y; e < y + 8; e = e + 2)
								{
									setCursoreAtPosition(x, e);
									SetColor(0, 14);
									cout << "   ";
									setCursoreAtPosition(x, e + 1);
									SetColor(0, 14);
									cout << "   ";
								}
							}
						}

					}
					break;

				}
				case 77://вправо
				{
					if (nap == 1)
					{
						if (x != 59)
						{
							for (e = x; e < x + 12; e = e + 3)
							{
								i = (e - 40) / 3;
								j = y / 2;
								setCursoreAtPosition(e, y);
								if ((i + j) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   "; 
								}
								else 
								{ 
									SetColor(0, 9);
									cout << "   "; 
								}
								setCursoreAtPosition(e, y + 1); 
								if ((i + j) % 2 != 0) 
								{
									SetColor(0, 1);
									cout << "   "; 
								}
								else 
								{ 
									SetColor(0, 9);
									cout << "   ";
								}
							}
							x = x + 3;
							for (e = x; e < x + 12; e = e + 3)
							{
								setCursoreAtPosition(e, y);
								SetColor(0, 14);
								cout << "   ";
								setCursoreAtPosition(e, y + 1);
								SetColor(0, 14);
								cout << "   ";

							}
						}
					}
					else 
					{
						if (x != 68)
						{
							for (e = y; e < y + 8; e = e + 2)
							{
								i = (x - 40) / 3;
								j = e / 2;
								setCursoreAtPosition(x, e);
								if ((i + j) % 2 != 0) 
								{ 
									SetColor(0, 1);
									cout << "   "; 
								}
								else
								{ 
									SetColor(0, 9);
									cout << "   ";
								}
								setCursoreAtPosition(x, e + 1);
								if ((i + j) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{
									SetColor(0, 9);
									cout << "   ";
								}
							}
							x = x + 3;
							for (e = y; e < y + 8; e = e + 2)
							{
								setCursoreAtPosition(x, e);
								SetColor(0, 14); 
								cout << "   ";
								setCursoreAtPosition(x, e + 1); 
								SetColor(0, 14);
								cout << "   ";
							}
						}
					}
					break;
				}
				case 80://вниз
				{
					if (nap == 1)
					{
						if (y != 19)
						{
							for (e = x; e < x + 12; e = e + 3)
							{
								i = (e - 40) / 3;
								j = y / 2;
								setCursoreAtPosition(e, y); 
								if ((i + j) % 2 != 0)
								{ 
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{ 
									SetColor(0, 9);
									cout << "   ";
								}
								setCursoreAtPosition(e, y + 1);
								if ((i + j) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{
									SetColor(0, 9);
									cout << "   ";
								}
							}
							y = y + 2;
							for (e = x; e < x + 12; e = e + 3)
							{
								setCursoreAtPosition(e, y);
								SetColor(0, 14);
								cout << "   ";
								setCursoreAtPosition(e, y + 1);
								SetColor(0, 14);
								cout << "   ";
							}
						}
					}
					else {
						if (y != 13)
						{
							for (e = y; e < y + 8; e = e + 2)
							{
								i = (x - 40) / 3;
								j = e / 2;
								setCursoreAtPosition(x, e);
								if ((i + j) % 2 != 0)
								{ 
									SetColor(0, 1);
									cout << "   ";
								}
								else 
								{
									SetColor(0, 9);
									cout << "   "; 
								}
								setCursoreAtPosition(x, e + 1);
								if ((i + j) % 2 != 0) 
								{ 
									SetColor(0, 1);
									cout << "   ";
								}
								else 
								{ 
									SetColor(0, 9);
									cout << "   ";
								}
							}
							y = y + 2;
							for (e = y; e < y + 8; e = e + 2)
							{
								setCursoreAtPosition(x, e);
								SetColor(0, 14);
								cout << "   ";
								setCursoreAtPosition(x, e + 1);
								SetColor(0, 14);
								cout << "   ";
							}
						}
					}
					break;
				}
				case 75://вліво
				{ 
					if (nap == 1)
					{

						if (x != 41)
						{
							for (e = x; e < x + 12; e = e + 3)
							{
								i = (e - 40) / 3;
								j = y / 2;
								setCursoreAtPosition(e, y);
								if ((i + j) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{
									SetColor(0, 9);
									cout << "   ";
								}
								setCursoreAtPosition(e, y + 1);
								if ((i + j) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{
									SetColor(0, 9);
									cout << "   ";
								}
							}
							x = x - 3;
							for (e = x; e < x + 12; e = e + 3)
							{
								setCursoreAtPosition(e, y);
								SetColor(0, 14);
								cout << "   ";
								setCursoreAtPosition(e, y + 1);
								SetColor(0, 14);
								cout << "   ";

							}
						}
					}
				else {
					if (x != 41) {
						for (e = y; e < y + 8; e = e + 2)
						{
							i = (x - 40) / 3;
							j = e / 2;
							setCursoreAtPosition(x, e); if ((i + j) % 2 != 0) { SetColor(0, 1); cout << "   "; }
							else { SetColor(0, 9); cout << "   "; }
							setCursoreAtPosition(x, e + 1); if ((i + j) % 2 != 0) { SetColor(0, 1); cout << "   "; }
							else { SetColor(0, 9); cout << "   "; }
						}
						x = x - 3;
						for (e = y; e < y + 8; e = e + 2)
						{
							setCursoreAtPosition(x, e); SetColor(0, 14); cout << "   ";
							setCursoreAtPosition(x, e + 1); SetColor(0, 14); cout << "   ";
						}
					}
				}
				break;
				}
				}
			}
			else 
			{
				switch (code) 
				{
				case 32:
				{
					if (nap == 1 && y < 15 || nap == -1 && x < 62)
					{
						nap = nap*(-1);
						if (nap == 1)
						{
							for (e = y; e < y + 8; e = e + 2)
							{
								i = (x - 40) / 3;
								j = e / 2;
								setCursoreAtPosition(x, e);
								if (_my_pole[i][j] == 1)
								{
									SetColor(0, 12);
									cout << "   ";
								}
								else
								{
									if ((i + j) % 2 != 0)
									{
										SetColor(0, 1);
										cout << "   ";
									}
									else
									{
										SetColor(0, 9);
										cout << "   ";
									}
								}
								setCursoreAtPosition(x, e + 1);
								if (_my_pole[i][j] == 1)
								{
									SetColor(0, 12);
									cout << "   ";
								}
								else
								{
									if ((i + j) % 2 != 0)
									{
										SetColor(0, 1);
										cout << "   ";
									}
									else
									{
										SetColor(0, 9);
										cout << "   ";
									}
								}
							}

							for (e = x; e < x + 12; e = e + 3)
							{
								setCursoreAtPosition(e, y);
								SetColor(0, 14);
								cout << "   ";
								setCursoreAtPosition(e, y + 1);
								SetColor(0, 14);
								cout << "   ";

							}
						}
						else
						{
							for (e = x; e < x + 12; e = e + 3)
							{
								i = (e - 40) / 3;
								j = y / 2;
								setCursoreAtPosition(e, y);
								if (_my_pole[i][j] == 1) 
								{ 
									SetColor(0, 12);
									cout << "   ";
								}
								else
								{ 
									if ((i + j) % 2 != 0)
									{ 
										SetColor(0, 1);
										cout << "   "; 
									}
									else
									{ 
										SetColor(0, 9);
										cout << "   "; 
									} 
								}
								setCursoreAtPosition(e, y + 1);
								if (_my_pole[i][j] == 1)
								{
									SetColor(0, 12);
									cout << "   ";
								}
								else
								{ 
									if ((i + j) % 2 != 0)
									{ 
										SetColor(0, 1);
										cout << "   "; 
									}
									else
									{
										SetColor(0, 9);
										cout << "   ";
									}
								}
							}

							for (e = y; e < y + 8; e = e + 2)
							{
								setCursoreAtPosition(x, e);
								SetColor(0, 14);
								cout << "   ";
								setCursoreAtPosition(x, e + 1);
								SetColor(0, 14); 
								cout << "   ";
							}
						}
					}
					break;
				}
				case 13:
				{
					if (nap == 1)
					{
						for (e = x; e < x + 12; e = e + 3)
						{
							i = (e - 40) / 3;
							j = y / 2;
							_my_pole[i][j] = 1;
						}

					}
					else {

						for (e = y; e < y + 8; e = e + 2)
						{
							i = (x - 40) / 3;
							j = e / 2;
							_my_pole[i][j] = 1;
						}
					}

					f = 1; break;
				}

				case 27:
				{
					f = 1;
					ui = 1;
					break; }
				}
			}
		} while (f != 1);
		break;
		}

		case 2:
		{ 
			for (w = 0; w < 2; w++)
			{
				if (ui == 0)
				{
					for (i = 0, x = 41; i < 10, x < 71; i++, x = x + 3)
					{
						for (j = 0, y = 1; j < 10, y < 21; j++, y = y + 2)
						{
							setCursoreAtPosition(x, y); 
							if (_my_pole[i][j] == 1)
							{ 
								SetColor(0, 12);
								cout << "   ";
							}
							else
							{ 
								if ((j + i) % 2 != 0) 
								{ 
									SetColor(0, 1);
									cout << "   ";
								} 
								else
								{ 
									SetColor(0, 9);
									cout << "   ";
								} 
							}
							setCursoreAtPosition(x, y + 1);
							if (_my_pole[i][j] == 1)
							{
								SetColor(0, 12);
								cout << "   ";
							}
							else
							{ 
								if ((j + i) % 2 != 0)
								{ 
									SetColor(0, 1);
									cout << "   "; 
								}
								else 
								{
									SetColor(0, 9);
									cout << "   ";
								} 
							}
						}
					}
					x = 41; y = nap = 1;
					i = j = 0;
					for (e = x; e < x + 9; e = e + 3)
					{

						setCursoreAtPosition(e, y); 
						SetColor(0, 14); 
						cout << "   ";
						setCursoreAtPosition(e, y + 1);
						SetColor(0, 14);
						cout << "   ";
					}
					do {
						f = 0;
						int code = _getch();
						if (code == 224)
						{
							code = _getch();
							switch (code)
							{
								{
							case 72:
							{
								if (y != 1)
								{
									if (nap == 1)
									{
										for (e = x; e < x + 9; e = e + 3)
										{
											i = (e - 40) / 3;
											j = y / 2;
											setCursoreAtPosition(e, y);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
											setCursoreAtPosition(e, y + 1);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
										}
										y = y - 2;
										for (e = x; e < x + 9; e = e + 3)
										{
											setCursoreAtPosition(e, y);
											SetColor(0, 14);
											cout << "   ";
											setCursoreAtPosition(e, y + 1);
											SetColor(0, 14);
											cout << "   ";
										}
									}
									else
									{
										if (y != 33)
										{
											for (e = y; e < y + 6; e = e + 2)
											{
												i = (x - 40) / 3;
												j = e / 2;
												setCursoreAtPosition(x, e);
												if (_my_pole[i][j] == 1)
												{
													SetColor(0, 12);
													cout << "   ";
												}
												else
												{
													if ((i + j) % 2 != 0)
													{
														SetColor(0, 1);
														cout << "   ";
													}
													else
													{
														SetColor(0, 9);
														cout << "   ";
													}
												}
												setCursoreAtPosition(x, e + 1);
												if (_my_pole[i][j] == 1)
												{
													SetColor(0, 12);
													cout << "   ";
												}
												else
												{
													if ((i + j) % 2 != 0)
													{
														SetColor(0, 1);
														cout << "   ";
													}
													else
													{
														SetColor(0, 9);
														cout << "   ";
													}
												}
											}
											y = y - 2;
											for (e = y; e < y + 6; e = e + 2)
											{
												setCursoreAtPosition(x, e);
												SetColor(0, 14);
												cout << "   ";
												setCursoreAtPosition(x, e + 1);
												SetColor(0, 14);
												cout << "   ";
											}
										}
									}

								}

								break;

							}
							case 77:
							{
								if (nap == 1)
								{
									if (x != 62)
									{
										for (e = x; e < x + 9; e = e + 3) {
											i = (e - 40) / 3;
											j = y / 2;
											setCursoreAtPosition(e, y); if (_my_pole[i][j] == 1) { SetColor(0, 12); cout << "   "; }
											else { if ((i + j) % 2 != 0) { SetColor(0, 1); cout << "   "; } else { SetColor(0, 9); cout << "   "; } }
											setCursoreAtPosition(e, y + 1); if (_my_pole[i][j] == 1) { SetColor(0, 12); cout << "   "; }
											else { if ((i + j) % 2 != 0) { SetColor(0, 1); cout << "   "; } else { SetColor(0, 9); cout << "   "; } }
										}
										x = x + 3;
										for (e = x; e < x + 9; e = e + 3)
										{
											setCursoreAtPosition(e, y); SetColor(0, 14); cout << "   ";
											setCursoreAtPosition(e, y + 1); SetColor(0, 14); cout << "   ";

										}
									}
								}
								else {
									if (x != 68) {
										for (e = y; e < y + 6; e = e + 2)
										{
											i = (x - 40) / 3;
											j = e / 2;
											setCursoreAtPosition(x, e);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
											setCursoreAtPosition(x, e + 1);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
										}
										x = x + 3;
										for (e = y; e < y + 6; e = e + 2)
										{
											setCursoreAtPosition(x, e);
											SetColor(0, 14);
											cout << "   ";
											setCursoreAtPosition(x, e + 1);
											SetColor(0, 14);
											cout << "   ";
										}
									}
								}
								break;
							}
							case 80:
							{
								if (nap == 1)
								{
									if (y != 19)
									{
										for (e = x; e < x + 9; e = e + 3)
										{
											i = (e - 40) / 3;
											j = y / 2;
											setCursoreAtPosition(e, y);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
											setCursoreAtPosition(e, y + 1);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
										}
										y = y + 2;
										for (e = x; e < x + 9; e = e + 3)
										{
											setCursoreAtPosition(e, y);
											SetColor(0, 14);
											cout << "   ";
											setCursoreAtPosition(e, y + 1);
											SetColor(0, 14);
											cout << "   ";
										}
									}
								}
								else
								{
									if (y != 15)
									{
										for (e = y; e < y + 6; e = e + 2)
										{
											i = (x - 40) / 3;
											j = e / 2;
											setCursoreAtPosition(x, e);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
											setCursoreAtPosition(x, e + 1);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
										}
										y = y + 2;
										for (e = y; e < y + 6; e = e + 2)
										{
											setCursoreAtPosition(x, e);
											SetColor(0, 14);
											cout << "   ";
											setCursoreAtPosition(x, e + 1);
											SetColor(0, 14);
											cout << "   ";
										}
									}
								}
								break;
							}
							case 75:
							{
								if (nap == 1)
								{
									if (x != 41)
									{
										for (e = x; e < x + 9; e = e + 3)
										{
											i = (e - 40) / 3;
											j = y / 2;
											setCursoreAtPosition(e, y);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if
													((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
											setCursoreAtPosition(e, y + 1); if (_my_pole[i][j] == 1) { SetColor(0, 12); cout << "   "; }
											else { if ((i + j) % 2 != 0) { SetColor(0, 1); cout << "   "; } else { SetColor(0, 9); cout << "   "; } }
										}
										x = x - 3;
										for (e = x; e < x + 9; e = e + 3)
										{
											setCursoreAtPosition(e, y);
											SetColor(0, 14);
											cout << "   ";
											setCursoreAtPosition(e, y + 1);
											SetColor(0, 14);
											cout << "   ";
										}
									}
								}
								else
								{
									if (x != 41)
									{
										for (e = y; e < y + 6; e = e + 2)
										{
											i = (x - 40) / 3;
											j = e / 2;
											setCursoreAtPosition(x, e);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
											setCursoreAtPosition(x, e + 1);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
										}
										x = x - 3;
										for (e = y; e < y + 6; e = e + 2)
										{
											setCursoreAtPosition(x, e);
											SetColor(0, 14);
											cout << "   ";
											setCursoreAtPosition(x, e + 1);
											SetColor(0, 14);
											cout << "   ";
										}
									}
								}
								break;
							}
								}
							}
						}
						else
						{
							switch (code)
							{
							case 32:
							{
								if (nap == 1 && y < 17 || nap == -1 && x < 65)
								{
									nap = nap*(-1);
									if (nap == 1)
									{
										for (e = y; e < y + 6; e = e + 2)
										{
											i = (x - 40) / 3;
											j = e / 2;
											setCursoreAtPosition(x, e);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
											setCursoreAtPosition(x, e + 1);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
										}

										for (e = x; e < x + 9; e = e + 3)
										{
											setCursoreAtPosition(e, y);
											SetColor(0, 14);
											cout << "   ";
											setCursoreAtPosition(e, y + 1);
											SetColor(0, 14);
											cout << "   ";

										}

									}
									else
									{
										for (e = x; e < x + 9; e = e + 3)
										{
											i = (e - 40) / 3;
											j = y / 2;
											setCursoreAtPosition(e, y);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
											setCursoreAtPosition(e, y + 1);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9); cout << "   ";
												}
											}
										}

										for (e = y; e < y + 6; e = e + 2)
										{
											setCursoreAtPosition(x, e);
											SetColor(0, 14);
											cout << "   ";
											setCursoreAtPosition(x, e + 1);
											SetColor(0, 14);
											cout << "   ";
										}
									}
								}
								break;
							}
							case 13: {
								int pr = f = 0;
								if (nap == 1)
								{
									for (e = x - 3; e <= x + 9; e = e + 3)
									{
										for (int a = y - 2; a <= y + 2; a = a + 2)
										{
											i = (e - 40) / 3;
											j = a / 2;
											if (i < 10 && j < 10)
											{
												if (_my_pole[i][j] == 1)
												{
													pr = 1;
												}
											}
										}
									}

									if (pr == 0)
									{
										for (e = x; e < x + 9; e = e + 3)
										{
											i = (e - 40) / 3;
											j = y / 2;
											_my_pole[i][j] = 1;
											f = 1;
										}
									}
								}
								else
								{
									for (e = y - 2; e <= y + 6; e = e + 2)
									{
										for (int a = x - 3; a <= x + 3; a = a + 3)
										{
											i = (a - 40) / 3;
											j = e / 2;
											if (i < 10 && j < 10)
											{
												if (_my_pole[i][j] == 1)
												{
													pr = 1;
												}
											}
										}
									}
									if (pr == 0)
									{
										for (e = y; e < y + 6; e = e + 2)
										{
											i = (x - 40) / 3;
											j = e / 2;
											_my_pole[i][j] = 1;
											f = 1;
										}
									}
								}
								break;
							}
							case 27:
							{
								f = 1;
								ui = 1;
								break;
							}
							}
						}

					} while (f != 1);
				}
			}
		break;

		}

		case 3:
		{
			for (w = 0; w < 3; w++)
			{
				if (ui == 0)
				{
					for (i = 0, x = 41; i < 10, x < 71; i++, x = x + 3)
					{
						for (j = 0, y = 1; j < 10, y < 21; j++, y = y + 2)
						{
							setCursoreAtPosition(x, y);
							if (_my_pole[i][j] == 1)
							{
								SetColor(0, 12);
								cout << "   ";
							}
							else
							{
								if ((j + i) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{
									SetColor(0, 9);
									cout << "   ";
								}
							}
							setCursoreAtPosition(x, y + 1);
							if (_my_pole[i][j] == 1)
							{
								SetColor(0, 12);
								cout << "   ";
							}
							else
							{
								if ((j + i) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{
									SetColor(0, 9);
									cout << "   ";
								}
							}
						}
					}
					x = 41; y = nap = 1;
					i = j = 0;
					for (e = x; e < x + 6; e = e + 3)
					{
						setCursoreAtPosition(e, y);
						SetColor(0, 14);
						cout << "   ";
						setCursoreAtPosition(e, y + 1);
						SetColor(0, 14);
						cout << "   ";
					}
					do {
						f = 0;
						int code = _getch();
						if (code == 224)
						{
							code = _getch();
							switch (code)
							{
							case 72:
							{
								if (y != 1)
								{
									if (nap == 1)
									{
										for (e = x; e < x + 6; e = e + 3)
										{
											i = (e - 40) / 3;
											j = y / 2;
											setCursoreAtPosition(e, y);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
											setCursoreAtPosition(e, y + 1);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
										}
										y = y - 2;
										for (e = x; e < x + 6; e = e + 3)
										{
											setCursoreAtPosition(e, y);
											SetColor(0, 14);
											cout << "   ";
											setCursoreAtPosition(e, y + 1);
											SetColor(0, 14);
											cout << "   ";
										}
									}
									else
									{
										if (y != 33)
										{
											for (e = y; e < y + 4; e = e + 2)
											{
												i = (x - 40) / 3;
												j = e / 2;
												setCursoreAtPosition(x, e);
												if (_my_pole[i][j] == 1)
												{
													SetColor(0, 12);
													cout << "   ";
												}
												else
												{
													if ((i + j) % 2 != 0)
													{
														SetColor(0, 1);
														cout << "   ";
													}
													else
													{
														SetColor(0, 9);
														cout << "   ";
													}
												}
												setCursoreAtPosition(x, e + 1);
												if (_my_pole[i][j] == 1)
												{
													SetColor(0, 12);
													cout << "   ";
												}
												else
												{
													if ((i + j) % 2 != 0)
													{
														SetColor(0, 1);
														cout << "   ";
													}
													else
													{
														SetColor(0, 9);
														cout << "   ";
													}
												}
											}
											y = y - 2;
											for (e = y; e < y + 4; e = e + 2)
											{
												setCursoreAtPosition(x, e);
												SetColor(0, 14);
												cout << "   ";
												setCursoreAtPosition(x, e + 1);
												SetColor(0, 14);
												cout << "   ";
											}
										}
									}
								}
								break;

							}
							case 77:
							{
								if (nap == 1)
								{
									if (x != 65)
									{
										for (e = x; e < x + 6; e = e + 3)
										{
											i = (e - 40) / 3;
											j = y / 2;
											setCursoreAtPosition(e, y);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
											setCursoreAtPosition(e, y + 1);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
										}
										x = x + 3;
										for (e = x; e < x + 6; e = e + 3)
										{
											setCursoreAtPosition(e, y);
											SetColor(0, 14);
											cout << "   ";
											setCursoreAtPosition(e, y + 1);
											SetColor(0, 14);
											cout << "   ";
										}
									}
								}
								else
								{
									if (x != 68)
									{
										for (e = y; e < y + 4; e = e + 2)
										{
											i = (x - 40) / 3;
											j = e / 2;
											setCursoreAtPosition(x, e);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
											setCursoreAtPosition(x, e + 1);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
										}
										x = x + 3;
										for (e = y; e < y + 4; e = e + 2)
										{
											setCursoreAtPosition(x, e);
											SetColor(0, 14);
											cout << "   ";
											setCursoreAtPosition(x, e + 1);
											SetColor(0, 14);
											cout << "   ";
										}
									}
								}
								break;
							}
							case 80:
							{
								if (nap == 1)
								{
									if (y != 19)
									{
										for (e = x; e < x + 6; e = e + 3)
										{
											i = (e - 40) / 3;
											j = y / 2;
											setCursoreAtPosition(e, y);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
											setCursoreAtPosition(e, y + 1);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
										}
										y = y + 2;
										for (e = x; e < x + 6; e = e + 3)
										{
											setCursoreAtPosition(e, y);
											SetColor(0, 14);
											cout << "   ";
											setCursoreAtPosition(e, y + 1);
											SetColor(0, 14);
											cout << "   ";
										}
									}
								}
								else
								{
									if (y != 17)
									{
										for (e = y; e < y + 4; e = e + 2)
										{
											i = (x - 40) / 3;
											j = e / 2;
											setCursoreAtPosition(x, e);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
											setCursoreAtPosition(x, e + 1);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
										}
										y = y + 2;
										for (e = y; e < y + 4; e = e + 2)
										{
											setCursoreAtPosition(x, e);
											SetColor(0, 14);
											cout << "   ";
											setCursoreAtPosition(x, e + 1);
											SetColor(0, 14);
											cout << "   ";
										}
									}
								}
								break;
							}
							case 75:
							{ if (nap == 1)
							{
								if (x != 41)
								{
									for (e = x; e < x + 6; e = e + 3)
									{
										i = (e - 40) / 3;
										j = y / 2;
										setCursoreAtPosition(e, y);
										if (_my_pole[i][j] == 1)
										{
											SetColor(0, 12);
											cout << "   ";
										}
										else
										{
											if ((i + j) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
										}
										setCursoreAtPosition(e, y + 1);
										if (_my_pole[i][j] == 1)
										{
											SetColor(0, 12);
											cout << "   ";
										}
										else
										{
											if ((i + j) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
										}
									}
									x = x - 3;
									for (e = x; e < x + 6; e = e + 3)
									{
										setCursoreAtPosition(e, y);
										SetColor(0, 14);
										cout << "   ";
										setCursoreAtPosition(e, y + 1);
										SetColor(0, 14);
										cout << "   ";
									}
								}
							}
							else {
								if (x != 41) {
									for (e = y; e < y + 4; e = e + 2)
									{
										i = (x - 40) / 3;
										j = e / 2;
										setCursoreAtPosition(x, e);
										if (_my_pole[i][j] == 1)
										{
											SetColor(0, 12);
											cout << "   ";
										}
										else
										{
											if ((i + j) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
										}
										setCursoreAtPosition(x, e + 1);
										if (_my_pole[i][j] == 1)
										{
											SetColor(0, 12);
											cout << "   ";
										}
										else
										{
											if ((i + j) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
										}
									}
									x = x - 3;
									for (e = y; e < y + 4; e = e + 2)
									{
										setCursoreAtPosition(x, e);
										SetColor(0, 14);
										cout << "   ";
										setCursoreAtPosition(x, e + 1);
										SetColor(0, 14);
										cout << "   ";
									}
								}
							}
							break;
							}
							}
						}
						else
						{
							switch (code)
							{
							case 32:
							{
								if (nap == 1 && y < 19 || nap == -1 && x < 68)
								{
									nap = nap*(-1);
									if (nap == 1)
									{
										for (e = y; e < y + 4; e = e + 2)
										{
											i = (x - 40) / 3;
											j = e / 2;
											setCursoreAtPosition(x, e);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
											setCursoreAtPosition(x, e + 1);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
										}
										for (e = x; e < x + 6; e = e + 3)
										{
											setCursoreAtPosition(e, y);
											SetColor(0, 14);
											cout << "   ";
											setCursoreAtPosition(e, y + 1);
											SetColor(0, 14);
											cout << "   ";
										}
									}
									else
									{
										for (e = x; e < x + 6; e = e + 3)
										{
											i = (e - 40) / 3;
											j = y / 2;
											setCursoreAtPosition(e, y);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
											setCursoreAtPosition(e, y + 1);
											if (_my_pole[i][j] == 1)
											{
												SetColor(0, 12);
												cout << "   ";
											}
											else
											{
												if ((i + j) % 2 != 0)
												{
													SetColor(0, 1);
													cout << "   ";
												}
												else
												{
													SetColor(0, 9);
													cout << "   ";
												}
											}
										}

										for (e = y; e < y + 4; e = e + 2)
										{
											setCursoreAtPosition(x, e);
											SetColor(0, 14);
											cout << "   ";
											setCursoreAtPosition(x, e + 1);
											SetColor(0, 14);
											cout << "   ";
										}
									}
								}
								break;
							}
							case 13:
							{
								int pr = f = 0;
								if (nap == 1)
								{
									for (e = x - 3; e <= x + 6; e = e + 3)
									{
										for (int a = y - 2; a <= y + 2; a = a + 2)
										{
											i = (e - 40) / 3;
											j = a / 2;
											if (i < 10 && j < 10)
											{
												if (_my_pole[i][j] == 1)
												{
													pr = 1;
												}
											}
										}
									}
									if (pr == 0)
									{
										for (e = x; e < x + 6; e = e + 3)
										{
											i = (e - 40) / 3;
											j = y / 2;
											_my_pole[i][j] = 1;
											f = 1;
										}
									}
								}
								else
								{
									for (e = y - 2; e <= y + 4; e = e + 2)
									{
										for (int a = x - 3; a <= x + 3; a = a + 3)
										{
											i = (a - 40) / 3;
											j = e / 2;
											if (i < 10 && j < 10)
											{
												if (_my_pole[i][j] == 1)
												{
													pr = 1;
												}
											}
										}
									}
									if (pr == 0)
										for (e = y; e < y + 4; e = e + 2)
										{
											i = (x - 40) / 3;
											j = e / 2;
											_my_pole[i][j] = 1; f = 1;
										}
								}

								break;
							}

							case 27:
							{
								f = 1;
								ui = 1;
								break;
							}
							}
						}

					} while (f != 1);
				}
			}
			break;
		}

		case 4:
		{
			for (w = 0; w < 4; w++)
			{
				if (ui == 0)
				{
					for (i = 0, x = 41; i < 10, x < 71; i++, x = x + 3)
					{
						for (j = 0, y = 1; j < 10, y < 21; j++, y = y + 2)
						{
							setCursoreAtPosition(x, y);
							if (_my_pole[i][j] == 1)
							{
								SetColor(0, 12);
								cout << "   ";
							}
							else
							{
								if ((j + i) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{
									SetColor(0, 9);
									cout << "   ";
								}
							}
							setCursoreAtPosition(x, y + 1);
							if (_my_pole[i][j] == 1)
							{
								SetColor(0, 12);
								cout << "   ";
							}
							else
							{
								if ((j + i) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{
									SetColor(0, 9);
									cout << "   ";
								}
							}
						}
					}
					x = 41; y = 1;
					i = j = 0;
					e = x;
					{
						setCursoreAtPosition(e, y);
						SetColor(0, 14);
						cout << "   ";
						setCursoreAtPosition(e, y + 1);
						SetColor(0, 14);
						cout << "   ";
					}
					do {
						f = 0;
						int code = _getch();
						if (code == 224)
						{
							code = _getch();
							switch (code)
							{
							case 72:
							{
								if (y != 1)
								{
									e = x;
									{
										i = (e - 40) / 3;
										j = y / 2;
										setCursoreAtPosition(e, y);
										if (_my_pole[i][j] == 1)
										{
											SetColor(0, 12);
											cout << "   ";
										}
										else
										{
											if ((i + j) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
										}
										setCursoreAtPosition(e, y + 1);
										if (_my_pole[i][j] == 1)
										{
											SetColor(0, 12);
											cout << "   ";
										}
										else
										{
											if ((i + j) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
										}
									}
									y = y - 2;
									e = x;
									{
										setCursoreAtPosition(e, y);
										SetColor(0, 14);
										cout << "   ";
										setCursoreAtPosition(e, y + 1);
										SetColor(0, 14);
										cout << "   ";
									}
								}
								break;
							}
							case 77:
							{
								if (x != 68)
								{
									e = x;
									{
										i = (e - 40) / 3;
										j = y / 2;
										setCursoreAtPosition(e, y);
										if (_my_pole[i][j] == 1)
										{
											SetColor(0, 12);
											cout << "   ";
										}
										else
										{
											if ((i + j) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
										}
										setCursoreAtPosition(e, y + 1);
										if (_my_pole[i][j] == 1)
										{
											SetColor(0, 12);
											cout << "   ";
										}
										else
										{
											if ((i + j) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
										}
									}
									x = x + 3;
									e = x;
									{
										setCursoreAtPosition(e, y);
										SetColor(0, 14);
										cout << "   ";
										setCursoreAtPosition(e, y + 1);
										SetColor(0, 14);
										cout << "   ";
									}
								}
								break;
							}
							case 80:
							{
								if (y != 19)
								{
									e = x;
									{
										i = (e - 40) / 3;
										j = y / 2;
										setCursoreAtPosition(e, y);
										if (_my_pole[i][j] == 1)
										{
											SetColor(0, 12);
											cout << "   ";
										}
										else
										{
											if ((i + j) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
										}
										setCursoreAtPosition(e, y + 1);
										if (_my_pole[i][j] == 1)
										{
											SetColor(0, 12);
											cout << "   ";
										}
										else
										{
											if ((i + j) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
										}
									}
									y = y + 2;
									e = x;
									setCursoreAtPosition(e, y);
									SetColor(0, 14);
									cout << "   ";
									setCursoreAtPosition(e, y + 1);
									SetColor(0, 14);
									cout << "   ";
								}
								break;
							}
							case 75:
							{
								if (x != 41)
								{
									e = x;

									i = (e - 40) / 3;
									j = y / 2;
									setCursoreAtPosition(e, y);
									if (_my_pole[i][j] == 1)
									{
										SetColor(0, 12);
										cout << "   ";
									}
									else
									{
										if ((i + j) % 2 != 0)
										{
											SetColor(0, 1);
											cout << "   ";
										}
										else
										{
											SetColor(0, 9);
											cout << "   ";
										}
									}
									setCursoreAtPosition(e, y + 1);
									if (_my_pole[i][j] == 1)
									{
										SetColor(0, 12);
										cout << "   ";
									}
									else
									{
										if ((i + j) % 2 != 0)
										{
											SetColor(0, 1);
											cout << "   ";
										}
										else
										{
											SetColor(0, 9);
											cout << "   ";
										}
									}
									x = x - 3;
									e = x;
									{
										setCursoreAtPosition(e, y);
										SetColor(0, 14);
										cout << "   ";
										setCursoreAtPosition(e, y + 1);
										SetColor(0, 14);
										cout << "   ";
									}
								}
								break;
							}
							}
						}
						else
						{
							switch (code)
							{
							case 13:
							{
								int pr = f = 0;
								for (e = x - 3; e <= x + 3; e = e + 3)
								{
									for (int a = y - 2; a <= y + 2; a = a + 2)
									{
										i = (e - 40) / 3;
										j = a / 2;
										if (i < 10 && j < 10)
										{
											if (_my_pole[i][j] == 1)
											{
												pr = 1;
											}
										}
									}
								}
								if (pr == 0)
								{
									for (e = x; e < x + 3; e = e + 3)
									{
										i = (e - 40) / 3;
										j = y / 2;
										_my_pole[i][j] = 1;
										f = 1;
									}
								}
								break;
							}
							case 27:
							{
								f = 1;
								ui = 1;
								break;
							}
							break;
							}
						}

					} while (f != 1);
				}
			}
			break;
		}

		break;
		}
	}
	return ui;
}

int FieldView::comp(int _my_pole[10][10], int udar, int ud[2], int hod[1])
{

	int per, n, m, k, h;
	int pri, prj;

	srand(time(NULL));
	setCursoreAtPosition(29, 22);
	SetColor(15, 0);
	cout << "Computer shoots";
	do {
		f = 1;
		per = 0;
		k = 0;
		setCursoreAtPosition(34, 24);;
		SetColor(15, 0);
		cout << "      ";
		Sleep(1000);

		h = 0; 
		if (hod[0] == 5)
		{
			for (n = ud[0] - 1; n <= ud[0] + 1 && n < 10; n++)
			{
				for (m = ud[1] - 1; m <= ud[1] + 1 && m < 10; m++)
				{
					if (_my_pole[n][m] == 1)
					{
						h = 1;
					}
				}
			}
			if (h == 0)
			{
				_my_pole[ud[0]][ud[1]] = 5;
				for (n = ud[0] - 1; n <= ud[0] + 1 && n < 10; n++)
				{
					for (m = ud[1] - 1; m <= ud[1] + 1 && m < 10; m++)
					{
						if (_my_pole[n][m] == 0)
						{
							_my_pole[n][m] = 3;
						}
					}
				}
			}
			if (h == 1)
			{
				per = 1;
				srand(time(NULL));
				do {
					pri = 1 + rand() % 4;
					prj = 0;
					switch (pri)
					{
					case 1:
					{
						if (_my_pole[ud[0] - 1][ud[1]] == 0 && ud[0] != 0)
						{
							_my_pole[ud[0] - 1][ud[1]] = 3;
							setCursoreAtPosition(34, 24);
							SetColor(15, 0);
							Sleep(1000);
							cout << "Missed!";
							prj = 1;
							per = 1;
							f = 1;
						}
						if (_my_pole[ud[0] - 1][ud[1]] == 1 && ud[0] != 0)
						{
							_my_pole[ud[0] - 1][ud[1]] = 4;
							setCursoreAtPosition(34, 24);
							SetColor(15, 0);
							cout << "Hit!";
							udar++;
							Sleep(1000);
							cout << "\x07";
							f = 0;
							prj = 1;
							per = 1;
							hod[0] = 1;
						}
						break;
					}
					case 2:
					{
						if (_my_pole[ud[0] + 1][ud[1]] == 0 && ud[0] != 9)
						{
							_my_pole[ud[0] + 1][ud[1]] = 3;
							setCursoreAtPosition(34, 24);
							SetColor(15, 0); Sleep(1000);
							cout << "Missed!";
							prj = 1;
							per = 1;
							f = 1;
						}
						if (_my_pole[ud[0] + 1][ud[1]] == 1 && ud[0] != 9)
						{
							_my_pole[ud[0] + 1][ud[1]] = 4;
							setCursoreAtPosition(34, 24);
							SetColor(15, 0);
							cout << "Hit!";
							udar++;
							Sleep(1000);
							cout << "\x07";
							f = 0;
							prj = 1;
							per = 1;
							hod[0] = 1;
						}
						break;
					}
					case 3:
					{
						if (_my_pole[ud[0]][ud[1] - 1] == 0 && ud[1] != 0)
						{
							_my_pole[ud[0]][ud[1] - 1] = 3;
							setCursoreAtPosition(34, 24);
							SetColor(15, 0);
							Sleep(1000);
							cout << "Missed!";
							prj = 1;
							per = 1;
							f = 1;
						}
						if (_my_pole[ud[0]][ud[1] - 1] == 1 && ud[1] != 0)
						{
							_my_pole[ud[0]][ud[1] - 1] = 4;
							setCursoreAtPosition(34, 24);
							SetColor(15, 0);
							cout << "Hit!";
							udar++;
							Sleep(1000);
							cout << "\x07";
							f = 0;
							prj = 1;
							per = 1;
							hod[0] = 1;
						}
						break;
					}
					case 4:
					{
						if (_my_pole[ud[0]][ud[1] + 1] == 0 && ud[1] != 9)
						{
							_my_pole[ud[0]][ud[1] + 1] = 3;
							setCursoreAtPosition(34, 24);
							SetColor(15, 0);
							Sleep(1000);
							cout << "Missed!";
							prj = 1;
							per = 1;
							f = 1;
						}
						if (_my_pole[ud[0]][ud[1] + 1] == 1 && ud[1] != 9)
						{
							_my_pole[ud[0]][ud[1] + 1] = 4;
							setCursoreAtPosition(34, 24);
							SetColor(15, 0);
							cout << "Hit!";
							udar++;
							Sleep(1000);
							cout << "\x07";
							f = 0;
							prj = 1;
							per = 1;
							hod[0] = 1;
						}
						break;
					}
					}
				} while (prj == 0);
			}
		}

		if (hod[0] == 1)
		{
			for (i = 0; i < 10; i++)
			{
				for (j = 0; j < 10; j++)
				{
					h = 0;
					if (_my_pole[i][j] == 4 || _my_pole[i][j] == 5)
					{
						_my_pole[i][j] = 5;
						if (i > 0)
						{
							if (_my_pole[i - 1][j] == 1)
							{
								h = 1;
								_my_pole[i - 1][j] = 5;
								setCursoreAtPosition(34, 24);
								SetColor(15, 0);
								cout << "Hit!";
								Sleep(1000);
								cout << "\x07";
								for (i = 0, x = 41; i < 10, x < 71; i++, x = x + 3)
								{
									for (j = 0, y = 1; j < 10, y < 21; j++, y = y + 2)
									{
										setCursoreAtPosition(x, y);
										switch (_my_pole[i][j])
										{
										case 0:
										{
											if ((j + i) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
											break;
										}
										case 1:
										{
											SetColor(0, 12);
											cout << "   ";
											break;
										}
										case 2:
										{
											SetColor(0, 7);
											cout << "   ";
											break;
										}
										case 3:
										{
											SetColor(0, 11);
											cout << "   ";
											break;
										}
										case 4:
										{
											SetColor(0, 7);
											cout << "   ";
											break;
										}
										case 5:
										{
											SetColor(0, 7);
											cout << "   ";
											break;
										}
										}

										setCursoreAtPosition(x, y + 1);
										switch (_my_pole[i][j])
										{
										case 0:
										{
											if ((j + i) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
											break;
										}
										case 1:
										{
											SetColor(0, 12);
											cout << "   ";
											break;
										}
										case 2:
										{
											SetColor(0, 7);
											cout << "   ";
											break;
										}
										case 3:
										{
											SetColor(0, 11);
											cout << "   ";
											break;
										}
										case 4:
										{
											SetColor(0, 7);
											cout << "   ";
											break;
										}
										case 5:
										{
											SetColor(0, 7);
											cout << "   ";
											break;
										}
										}
									}
								}
							}
						}
						if (i < 9)
						{
							if (_my_pole[i + 1][j] == 1)
							{
								h = 1;
								_my_pole[i + 1][j] = 5;
								setCursoreAtPosition(34, 24);
								SetColor(15, 0);
								cout << "Hit!";
								Sleep(1000);
								cout << "\x07";

								for (i = 0, x = 41; i < 10, x < 71; i++, x = x + 3)
								{
									for (j = 0, y = 1; j < 10, y < 21; j++, y = y + 2)
									{
										setCursoreAtPosition(x, y);
										switch (_my_pole[i][j])
										{
										case 0:
										{
											if ((j + i) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
											break;
										}
										case 1:
										{
											SetColor(0, 12);
											cout << "   ";
											break;
										}
										case 2:
										{
											SetColor(0, 7);
											cout << "   ";
											break;
										}
										case 3:
										{
											SetColor(0, 11);
											cout << "   ";
											break;
										}
										case 4:
										{
											SetColor(0, 7);
											cout << "   ";
											break;
										}
										case 5:
										{
											SetColor(0, 7);
											cout << "   ";
											break;
										}
										}
										setCursoreAtPosition(x, y + 1);
										switch (_my_pole[i][j])
										{
										case 0:
										{
											if ((j + i) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
											break;
										}
										case 1:
										{
											SetColor(0, 12);
											cout << "   ";
											break;
										}
										case 2:
										{
											SetColor(0, 7);
											cout << "   ";
											break;
										}
										case 3:
										{
											SetColor(0, 11);
											cout << "   ";
											break;
										}
										case 4:
										{
											SetColor(0, 7);
											cout << "   ";
											break;
										}
										case 5:
											SetColor(0, 7);
											cout << "   ";
											break;
										}
									}
								}
							}
						}
						if (j > 0) {
							if (_my_pole[i][j - 1] == 1)
							{
								h = 1;
								_my_pole[i][j - 1] = 5;
								setCursoreAtPosition(34, 24);;
								SetColor(15, 0);
								cout << "Hit!";
								Sleep(1000);
								cout << "\x07";
								for (i = 0, x = 41; i < 10, x < 71; i++, x = x + 3)
								{
									for (j = 0, y = 1; j < 10, y < 21; j++, y = y + 2)
									{
										setCursoreAtPosition(x, y);
										switch (_my_pole[i][j])
										{
										case 0:
											if ((j + i) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
											break;
										case 1:
											SetColor(0, 12);
											cout << "   ";
											break;
										case 2:
											SetColor(0, 7);
											cout << "   ";
											break;
										case 3:
											SetColor(0, 11);
											cout << "   ";
											break;
										case 4:
											SetColor(0, 7);
											cout << "   ";
											break;
										case 5:
											SetColor(0, 7);
											cout << "   ";
											break;
										}
										setCursoreAtPosition(x, y + 1);
										switch (_my_pole[i][j])
										{
										case 0:
											if ((j + i) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
											break;
										case 1:
											SetColor(0, 12);
											cout << "   ";
											break;
										case 2:
											SetColor(0, 7);
											cout << "   ";
											break;
										case 3:
											SetColor(0, 11);
											cout << "   ";
											break;
										case 4:
											SetColor(0, 7);
											cout << "   ";
											break;
										case 5:
											SetColor(0, 7);
											cout << "   ";
											break;
										}
									}
								}
							}
						}
						if (j < 9) {
							if (_my_pole[i][j + 1] == 1)
							{
								h = 1;
								_my_pole[i][j + 1] = 5;
								setCursoreAtPosition(34, 24);;
								SetColor(15, 0);
								cout << "Hit!";
								Sleep(1000);
								cout << "\x07";
								for (i = 0, x = 41; i < 10, x < 71; i++, x = x + 3)
								{
									for (j = 0, y = 1; j < 10, y < 21; j++, y = y + 2)
									{
										setCursoreAtPosition(x, y);
										switch (_my_pole[i][j])
										{
										case 0:
											if ((j + i) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
											break;
										case 1:
											SetColor(0, 12);
											cout << "   ";
											break;
										case 2:
											SetColor(0, 7);
											cout << "   ";
											break;
										case 3:
											SetColor(0, 11);
											cout << "   ";
											break;
										case 4:
											SetColor(0, 7);
											cout << "   ";
											break;
										case 5:
											SetColor(0, 7);
											cout << "   ";
											break;
										}
										setCursoreAtPosition(x, y + 1);
										switch (_my_pole[i][j])
										{
										case 0:
											if ((j + i) % 2 != 0)
											{
												SetColor(0, 1);
												cout << "   ";
											}
											else
											{
												SetColor(0, 9);
												cout << "   ";
											}
											break;
										case 1:
											SetColor(0, 12);
											cout << "   ";
											break;
										case 2:
											SetColor(0, 7);
											cout << "   ";
											break;
										case 3:
											SetColor(0, 11);
											cout << "   ";
											break;
										case 4:
											SetColor(0, 7);
											cout << "   ";
											break;
										case 5:
											SetColor(0, 7);
											cout << "   ";
											break;
										}
									}
								}
							}
						}
					}
				}
			}

			for (i = 0; i < 10; i++)
			{
				for (j = 0; j < 10; j++)
				{
					h = 0;
					if (_my_pole[i][j] == 5)
					{
						if (i > 0)
						{
							if (_my_pole[i - 1][j] == 0)
							{
								h = 1;
								_my_pole[i - 1][j] = 3;
							}
						}
						if (i < 9)
						{
							if (_my_pole[i + 1][j] == 0)
							{
								h = 1;
								_my_pole[i + 1][j] = 3;
							}
						}
						if (j > 0)
						{
							if (_my_pole[i][j - 1] == 0)
							{
								h = 1;
								_my_pole[i][j - 1] = 3;
							}
						}
						if (j < 9)
						{
							if (_my_pole[i][j + 1] == 0)
							{
								h = 1;
								_my_pole[i][j + 1] = 3;
							}
						}
						if (i > 0 && j > 0)
						{
							if (_my_pole[i - 1][j - 1] == 0)
							{
								h = 1;
								_my_pole[i - 1][j - 1] = 3;
							}
						}
						if (i > 0 && j < 9)
						{
							if (_my_pole[i - 1][j + 1] == 0)
							{
								h = 1;
								_my_pole[i - 1][j + 1] = 3;
							}
						}
						if (i < 9 && j < 9)
						{
							if (_my_pole[i + 1][j + 1] == 0)
							{
								h = 1;
								_my_pole[i + 1][j + 1] = 3;
							}
						}
						if (i < 9 && j>0)
						{
							if (_my_pole[i + 1][j - 1] == 0)
							{
								h = 1;
								_my_pole[i + 1][j - 1] = 3;
							}
						}
					}
				}
			}
		}

		udar = 0;
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (_my_pole[i][j] == 4 || _my_pole[i][j] == 5)
				{
					udar++;
				}
			}
		}

		if (udar == 20)
		{
			f = 1;
			per = 1;
		}

		for (i = 0, x = 41; i < 10, x < 71; i++, x = x + 3)
		{
			for (j = 0, y = 1; j < 10, y < 21; j++, y = y + 2)
			{
				setCursoreAtPosition(x, y);
				switch (_my_pole[i][j])
				{
				case 0:
					if ((j + i) % 2 != 0)
					{
						SetColor(0, 1);
						cout << "   ";
					}
					else
					{
						SetColor(0, 9);
						cout << "   ";
					}
					break;
				case 1:
					SetColor(0, 12);
					cout << "   ";
					break;
				case 2:
					SetColor(0, 7);
					cout << "   ";
					break;
				case 3:
					SetColor(0, 11);
					cout << "   ";
					break;
				case 4:
					SetColor(0, 7);
					cout << "   ";
					break;
				case 5:
					SetColor(0, 7);
					cout << "   ";
					break;
				}
				setCursoreAtPosition(x, y + 1);
				switch (_my_pole[i][j])
				{
				case 0:
					if ((j + i) % 2 != 0)
					{
						SetColor(0, 1);
						cout << "   ";
					}
					else
					{
						SetColor(0, 9);
						cout << "   ";
					}
					break;
				case 1:
					SetColor(0, 12);
					cout << "   ";
					break;
				case 2:
					SetColor(0, 7);
					cout << "   ";
					break;
				case 3:
					SetColor(0, 11);
					cout << "   ";
					break;
				case 4:
					SetColor(0, 7);
					cout << "   ";
					break;
				case 5:
					SetColor(0, 7);
					cout << "   ";
					break;
				}
				}
			}
		
		if (per == 0)
		{
			do {
				i = 0 + rand() % 10;
				j = 0 + rand() % 10;
			} while (_my_pole[i][j] > 1);
			if (_my_pole[i][j] == 1) 
			{
				_my_pole[i][j] = 4;
				ud[0] = i;
				ud[1] = j; 
				setCursoreAtPosition(34, 24);;
				SetColor(15, 0);
				cout << "Hit!"; 
				hod[0] = 5; 
				Sleep(1000);
				cout << "\x07";
				f = 0;
			}

			if (_my_pole[i][j] == 0)
			{ 
				_my_pole[i][j] = 3;
				f = 1;
				setCursoreAtPosition(34, 24);;
				SetColor(15, 0); 
				cout << "Missed!";
				Sleep(1000);
			}

		}

		Sleep(1000);
		for (i = 0, x = 41; i < 10, x < 71; i++, x = x + 3)
		{
			for (j = 0, y = 1; j < 10, y < 21; j++, y = y + 2)
			{

				setCursoreAtPosition(x, y);
				switch (_my_pole[i][j])
				{
				case 0:
					if ((j + i) % 2 != 0)
					{
						SetColor(0, 1);
						cout << "   ";
					}
					else
					{
						SetColor(0, 9);
						cout << "   ";
					}
					break;
				case 1:
					SetColor(0, 12);
					cout << "   ";
					break;
				case 2:
					SetColor(0, 7);
					cout << "   ";
					break;
				case 3:
					SetColor(0, 11);
					cout << "   ";
					break;
				case 4:
					SetColor(0, 7);
					cout << "   ";
					break;
				case 5:
					SetColor(0, 7);
					cout << "   ";
					break;
				}
				setCursoreAtPosition(x, y + 1);
				switch (_my_pole[i][j])
				{
				case 0:
					if ((j + i) % 2 != 0)
					{
						SetColor(0, 1);
						cout << "   ";
					}
					else
					{
						SetColor(0, 9);
						cout << "   ";
					}
					break;
				case 1:
					SetColor(0, 12);
					cout << "   ";
					break;
				case 2:
					SetColor(0, 7);
					cout << "   ";
					break;
				case 3:
					SetColor(0, 11);
					cout << "   ";
					break;
				case 4:
					SetColor(0, 7);
					cout << "   ";
					break;
				case 5:
					SetColor(0, 7);
					cout << "   ";
					break;
				}
			}
		}
	} while (f == 0);

	return udar;
}

int FieldView::player(int _pole[10][10], int udar)
{
	setCursoreAtPosition(34, 24);;
	SetColor(0, 0);
	cout << "         ";
	int k = 0, pop, iper, jper;
	int end;
	for (i = 0, x = 1; i < 10, x < 31; i++, x = x + 3)
	{
		for (j = 0, y = 1; j < 10, y < 21; j++, y = y + 2)
		{
			setCursoreAtPosition(x, y);
			if (_pole[i][j] == 3)
			{ 
				SetColor(0, 11); 
				cout << "   ";
			}
			else
			{ 
				if (_pole[i][j] == 2) 
				{
					SetColor(0, 12);
					cout << "   ";
				}
				else
				{
					if ((j + i) % 2 != 0)
					{ 
						SetColor(0, 1); 
						cout << "   ";
					} 
					else 
					{
						SetColor(0, 9);
						cout << "   "; 
					} 
				} 
			}
			setCursoreAtPosition(x, y + 1);
			if (_pole[i][j] == 3)
			{
				SetColor(0, 11);
				cout << "   ";
			}
			else
			{
				if (_pole[i][j] == 2) 
				{ 
					SetColor(0, 12);
					cout << "   "; 
				} 
				else 
				{ 
					if ((j + i) % 2 != 0)
					{ 
						SetColor(0, 1);
						cout << "   ";
					} 
					else 
					{
						SetColor(0, 9); 
						cout << "   ";
					} 
				} 
			}
		}
	}
	x = 1;
	y = 1;
	i = j = 0;
	e = x;
	{

		setCursoreAtPosition(e, y); 
		SetColor(0, 14);
		cout << "   ";
		setCursoreAtPosition(e, y + 1);
		SetColor(0, 14); 
		cout << "   ";
	}
	do {
		f = 0;
		pop = 0;
		setCursoreAtPosition(29, 22);
		SetColor(15, 0);
		cout << " Player shoots ";
		int code = _getch();
		if (code == 224)
		{
			setCursoreAtPosition(34, 24);;
			SetColor(0, 0);
			cout << "          ";
			code = _getch();
			switch (code)
			{
			case 72://verx
			{
				if (y != 1)
				{
					e = x;
					{
						i = e / 3;
						j = y / 2;
						setCursoreAtPosition(e, y);
						if (_pole[i][j] == 3)
						{
							SetColor(0, 11);
							cout << "   ";
						}
						else
						{
							if (_pole[i][j] == 2)
							{
								SetColor(0, 12);
								cout << "   ";
							}
							else
							{
								if ((i + j) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{
									SetColor(0, 9);
									cout << "   ";
								}
							}
						}
						setCursoreAtPosition(e, y + 1);
						if (_pole[i][j] == 3)
						{
							SetColor(0, 11);
							cout << "   ";
						}
						else
						{
							if (_pole[i][j] == 2)
							{
								SetColor(0, 12);
								cout << "   ";
							}
							else
							{
								if ((i + j) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{
									SetColor(0, 9);
									cout << "   ";
								}
							}
						}
					}
					y = y - 2;
					e = x;
					{
						setCursoreAtPosition(e, y);
						SetColor(0, 14);
						cout << "   ";
						setCursoreAtPosition(e, y + 1);
						SetColor(0, 14);
						cout << "   ";
					}
				}
				break;
			}
			case 77://vpravo
			{

				if (x != 28)
				{
					e = x;
					{
						i = e / 3;
						j = y / 2;
						setCursoreAtPosition(e, y);
						if (_pole[i][j] == 3)
						{
							SetColor(0, 11);
							cout << "   ";
						}
						else
						{
							if (_pole[i][j] == 2)
							{
								SetColor(0, 12);
								cout << "   ";
							}
							else
							{
								if ((i + j) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{
									SetColor(0, 9);
									cout << "   ";
								}
							}
						}
						setCursoreAtPosition(e, y + 1);
						if (_pole[i][j] == 3)
						{
							SetColor(0, 11);
							cout << "   ";
						}
						else
						{
							if (_pole[i][j] == 2)
							{
								SetColor(0, 12);
								cout << "   ";
							}
							else
							{
								if ((i + j) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{
									SetColor(0, 9);
									cout << "   ";
								}
							}
						}
					}
					x = x + 3;
					e = x;
					{
						setCursoreAtPosition(e, y);
						SetColor(0, 14);
						cout << "   ";
						setCursoreAtPosition(e, y + 1);
						SetColor(0, 14);
						cout << "   ";
					}
				}
				break;
			}
			case 80://vnys
			{
				if (y != 19)
				{
					e = x;
					{
						i = e / 3;
						j = y / 2;
						setCursoreAtPosition(e, y);
						if (_pole[i][j] == 3)
						{
							SetColor(0, 11);
							cout << "   ";
						}
						else
						{
							if (_pole[i][j] == 2)
							{
								SetColor(0, 12);
								cout << "   ";
							}
							else
							{
								if ((i + j) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{
									SetColor(0, 9);
									cout << "   ";
								}
							}
						}
						setCursoreAtPosition(e, y + 1);
						if (_pole[i][j] == 3)
						{
							SetColor(0, 11);
							cout << "   ";
						}
						else
						{
							if (_pole[i][j] == 2)
							{
								SetColor(0, 12);
								cout << "   ";
							}
							else
							{
								if ((i + j) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{
									SetColor(0, 9);
									cout << "   ";
								}
							}
						}
					}
					y = y + 2;
					e = x;
					{
						setCursoreAtPosition(e, y);
						SetColor(0, 14);
						cout << "   ";
						setCursoreAtPosition(e, y + 1);
						SetColor(0, 14);
						cout << "   ";
					}
				}
				break;
			}
			case 75://vlivo
			{
				if (x != 1)
				{
					e = x;
					{
						i = e / 3;
						j = y / 2;
						setCursoreAtPosition(e, y);
						if (_pole[i][j] == 3)
						{
							SetColor(0, 11);
							cout << "   ";
						}
						else
						{
							if (_pole[i][j] == 2)
							{
								SetColor(0, 12);
								cout << "   ";
							}
							else
							{
								if ((i + j) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{
									SetColor(0, 9);
									cout << "   ";
								}
							}
						}
						setCursoreAtPosition(e, y + 1);
						if (_pole[i][j] == 3)
						{
							SetColor(0, 11);
							cout << "   ";
						}
						else
						{
							if (_pole[i][j] == 2)
							{
								SetColor(0, 12);
								cout << "   ";
							}
							else
							{
								if ((i + j) % 2 != 0)
								{
									SetColor(0, 1);
									cout << "   ";
								}
								else
								{
									SetColor(0, 9);
									cout << "   ";
								}
							}
						}
					}
					x = x - 3;
					e = x;
					{
						setCursoreAtPosition(e, y);
						SetColor(0, 14);
						cout << "   ";
						setCursoreAtPosition(e, y + 1);
						SetColor(0, 14);
						cout << "   ";
					}
				}
				break;
			}
			}
		}
		else
		{
			switch (code)
			{
			case 13:
			{
				int pr = f = 0;
				pop = 0;
				e = x;
				int a = y;

				i = e / 3;
				j = a / 2;
				if (i < 10 && j < 10)
				{
					if (_pole[i][j] == 2 || _pole[i][j] == 3)
					{
						pr = 1;
					}
				}
				if (pr == 0)
				{
					e = x;

					i = e / 3;
					j = y / 2;
					if (_pole[i][j] == 0)
					{
						_pole[i][j] = 3;
						f = 1;
						setCursoreAtPosition(34, 24);
						SetColor(15, 0);
						cout << "Missed";
					}
					else
					{
						_pole[i][j] = 2;
						cout << "\x07";
						setCursoreAtPosition(34, 24);
						SetColor(15, 0);
						cout << "Hit!";
						pop = 1;
						udar++;
					}
				}
				break;
			}
			case 27:
			{
				MainOption main;
				main.draw();
				break;
			}
			}

			int mas[20][2], sh = 0, a, b;
			for (i = 0; i < 10; i++)
			{
				for (j = 0; j < 10; j++)
				{
					if (_pole[i][j] == 1)
					{
						if (i > 0)
						{
							if (_pole[i - 1][j] == 2)
							{
								mas[sh][0] = i - 1;
								mas[sh][1] = j;
								sh++;
								if (i > 1)
								{
									if (_pole[i - 2][j] == 2)
									{
										mas[sh][0] = i - 2;
										mas[sh][1] = j;
										sh++;
										if (i > 2)
										{
											if (_pole[i - 3][j] == 2)
											{
												mas[sh][0] = i - 3;
												mas[sh][1] = j;
												sh++;
											}
										}
									}
								}
							}
						}

						if (i < 9)
						{
							if (_pole[i + 1][j] == 2)
							{
								mas[sh][0] = i + 1; mas[sh][1] = j; sh++;
								if (i < 8)
								{
									if (_pole[i + 2][j] == 2)
									{
										mas[sh][0] = i + 2;
										mas[sh][1] = j;
										sh++;
										if (i < 7)
										{
											if (_pole[i + 3][j] == 2)
											{
												mas[sh][0] = i + 3;
												mas[sh][1] = j;
												sh++;
											}
										}
									}
								}
							}
						}

						if (j > 0)
							if (_pole[i][j - 1] == 2)
							{
								mas[sh][0] = i;
								mas[sh][1] = j - 1;
								sh++;
								if (j > 1)
									if (_pole[i][j - 2] == 2)
									{
										mas[sh][0] = i;
										mas[sh][1] = j - 2;
										sh++;
										if (j > 2)
											if (_pole[i][j - 3] == 2)
											{
												mas[sh][0] = i;
												mas[sh][1] = j - 3;
												sh++;
											}
									}
							}

						if (j < 9)
							if (_pole[i][j + 1] == 2)
							{
								mas[sh][0] = i;
								mas[sh][1] = j + 1;
								sh++;
								if (i < 8)
									if (_pole[i][j + 2] == 2)
									{
										mas[sh][0] = i;
										mas[sh][1] = j + 2;
										sh++;
										if (i < 7)
											if (_pole[i][j + 3] == 2)
											{
												mas[sh][0] = i;
												mas[sh][1] = j + 3;
												sh++;
											}
									}
							}
					}
				}
			}
			for (i = 0; i < 10; i++)
			{
				for (j = 0; j < 10; j++)
				{
					b = 0;
					if (_pole[i][j] == 2)
					{
						for (a = 0; a < sh; a++)
						{
							if (i == mas[a][0] && j == mas[a][1])
							{
								b = 1;
							}
						}
						if (b == 0)
						{
							if (i > 0)
							{
								if (_pole[i - 1][j] == 0)
								{
									_pole[i - 1][j] = 3;
								}
							}
							if (i < 9)
							{
								if (_pole[i + 1][j] == 0)
								{
									_pole[i + 1][j] = 3;
								}
							}
							if (j > 0)
							{
								if (_pole[i][j - 1] == 0)
								{
									_pole[i][j - 1] = 3;
								}
							}
							if (j < 9)
							{
								if (_pole[i][j + 1] == 0)
								{
									_pole[i][j + 1] = 3;
								}
							}
							if (i > 0 && j > 0)
							{
								if (_pole[i - 1][j - 1] == 0)
								{
									_pole[i - 1][j - 1] = 3;
								}
							}
							if (i > 0 && j < 9)
							{
								if (_pole[i - 1][j + 1] == 0)
								{
									_pole[i - 1][j + 1] = 3;
								}
							}
							if (i < 9 && j < 9)
							{
								if (_pole[i + 1][j + 1] == 0)
								{
									_pole[i + 1][j + 1] = 3;
								}
							}
							if (i < 9 && j>0)
							{
								if (_pole[i + 1][j - 1] == 0)
								{
									_pole[i + 1][j - 1] = 3;
								}
							}
						}
					}

				}
			}
			iper = x;
			jper = y;
			setCursoreAtPosition(e, y);
			SetColor(0, 14);
			cout << "   ";
			setCursoreAtPosition(e, y + 1);
			SetColor(0, 14);
			cout << "   ";

			for (i = 0, x = 1; i < 10, x < 31; i++, x = x + 3)
			{
				for (j = 0, y = 1; j < 10, y < 21; j++, y = y + 2)
				{
					setCursoreAtPosition(x, y);
					switch (_pole[i][j])
					{
					case 0:
						if ((j + i) % 2 != 0)
						{
							SetColor(0, 1);
							cout << "   ";
						}
						else
						{
							SetColor(0, 9);
							cout << "   ";
						}
						break;
					case 1:
						if ((j + i) % 2 != 0)
						{
							SetColor(0, 1);
							cout << "   ";
						}
						else
						{
							SetColor(0, 9);
							cout << "   ";
						}
						break;
					case 2:
						SetColor(0, 12);
						cout << "   ";
						break;
					case 3:
						SetColor(0, 11);
						cout << "   ";
						break;
					}
					setCursoreAtPosition(x, y + 1);
					switch (_pole[i][j])
					{
					case 0:
						if ((j + i) % 2 != 0)
						{
							SetColor(0, 1);
							cout << "   ";
						}
						else
						{
							SetColor(0, 9);
							cout << "   ";
						}
						break;
					case 1:
						if ((j + i) % 2 != 0)
						{
							SetColor(0, 1);
							cout << "   ";
						}
						else
						{
							SetColor(0, 9);
							cout << "   ";
						}
						break;
					case 2:
						SetColor(0, 12);
						cout << "   ";
						break;
					case 3:
						SetColor(0, 11);
						cout << "   ";
						break;
					}
				}
			}
			x = iper;
			y = jper;

			udar = 0;
			for (i = 0; i < 10; i++)
			{
				for (j = 0; j < 10; j++)
				{
					if (_pole[i][j] == 2 || _pole[i][j] == 2)
					{
						udar++;
					}
				}
			}
			end = 0;
			if (udar == 20)
			{
				f = 1;
				pop = 0;
			}

			if (k == 1)
			{
				udar = -1;
				f = 1;
			}
		}
	} while ((f != 1 || pop != 0));


	return udar;
}

void FieldView::Game()
{
	int chislocomp = 0, chislomy = 0;
	SetColor(15, 0);
	system("cls");

	for (i = 0, x = 1; i < 10, x < 31; i++, x = x + 3)
	{
		for (j = 0, y = 1; j < 10, y < 21; j++, y = y + 2)
		{
			setCursoreAtPosition(x, y);  
			if ((j + i) % 2 != 0)
			{ 
				SetColor(0, 1); 
				cout << "   ";
			}
			else 
			{ 
				SetColor(0, 9); 
				cout << "   ";
			}
			setCursoreAtPosition(x, y + 1);
			if ((j + i) % 2 != 0)
			{ 
				SetColor(0, 1);
				cout << "   "; 
			}
			else
			{ 
				SetColor(0, 9);
				cout << "   ";
			}
		}
	}

	for (i = 0, x = 41; i < 10, x < 71; i++, x = x + 3)
	{
		for (j = 0, y = 1; j < 10, y < 21; j++, y = y + 2)
		{
			setCursoreAtPosition(x, y);
			if (mypole[i][j] == 1)
			{ 
				SetColor(0, 12);
				cout << "   ";
			}
			else
			{ 
				if ((j + i) % 2 != 0)
				{ 
					SetColor(0, 1);
					cout << "   "; 
				} 
				else
				{ 
					SetColor(0, 9);
					cout << "   ";
				} 
			}
			setCursoreAtPosition(x, y + 1);
			if (mypole[i][j] == 1)
			{
				SetColor(0, 12);
				cout << "   ";
			}
			else
			{ 
				if ((j + i) % 2 != 0)
				{ 
					SetColor(0, 1); 
					cout << "   ";
				} 
				else 
				{ 
					SetColor(0, 9);
					cout << "   ";
				} 
			}
		}
	}
	ud[0] = -3; 
	ud[1] = -3;
		SetColor(12, 0);
		setCursoreAtPosition(33, 0);
		cout << "SEA WAR";
		setCursoreAtPosition(9, 0);
		cout << "Computer pole";
		setCursoreAtPosition(51, 0);
		cout << "Player pole";
		SetColor(7, 0);
		setCursoreAtPosition(51, 26);
		cout << "Hit - press Enter";
		setCursoreAtPosition(51, 27);
		cout << "Exit - press ESC";
		setCursoreAtPosition(51, 28);
		cout << "Control - press arrows";
		setCursoreAtPosition(28, 21); cout << "\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xBB\n";
		setCursoreAtPosition(28, 22); cout << "\xba"; cout << "\t            "; cout << "\xba\n";
		setCursoreAtPosition(28, 23); cout << "\xba"; cout << "\t            "; cout << "\xba\n";
		setCursoreAtPosition(28, 24); cout << "\xba"; cout << "\t            "; cout << "\xba\n";
		setCursoreAtPosition(28, 25); cout << "\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xBC\n";


	while (chislocomp < 20 && chislomy < 20)
	{
		
		if (chislomy == -1) 
		{ 
			break; 
		}
		if (chislocomp != 20 && chislomy != 20)
		{
			if (first == 1)
			{
				chislocomp = comp(mypole, chislocomp, ud, hod);
				first = first*(-1);
			}
			else
			{
				chislomy = player(pole, chislomy);
				first = first*(-1);
			}
		}
	}
	SetColor(0, 0); 
	system("cls");

	if (chislocomp == 20)
	{
		setCursoreAtPosition(33, 14); 
		SetColor(0, 12);
		cout << "You lose! :(";
		_getch();
		MainOption main;
		main.draw();
	}
	if (chislomy == 20)
	{
		setCursoreAtPosition(33, 14);
		SetColor(0, 2);
		cout << "You win! :)"; 
		_getch();
		MainOption main;
		main.draw();
	}
}