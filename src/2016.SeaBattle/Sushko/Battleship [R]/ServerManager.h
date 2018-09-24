#pragma once
#include <string>

using std::string;
using std::wstring;
using std::stoi;

class ServerManager {

	wstring roomID;
public:

	void setRoom(wstring _room);

	wstring getRoom();
	string getRespond();
	void post(string _post);
	 
};