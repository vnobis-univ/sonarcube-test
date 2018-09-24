#include <iostream>
using namespace std;

#include "ForConsole.h"
#include "Printer.h"
#include "View.h"
#include "StartView.h"
#include "FieldView.h"

int main()
{
	setConsoleSize();
	
	View* some = new StartView();
	some->handle();
	

	
	return 0;
}