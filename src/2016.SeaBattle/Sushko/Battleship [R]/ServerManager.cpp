#include "ServerManager.h"
#include <cpprest/http_client.h>

using namespace web::http;
using namespace web::http::client;
using namespace std;

void ServerManager::setRoom(wstring _room)
{
	roomID = _room;
}

wstring ServerManager::getRoom()
{
	http_client client(U("http://ec2-54-171-91-182.eu-west-1.compute.amazonaws.com:3000"));
	http_response res = client.request(methods::GET, U("/rooms/get-new-room")).get();
	string respond = res.extract_utf8string().get();
	wstring id(L"");

	for (int i = 3; i < respond.length(); i++)
		id += respond[i];

	roomID = id;
	return id;
}

string ServerManager::getRespond()
{
	http_client client(U("http://ec2-54-171-91-182.eu-west-1.compute.amazonaws.com:3000"));
	http_response res = client.request(methods::GET, U("/rooms/" + roomID)).get();

	return res.extract_utf8string().get();
}

void ServerManager::post(string _post)
{
	http_client client(U("http://ec2-54-171-91-182.eu-west-1.compute.amazonaws.com:3000/rooms/" + roomID));
	client.request(methods::POST, L"", wstring(_post.begin(), _post.end()));
}
