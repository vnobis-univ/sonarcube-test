#include "InternetConnection.h"

InternetConnection::InternetConnection() :
id_client(U("http://ec2-54-171-91-182.eu-west-1.compute.amazonaws.com:3000/")),
communication_client(U("http://ec2-54-171-91-182.eu-west-1.compute.amazonaws.com:3000/rooms/"))
{
}

string InternetConnection::getId()
{
	return id;
}

void InternetConnection::setId(string str)
{
	id = str;
}

void InternetConnection::setComClient()
{
	try
	{
		wstring str = wstring(id.begin(), id.end());
		communication_client = http_client(U("http://ec2-54-171-91-182.eu-west-1.compute.amazonaws.com:3000/rooms/") + str);
	}
	catch (...)
	{
	}
}

bool InternetConnection::createRoom()
{
	try
	{
		http_response res = id_client.request(methods::GET, U("/rooms/get-new-room")).get();
		id = res.extract_utf8string(true).get();
		id = string(id.begin() + 3, id.end());
		return true;
	}
	catch (...)
	{
		return false;
	}
}

void InternetConnection::postMessage(string mes)
{
	string_t request_mes = to_string_t(mes);
	http_request request(methods::POST);
	request.set_body(request_mes);
	communication_client.request(request);
}

string InternetConnection::getMessage()
{
	try
	{
		http_response response = communication_client.request(methods::GET).get();
		return response.extract_utf8string(true).get();
	}
	catch (...)
	{
		return "false";
	}
}

