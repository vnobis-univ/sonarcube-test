#include "ServerManipulator.h"
#include <cpprest/http_client.h>
#include <string>

using namespace web::http;
using namespace web::http::client;

using std::wstring;
using std::string;

void ServerManipulator::setRoom(wstring room)
{
	roomID = room;
}

void ServerManipulator::setRoom(int room)
{
	setRoom(std::to_wstring(room));
}

wstring ServerManipulator::getNewRoom()
{
	http_client client(U("http://ec2-54-171-91-182.eu-west-1.compute.amazonaws.com:3000"));
	http_response res = client.request(methods::GET, U("/rooms/get-new-room")).get();
	string respond = res.extract_utf8string().get();
	wstring id(L"");

	for (int i = 3; i < respond.length(); ++i)
		id += respond[i];

	return id;
}

string ServerManipulator::get()
{
	http_client client(U("http://ec2-54-171-91-182.eu-west-1.compute.amazonaws.com:3000"));

	http_response res = client.request(methods::GET, U("/rooms/" + roomID)).get();

	return res.extract_utf8string().get();
}

void ServerManipulator::post(string _post)
{
	http_client client(U("http://ec2-54-171-91-182.eu-west-1.compute.amazonaws.com:3000/rooms/" + roomID));
	client.request(methods::POST, L"", wstring(_post.begin(), _post.end()));
}
