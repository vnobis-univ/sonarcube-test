#include "ExternUtils.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HDC hdc = GetDC(GetConsoleWindow());

Printer white(Color::light_white, Color::aqua);
Printer yellow(Color::light_yellow, Color::aqua);
Printer aqua(Color::aqua, Color::aqua);
Printer redP(Color::light_red, Color::black);
Printer lightAqua(Color::light_aqua, Color::aqua);

HPEN red(CreatePen(PS_SOLID, 2, RGB(255, 1, 1)));
HPEN whitePen(CreatePen(PS_SOLID, 1, RGB(255, 255, 255)));
HPEN yellowPen(CreatePen(PS_SOLID, 2, RGB(254, 133, 33)));

HPEN blue(CreatePen(PS_SOLID, 2, RGB(8, 28, 71)));
//HPEN blue(CreatePen(PS_SOLID, 2, RGB(27, 77, 77)));
HPEN darkAqua(CreatePen(PS_SOLID, 2, RGB(0, 250, 250)));