#pragma once
#include <vector>
#include "View.h"
#include "Field.h"
#include "Ship.h"
#include "TranslationService.h"

class FieldView : public View
{
	TranslationService service_;
	Field* player_field_;
	Field* enemy_field_;
	Ship playersCurrentShip_;
	string room_id_;
	string game_message_;
	bool playerShipsArePlaced_ = false;
	bool enemy_turn_ = false;
	bool playerIsReady_ = false;
	bool start_game_;
	bool multiplayer_;
	int current_score_;
	int currentX_ = 0;
	int currentY_ = 0;
	int playersCurrentShipIndex_ = 0;
	int shipsCount_ = 10;
	int getNextShipSize();
	int getPointsForKillingShip(int indexOfShip);
	void toggleTurn();
	void drawFieldDecorations();
	void drawInCursorLocation();
	View* handleShipPlacement(int key);
	View* handleMotionOnField(int key);
public:
	FieldView(bool multiplayer, bool start_game, string room_id, int score = 0);
	void draw() override;
	View* handle() override;
};

