#include "Main.h"
#include <iostream>

void Head::Draw()
{
	cout<<"Test"<<endl;


}

void Head::Clean()
{
		system("cls");
}


Head::Head(): cur(1) {}