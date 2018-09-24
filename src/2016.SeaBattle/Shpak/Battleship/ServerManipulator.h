#pragma once
#include <string>

class ServerManipulator
{
	std::wstring roomID;

public:
	void setRoom(std::wstring);
	void setRoom(int);

	std::wstring getNewRoom();

	std::string get();
	void post(std::string);
};

