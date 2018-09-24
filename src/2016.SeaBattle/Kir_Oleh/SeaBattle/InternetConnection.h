#pragma once
#include <string>
#include <cpprest/http_client.h>

using namespace web::http;
using namespace web::http::client;
using namespace utility;
using namespace utility::conversions;
using namespace std;

class InternetConnection
{

	http_client id_client;
	http_client communication_client;
	string id;
public:
	InternetConnection();
	string getId();
	void setId(string str);
	void setComClient();
	bool createRoom();
	void postMessage(string mes);
	string getMessage();
};