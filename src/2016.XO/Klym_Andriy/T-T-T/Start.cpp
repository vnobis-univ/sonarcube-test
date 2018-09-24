
#include "Start.h"

void StartView::SetColor(int text, int background) 
	{
		SetConsoleTextAttribute(hStdOut, background * 16 + text);
	}

void StartView::gotoxy(int x,int y)
	{
	  HANDLE hConsole;
	  COORD cursorLoc;
	  std::cout.flush();
	  cursorLoc.X = x;
	  cursorLoc.Y = y;
	  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	  SetConsoleCursorPosition(hConsole, cursorLoc);
	}

StartView::StartView() 
{
		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		menu[0] = "Start";
		menu[1] = "Highscore";
		menu[2] = "Exit";
		f=1;
		a=0;
		
		
		

}

void StartView::Draw()
	{
		for(int i=0;i<80;i++)
		{
			SetColor(14,9);
			for(int j=0;j<4;j++)
				cout<<ofmenu[j][i];
			
		}
		
		gotoxy(30,10);
		SetColor(14,0);
		cout<<menu[0]<<endl;
		gotoxy(30,11);
		SetColor(2,0);
		cout<<menu[1]<<endl;
		gotoxy(30,12);
		cout<<menu[2]<<endl;
		
		cur=1;
		while (true) 
		{ 
			int k;
			k = _getch(); 
			if (k == 224) 
			{ 
				k = _getch(); 
			} 
			switch(k)
			{
			case 80:
				{
					if(f==1)
					{
						system("cls");
						for(int i=0;i<80;i++)
						{
							SetColor(14,9);
							for(int j=0;j<4;j++)
								cout<<ofmenu[j][i];
			
						}
						gotoxy(30,10);
						SetColor(2,0);
						cout<<menu[0]<<endl;
						gotoxy(30,11);
						SetColor(14,0);
						cout<<menu[1]<<endl;
						gotoxy(30,12);
						SetColor(2,0);
						cout<<menu[2]<<endl;
						f=2;
						break;
					}
					if(f==2)
					{
						system("cls");
						for(int i=0;i<80;i++)
						{
							SetColor(14,9);
							for(int j=0;j<4;j++)
								cout<<ofmenu[j][i];
			
						}
						gotoxy(30,10);
						SetColor(2,0);
						cout<<menu[0]<<endl;
						gotoxy(30,11);
						cout<<menu[1]<<endl;
						gotoxy(30,12);
						SetColor(14,0);
						cout<<menu[2]<<endl;
						f=3;
						break;
					}
					if(f==3)
					{
						system("cls");
						for(int i=0;i<80;i++)
						{
							SetColor(14,9);
							for(int j=0;j<4;j++)
								cout<<ofmenu[j][i];
			
						}
						gotoxy(30,10);
						SetColor(14,0);
						cout<<menu[0]<<endl;
						SetColor(2,0);
						gotoxy(30,11);
						cout<<menu[1]<<endl;
						gotoxy(30,12);
						cout<<menu[2]<<endl;
						f=1;
						break;
					}
					break;
				}
			case 72:
				{
					if(f==1)
					{
						system("cls");
						gotoxy(30,10);
						SetColor(2,0);
						cout<<menu[0]<<endl;
						gotoxy(30,11);
						cout<<menu[1]<<endl;
						SetColor(14,0);
						gotoxy(30,12);
						cout<<menu[2]<<endl;
						f=3;
						break;

					}
					if(f==2)
					{
						system("cls");
						gotoxy(30,10);
						SetColor(14,0);
						cout<<menu[0]<<endl;
						gotoxy(30,11);
						SetColor(2,0);

						cout<<menu[1]<<endl;
						gotoxy(30,12);
						cout<<menu[2]<<endl;
						f=1;
						break;

					}
					if(f==3)
					{
						system("cls");
						gotoxy(30,10);
						SetColor(2,0);
						cout<<menu[0]<<endl;
						gotoxy(30,11);
						SetColor(14,0);
						cout<<menu[1]<<endl;
						gotoxy(30,12);
						SetColor(2,0);
						cout<<menu[2]<<endl;
						f=2;
						break;
						
					}
					break;
				}
			case 13:
				{
					
					
					if(f==1)
					{
						system("cls");
						FieldView field;
						field.Draw();
						break;
					}
					if(f==2)
					{
						system("cls");
						HighScores score;
						score.Draw();
						break;
					}
					if(f==3)
					{
						system("cls");
						exit(0);
						break;
					}
					break;
				}
				
			}
		

		}
			
		
	}