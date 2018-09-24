#include <string>
#include "NetworkField.h"
#include "Globals.h"

NetworkField::NetworkField(
	int locationX,
	int locationY,
	int cell_width,
	int cell_height,
	bool start_game,
	CommunicationManager* communication_manager) :
	Field(locationX, locationY, cell_width, cell_height),
	start_game_(start_game),
	communication_manager_(communication_manager)
{
	player_name_ = start_game_ ? "player1" : "player2";
}

CellState NetworkField::convertFrom(FireResult fire_result)
{
	switch (fire_result)
	{
	case FireResult::Hit:
	case FireResult::Kill:
		return CellState::Hit;
	case FireResult::Miss:
	default:
		return CellState::Missed;
	}
}

FireDetails NetworkField::parseTokens(vector<string>& tokens)
{
	// messages received is in the following format:
	// type:value:value
	// 
	// below are some examples of messages:
	// fire-action:3:5
	// fire-result:miss:-1
	// fire-result:hit:-1
	// fire-result:kill:4
	// place-result:player2:ready

	FireDetails details;

	if (tokens[0] == fire_action)
	{
		details.X = stoi(tokens[1]);
		details.Y = stoi(tokens[2]);
	}
	else if (tokens[0] == fire_result || tokens[0] == battle_result)
	{
		if (tokens[1] == fire_miss)
		{
			details.Result = FireResult::Miss;
		}
		else if (tokens[1] == fire_hit)
		{
			details.Result = FireResult::Hit;
		}
		else if (tokens[1] == fire_kill)
		{
			details.Result = FireResult::Kill;
		}
		else if (tokens[1] == fire_all_killed)
		{
			details.Result = FireResult::AllKilled;
		}

		details.ShipSize = stoi(tokens[2]);
	}

	return details;
}

FireDetails NetworkField::fireAt(int x, int y)
{
	// create a message request and send via network
	string fireAtMessage = fire_action + delimiter_ + to_string(x) + delimiter_ + to_string(y);
	communication_manager_->sendMessage(fireAtMessage);

	// wait for response message to be received
	// tokenize (split) received message
	string responseMessage;
	vector<string> tokens;

	do
	{
		responseMessage = communication_manager_->receiveMessage();
		tokens = split(responseMessage, delimiter_);
	} while (tokens[0] != fire_result && tokens[0] != battle_result);

	// parse tokens into values
	FireDetails details = parseTokens(tokens);

	// update internal field state
	// (so it can draw itself correctly)
	setCellState(x, y, convertFrom(details.Result));

	// update network result with coordinates
	details.X = x;
	details.Y = y;

	return details;
}

FireDetails NetworkField::waitForFire()
{
	// wait for response message to be received
	// tokenize (split) received message
	string responseMessage;
	vector<string> tokens;

	do
	{
		Sleep(100);
		responseMessage = communication_manager_->receiveMessage();
		tokens = split(responseMessage, delimiter_);
	} while (tokens[0] != fire_action && tokens[0] != battle_result);

	// parse tokens into values and get details
	FireDetails details = parseTokens(tokens);

	return details;
}

void NetworkField::finishBattle()
{
	string fireAtMessage = battle_result + delimiter_ + fire_all_killed + delimiter_ + "-1";
	communication_manager_->sendMessage(fireAtMessage);
}

void NetworkField::submitFire(FireDetails details)
{
	string type = "";

	switch (details.Result)
	{
	case FireResult::Miss:
		type = fire_miss;
		break;
	case FireResult::Hit:
		type = fire_hit;
		break;
	case FireResult::Kill:
		type = fire_kill;
		break;
	case FireResult::AllKilled: 
		type = fire_all_killed;
		break;
	default: 
		break;
	}

	// create a message response and send via network
	string fireAtMessage = fire_result + delimiter_ + type + delimiter_ + to_string(details.ShipSize);
	communication_manager_->sendMessage(fireAtMessage);
}

bool NetworkField::isReady()
{
	bool is_ready = false;
	string myReadyMessage = place_result + delimiter_ + player_name_ + delimiter_ + place_ready;
	string responseMessage = communication_manager_->receiveMessage();

	if (responseMessage == "Created")
	{
		communication_manager_->sendMessage(myReadyMessage);
		is_ready = false;
	}
	else if (responseMessage == myReadyMessage)
	{
		is_ready = false;
	}
	else
	{
		vector<string> tokens = split(responseMessage, delimiter_);
		if (tokens.size() > 1 &&
			tokens[0] == place_result &&
			tokens[1] != player_name_ &&
			tokens[2] == place_ready)
		{
			communication_manager_->sendMessage(myReadyMessage);
			is_ready = true;
		}
	}

	Sleep(100);
	return is_ready;
}

bool NetworkField::allShipsKilled()
{
	string responseMessage = communication_manager_->receiveMessage();
	vector<string> tokens = split(responseMessage, delimiter_);

	if ((tokens[0] == fire_result ||
		tokens[0] == battle_result) && 
		tokens[1] == fire_all_killed)
	{
		NetworkField::finishBattle();
		return true;
	}

	return false;
}
