#pragma once
#include <cpprest/http_client.h>
#include <string>

using namespace std;
using namespace web::http;
using namespace web::http::client;

class Connection
{
	utility::string_t roomId;
	http_client client;
public:
	Connection();

	void setId();

	void setId(const string&);

	utility::string_t id() const;

	string stringId() const;

	string getServerData();

	void setServerData(const string&);

	void readIdFromUser(bool&); // reads user id when joining the room

};