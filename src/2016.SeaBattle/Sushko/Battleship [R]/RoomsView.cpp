#include <iostream>
#include "RoomsView.h"
#include "ConsoleUtils.h"
#include "ExternUtils.h"
#include "OptionSelector.h"
#include "StartView.h"
#include "FieldView.h"
#include "Response.h"

using namespace std;

void RoomsView::printOptions(int margin, int line, int curr) {
	for (int i = 0; i < options.size(); ++i) {

		i == curr ? yellow.setColor() : white.setColor();

		moveTo(margin, line);
		cout << options[i];
		margin += options[i].length() + 6;
	}
}

RoomsView::RoomsView(): info(vector<string>(10)), options(vector<string>(2))  {}

void RoomsView::draw() {

	lightAqua.midLinePrint(2, info[0]);
	lightAqua.midLinePrint(27, info[6]);

	white.midLinePrint(6, info[1]);
	white.midLinePrint(7, info[2]);
	
	printOptions(47, 11, 0);
}

View* RoomsView::handle()
{
	View* nextView = this;

	OptionSelector current(0, 0, 1);
	bool nextChosen = false;
	wstring id(L"");

	while (!nextChosen) {

		switch (_getwch()) {

		case 75: // <-
			--current;
			break;
		case 77: // ->
			++current;
			break;
		case 13: //enter  -> creating or joining the room  -> switch to GameView; 
			if (current == 0)
			{
				id = server.getRoom();
				white.midLinePrint(14, info[3] + string(id.begin(), id.end()));
				white.midLinePrint(15, info[4]);
				typeid(*this) == typeid(EngRoomsView) ? nextView = new EngGameView(server, true) : nextView = new UkrGameView(server, true);
			}
			else 
			{
				bool correct = false;
				
				while (!correct) {
					white.midLinePrint(15, info[7]);
				
					string inVal = consoleInput({ 65 ,15 }, 8, 48, 57);
					id = wstring(inVal.begin(), inVal.end());

					server.setRoom(id);

					if (to_response(server.getRespond()) == Response::CREATED) {
						server.post("Joined");
						correct = nextChosen = true;
						typeid(*this) == typeid(EngRoomsView) ? nextView = new EngGameView(server) : nextView = new UkrGameView(server);
					}
					else {
						white.midLinePrint(18, info[8]);
						_getwch();
						aqua.midLinePrint(18, info[8]);
						moveTo(65, 15), white.print(string(9, ' '));
					}
				}

			}
			
			white.midLinePrint(18, info[5]);
			_getwch();
			nextChosen = true;
			break;
		case 27:  //ESC -> return to startView
			nextChosen = true;
			typeid(*this) == typeid(EngRoomsView) ? nextView = new EngStartView() : nextView = new UkrStartView();
			break;
		}
		printOptions(47, 11, current);
	}

	return nextView;

}

EngRoomsView::EngRoomsView() {

	info[0] = "Battle is coming!";
	info[1] = "To start playing you should create a new room,";
	info[2] = "or join exiting one:";
	options[0] = "CREATE ROOM";
	options[1] = "JOIN ROOM";
	info[3] = "Created! Room id: ";
	info[4] = "Now your rival should join this room";
	info[5] = "Press any key and fight for death!";
	info[6] = "(c)all rights reserved, 2016";
	info[7] = "Enter ID: ";
	info[8] = "ROOM DOESN'T EXIST!";
}

UkrRoomsView::UkrRoomsView(){

	info[0] = "Битва близько!";
	info[1] = "Для початку гри необхідно створити нову кінмату,";
	info[2] = "або приєднатись до існуючої:";
	options[0] = "СТВОРИТИ";
	options[1] = "ПРИЄДНАТИСЬ";
	info[3] = "Створено! id : ";
	info[4] = "Ваш суперник повинен приєднатись до цієї кімнати";
	info[5] = "Натисніть будь-яку клавішу і го-го-го!";
	info[6] = "(c) всі права захищено, 2016";
	info[7] = "Введіть ID: ";
	info[8] = "КІМНАТА НЕ ІСНУЄ!";
}
