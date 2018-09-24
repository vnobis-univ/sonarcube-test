#include "RoomInfoView.h"
#include "Globals.h"
#include "ConsoleFunctions.h"
#include <conio.h>
#include "FieldView.h"
#include "StartView.h"

RoomInfoView::RoomInfoView(bool start_game) :
	service_(language),
	communication_manager_(new CommunicationManager()),
	start_game_(start_game),
	room_id_(""),
	message_("press_enter_to_continue")
{
	if (start_game_)
	{
		room_id_ = communication_manager_->startGame();
	}
}

void RoomInfoView::draw()
{
	if (start_game_)
	{
		printAtCenterOfLine(14, service_.getWord("youve_started_new_game"), yellowSymbolsGreenBackground);
		printAtCenterOfLine(15, service_.getWord("room_id") + room_id_, yellowSymbolsGreenBackground);
		printAtCenterOfLine(16, service_.getWord("please_give_to_friend"), yellowSymbolsGreenBackground);
		printAtCenterOfLine(18, service_.getWord("press_enter_to_continue"), lightGreenSymbolsGreenBackground);
	}
	else
	{
		printAtCenterOfLine(14, service_.getWord("youre_joining_game"), yellowSymbolsGreenBackground);
		printAtCenterOfLine(16, service_.getWord("please_take_from_friend"), yellowSymbolsGreenBackground);
		printAtCenterOfLine(15, service_.getWord("enter_room_id") + room_id_, yellowSymbolsGreenBackground);
		printAtCenterOfLine(18, service_.getWord(message_), lightGreenSymbolsGreenBackground);
	}
}

View* RoomInfoView::handle()
{
	View* nextView = this;

	int keyPressed = _getch();
	if (keyPressed == KEY_ENTER && room_id_.length() > 0 && room_id_.length() <= 5)
	{
		communication_manager_->joinGame(room_id_);
		string response = communication_manager_->receiveMessage();
		if (response == "room doesn't exist" || response != "Created")
		{
			message_ = "please_enter_valid_roomid";
		}
		else
		{
			nextView = new FieldView(true, start_game_, room_id_, 0);
		}
	}
	else if (start_game_ == false && keyPressed >= '0' && keyPressed <= '9' && room_id_.length() < 5)
	{
		room_id_ += keyPressed;
	}
	else if (start_game_ == false && keyPressed == KEY_BACKSPACE && room_id_.length() > 0)
	{
		room_id_ = room_id_.substr(0, room_id_.length() - 1);
	}
	else if (keyPressed == KEY_ESCAPE)
	{
		nextView = new StartView();
	}

	return nextView;
}