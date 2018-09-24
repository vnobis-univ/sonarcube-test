#include <Windows.h>
#include "MenuEN.h"
#include <conio.h>

void setConsoleToLucidaConsole()
{
	COORD dwFontSize;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info;
	if (!GetCurrentConsoleFontEx(output, false, &info))
	return;
	dwFontSize.X = 10;
	dwFontSize.Y = 16;
	info.FontFamily = FF_DONTCARE;
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, L"Lucida Console");
	info.dwFontSize = dwFontSize;
	SetCurrentConsoleFontEx(output, false, &info);
}

int main()
{
	setConsoleToLucidaConsole();
	system("title SeaWar");
	system("color 80");
	HWND hwnd;    
	
    char Title[1024];
    GetConsoleTitle(Title, 1024); 
    hwnd=FindWindow(NULL, Title); 
    MoveWindow(hwnd,0,0,1700,700,TRUE);

	


	
	MenuEN menu;
	menu.print();


}