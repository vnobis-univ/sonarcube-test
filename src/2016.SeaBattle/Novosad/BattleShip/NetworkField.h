#pragma once
#include "CommunicationManager.h"
#include "Field.h"

class NetworkField : public Field
{
	const string fire_action = "fire-action";
	const string fire_result = "fire-result";
	const string battle_result = "battle-result";
	const string fire_miss = "miss";
	const string fire_hit = "hit";
	const string fire_kill = "kill";
	const string fire_all_killed = "all-killed";
	const string place_result = "place-result";
	const string place_ready = "ready";

	char delimiter_ = ':';
	bool start_game_;
	string player_name_;
	CommunicationManager* communication_manager_;
	FireDetails parseTokens(vector<string>& tokens);
	CellState convertFrom(FireResult fire_result);
public:
	NetworkField(
		int locationX,
		int locationY,
		int cell_width,
		int cell_height,
		bool start_game,
		CommunicationManager* communication_manager);

	FireDetails fireAt(int x, int y) override;
	FireDetails waitForFire() override;
	void finishBattle() override;
	void submitFire(FireDetails details) override;
	bool isReady() override;
	bool allShipsKilled() override;
};