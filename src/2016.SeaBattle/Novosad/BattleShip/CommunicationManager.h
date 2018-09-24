#pragma once
#include "cpprest/http_client.h"

using namespace web::http;
using namespace client;
using namespace std;

class CommunicationManager
{
	http_client client;
	string roomId;
public:
	CommunicationManager();
	string getRoomId();
	string startGame();
	void joinGame(string _roomId);
	void sendMessage(string messageBody);
	string receiveMessage();
};