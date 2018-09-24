#include "FieldView.h"
#include "ConsoleUtils.h"
#include "ExternUtils.h"
#include "Response.h"
#include "ResultView.h"
using namespace std;

const int infoNum = 10;

FieldView::FieldView(ServerManager sm, bool _master) :
	playerFld({ 144,78 }), rivalFld({ 544, 78 }),
	info(vector<string>(infoNum)), server(sm), master(_master) { }

void FieldView::makeMove(vector<COORD>& illegal, int& ships, int& score) {

	bool done = false;
	COORD selected = { 4,4 };

	while (!done && ships) {
	
		COORD moved = selected;
		bool legal;

		rivalFld.field[selected.X][selected.Y].draw(rivalFld.edge, yellowPen);
		switch (_getwch())
		{
		case 27:	      //ESC
			if (confirmExit(info[5])) {
				ships = 0;
			}
			break;
		case 77:          // right arrow
			moved.X++;
			break;
		case 75:          // left  arrow
			moved.X--;
			break;
		case 72:          // down arrow
			moved.Y--;
			break;
		case 80:          // up arrow
			moved.Y++;
			break;
		case 13:          //enter							-> communicate with server to get KILL/MISS
			legal = true;

			for (auto& i : illegal) {                          //..only if coord is valid
				if (i.X == selected.X && i.Y == selected.Y) {
					legal = false;
					break;
				}
			}

			if (legal) {
				server.post("SHOOT" + to_string(selected.X) + to_string(selected.Y));
				Sleep(200), server.getRespond(); 
				illegal.push_back(selected);
				
				string resp = server.getRespond();

				if (resp == "HIT") { 
					rivalFld.field[selected.X][selected.Y].drawX(rivalFld.edge, red);
					rivalFld.field[selected.X][selected.Y].setState(CELL_STATE::DAMAGED_SHIP);
				}
				else if(resp[0] == 'D') {	//DESTROYED
					ships--;
					score += resp.length() * 2;
					rivalFld.field[selected.X][selected.Y].drawX(rivalFld.edge, red);
					rivalFld.field[selected.X][selected.Y].setState(CELL_STATE::DAMAGED_SHIP);

					for (int i = 6; i < resp.length() -1; i+=2) {
						COORD temp = { resp[i] - '0', resp[i+1] - '0' };

						rivalFld.field[temp.X][temp.Y].draw(rivalFld.edge, red);

						if (rivalFld.field[temp.X -1][temp.Y].getState() == CELL_STATE::EMPTY && ( temp.X - 1 >= 0) && (temp.X - 1) <= 9 && temp.Y >= 0 && temp.Y <= 9) {
							rivalFld.field[temp.X -1][temp.Y].drawDot(rivalFld.edge, red);
							illegal.push_back({ temp.X - 1, temp.Y });
						}

						if (rivalFld.field[temp.X + 1][temp.Y].getState() == CELL_STATE::EMPTY && (temp.X + 1 >= 0) && (temp.X + 1) <= 9 && temp.Y >= 0 && temp.Y <= 9) {
							rivalFld.field[temp.X + 1][temp.Y].drawDot(rivalFld.edge, red);
							illegal.push_back({ temp.X + 1, temp.Y });
						}

						if (rivalFld.field[temp.X + 1][temp.Y+1].getState() == CELL_STATE::EMPTY && (temp.X + 1 >= 0) && (temp.X + 1) <= 9 && temp.Y+1 >= 0 && temp.Y+1 <= 9) {
							rivalFld.field[temp.X + 1][temp.Y+1].drawDot(rivalFld.edge, red);
							illegal.push_back({ temp.X + 1, temp.Y +1});
						}

						if (rivalFld.field[temp.X - 1][temp.Y - 1].getState() == CELL_STATE::EMPTY && (temp.X - 1 >= 0) && (temp.X - 1) <= 9 && temp.Y - 1 >= 0 && temp.Y - 1 <= 9) {
							rivalFld.field[temp.X - 1][temp.Y - 1].drawDot(rivalFld.edge, red);
							illegal.push_back({ temp.X - 1, temp.Y - 1 });
						}

						if (rivalFld.field[temp.X][temp.Y + 1].getState() == CELL_STATE::EMPTY && (temp.X>= 0) && (temp.X) <= 9 && temp.Y + 1 >= 0 && temp.Y + 1 <= 9) {
							rivalFld.field[temp.X][temp.Y + 1].drawDot(rivalFld.edge, red);
							illegal.push_back({ temp.X, temp.Y + 1 });
						}

						if (rivalFld.field[temp.X - 1][temp.Y + 1].getState() == CELL_STATE::EMPTY && (temp.X -1>= 0) && (temp.X-1) <= 9 && temp.Y + 1 >= 0 && temp.Y + 1 <= 9) {
							rivalFld.field[temp.X -1 ][temp.Y + 1].drawDot(rivalFld.edge, red);
							illegal.push_back({ temp.X-1, temp.Y + 1 });
						}

						if (rivalFld.field[temp.X + 1][temp.Y - 1].getState() == CELL_STATE::EMPTY && (temp.X + 1 >= 0) && (temp.X + 1) <= 9 && temp.Y - 1 >= 0 && temp.Y - 1 <= 9) {
							rivalFld.field[temp.X + 1][temp.Y - 1].drawDot(rivalFld.edge, red);
							illegal.push_back({ temp.X + 1, temp.Y - 1 });
						}

						if (rivalFld.field[temp.X][temp.Y - 1].getState() == CELL_STATE::EMPTY && (temp.X >= 0) && (temp.X) <= 9 && temp.Y - 1 >= 0 && temp.Y - 1 <= 9) {
							rivalFld.field[temp.X][temp.Y - 1].drawDot(rivalFld.edge, red);
							illegal.push_back({ temp.X, temp.Y - 1 });
						}

						rivalFld.field[temp.X][temp.Y].setState(CELL_STATE::DESTROYED_SHIP);

					}

					//white.midLinePrint(28, resp);
				}
				else if (resp == "MISS") {
					rivalFld.field[selected.X][selected.Y].drawDot(rivalFld.edge, red);
					done = true;
				}
			//	white.midLinePrint(24, server.getRespond());
			}
			else {
				rivalFld.field[selected.X][selected.Y].draw(rivalFld.edge, red);
				Sleep(200);
			}

		default:
			break;
		}

		if (moved.X <= 9 && moved.Y <= 9 && moved.X >= 0 && moved.Y >= 0) {
			rivalFld.field[selected.X][selected.Y].getState() == CELL_STATE::DESTROYED_SHIP ?
				rivalFld.field[selected.X][selected.Y].draw(rivalFld.edge, red):
				rivalFld.field[selected.X][selected.Y].draw(rivalFld.edge, blue);

			selected = moved;
		}
	}

}

void FieldView::listen(int& shipCount) {
	
	string status = server.getRespond();
	white.midLinePrint(26, info[3]);

	string finalStatus;
	master ? finalStatus = "!MASTER_DONE" : finalStatus = "MASTER_DONE";

	while (status != finalStatus && shipCount) {
		status = server.getRespond();

		if (status[0] == 'S') {
			COORD shoot = { status[5] - '0',  status[6] - '0' };
		//	white.midLinePrint(25, to_string(shoot.X) + " " + to_string(shoot.Y));

			if (playerFld.field[shoot.X][shoot.Y].getState() == CELL_STATE::SHIP) {

				Ship& damaged = shipManager.getShipWithCoords({ shoot.X, shoot.Y }, playerFld.ships);
				damaged.setDamage({ shoot.X, shoot.Y });

				playerFld.field[shoot.X][shoot.Y].drawX(playerFld.edge, red);

				if (damaged.destroyed()) {
					shipCount--;
					server.post("DESTR_" + damaged.getCoords());
				}
				else {
					server.post("HIT");	
				}
			}
			else {
				server.post("MISS");
				playerFld.field[shoot.X][shoot.Y].drawDot(playerFld.edge, red);
			}
			
		}
	}

	aqua.midLinePrint(26, info[3]);

}

void FieldView::drawFields(){
	moveTo(19, 4);
	playerFld.draw();
	moveTo(69, 4);
	rivalFld.draw();
}

void FieldView::draw() {

	while (to_response(server.getRespond()) != Response::JOINED) {         //waiting for opponent
		white.midLinePrint(5, info[0]);
	}
	aqua.midLinePrint(5, info[0]);
	
	drawFields();
	white.midLinePrint(24, info[4]);
	playerFld.deployShips();
	aqua.midLinePrint(24, info[4]);

	if (to_response(server.getRespond()) == Response::JOINED) {            //INFORM ABOUT DEPLOYED SHIPS AND WAIT FOR OPPONENT 
		server.post("P1_READY");
		while (to_response(server.getRespond()) != Response::P2_READY) {
			white.midLinePrint(25, info[1]);
		}
	}
	else
		server.post("P2_READY");
		
	aqua.midLinePrint(25, info[1]);
	
	if (master) {
		white.midLinePrint(25, info[2]);
		_getwch();
		aqua.midLinePrint(25, info[2]);
	}
}

View* FieldView::handle() {
	
	vector<COORD> illegal;  //illegal moves aren't sent to server 
	
	int shipCount = 10, playerShips = 10, score = 0;

	while (shipCount && playerShips) {
	
		if (master) {
			makeMove(illegal, playerShips, score);
			if (!playerShips || !shipCount) {
				break;
			}

			server.post("MASTER_DONE");
			listen(shipCount);
		}
		else {
			listen(shipCount);
			if (!shipCount || !playerShips) {
				break;
			}
			makeMove(illegal, playerShips, score);
			server.post("!MASTER_DONE");
		}

		Sleep(100);
	}

	playerShips ? white.midLinePrint(27, info[7]) : white.midLinePrint(27, info[6]);
	white.midLinePrint(28, info[8]);
	_getwch();
	
	View* nextView;

	typeid(*this) == typeid(EngGameView) ? nextView = new EngResult(score) : nextView = new UkrResult(score);
	return nextView;
}

EngGameView::EngGameView(ServerManager sm, bool _isMaster) : FieldView(sm, _isMaster) {
	info[0] = "Waiting for opponent...";
	info[1] = "Waiting for opponent ship deployment...";
	info[2] = "Ready to go! Press any key and win!";
	info[3] = "Opponent's turn...";
	info[4] = "Press Q to rotate ship";
	info[5] = "  PRESS ESC AGAIN TO COFIRM EXIT OR ANY KEY TO CONTINUE  ";
	info[6] = "YOU WIN!";
	info[7] = "YOU LOOSE (";
	info[8] = "PRESS ANY KEY TO CONTINUE ";
}

UkrGameView::UkrGameView(ServerManager sm, bool _isMaster): FieldView(sm, _isMaster) {
	info[0] = "Очікуємо суперника...";
	info[1] = "Очікуємо розстановки кораблів суперника...";
	info[2] = "Все готово! Натисніть будь-яку клавішу для продовження";
	info[3] = "Противника хід...";
	info[4] = "Натисніть Q для повороту корабля";
	info[5] = "  ДЛЯ ПІДТВЕРДЖЕННЯ ВИХОДУ, НАТИСНІТЬ ESC ПОВТОРНО  ";
	info[6] = "ВИ ПЕРЕМОГЛИ!";
	info[7] = "ВИ ПРОГРАЛИ (";
	info[8] = "Натисніть будь-яку клавішу для продовження";
}
