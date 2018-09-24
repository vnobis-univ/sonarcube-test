#pragma once

#include "Connection.h"
#include "ConsoleProperties.h"

Connection::Connection()
	: roomId(L""),
	client(U("http://ec2-54-171-91-182.eu-west-1.compute.amazonaws.com:3000/"))
{
}

void Connection::setId()
{
	http_response res = client.request(methods::GET, U("/rooms/get-new-room")).get();
	roomId = res.extract_utf16string().get();
	roomId.erase(0, 3);
}

void Connection::setId(const string& s)
{
	roomId = utility::conversions::utf8_to_utf16(s);
}

utility::string_t Connection::id() const
{
	return roomId;
}

string Connection::stringId() const
{
	return utility::conversions::utf16_to_utf8(roomId);
}

string Connection::getServerData()
{
	http_response res = client.request(methods::GET, U("/rooms/" + roomId)).get();
	string serverData = res.extract_utf8string().get();

	return serverData;
}

void Connection::setServerData(const string& s)
{
	utility::string_t toPut = utility::conversions::utf8_to_utf16(s);
	client.request(methods::POST, U("/rooms/" + roomId), toPut);
}

void Connection::readIdFromUser(bool& successfulLogin) // successfulLogin tells whether connection was made
{
	bool isOk = false;
	string id;

	while (!isOk) // works until user's  id is correctly written
	{
		id = getUserTextInput(5);

		if (id.size() == 5)
		{
			int symbolCounter = 0;

			for (size_t i = 0; i < id.size(); ++i) // checks whether all of the symbols are numbers
			{
				if (id[i] >= '0' && id[i] <= '9')
				{
					++symbolCounter;
				}
				else
				{
					break;
				}
			}

			if (symbolCounter == 5)
			{
				isOk = true;
			}
		}
	}

	setId(id);

	if (getServerData() == "Created")
	{
		successfulLogin = true;
	}
}