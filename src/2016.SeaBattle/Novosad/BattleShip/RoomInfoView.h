#pragma once
#include "View.h"
#include "NetworkField.h"
#include "TranslationService.h"

class RoomInfoView : public View
{
	TranslationService service_;
	CommunicationManager* communication_manager_;
	bool start_game_;
	string room_id_;
	string message_;
public:
	RoomInfoView(bool start_game);
	void draw() override;
	View* handle() override;
};
