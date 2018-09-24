#include <iostream>
#include "View.h"
#include "StartView.h"

using namespace std;

int main()
{
	
	View view;
	StartView sview;
	
	view.Clean();
	sview.Draw();
	return 0;
}