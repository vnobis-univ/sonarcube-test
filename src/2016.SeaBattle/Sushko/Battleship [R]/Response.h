#pragma once
#include <string>

using std::string;

enum class Response {
	CREATED,
	JOINED,
	P1_READY,
	P2_READY,
	SHOOT,
	UNEXPECTED_RESP
};

Response to_response(string wstr);