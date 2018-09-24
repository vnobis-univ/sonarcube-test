#include "CommunicationManager.h"
#include "windows.h"
#include <string>
#include <cpprest/details/basic_types.h>
#include <cpprest/http_msg.h>

using namespace std;

CommunicationManager::CommunicationManager() : 
	client(U("http://ec2-54-171-91-182.eu-west-1.compute.amazonaws.com:3000")),
	roomId("")
{
}

string CommunicationManager::getRoomId()
{
	return roomId;
}

string CommunicationManager::startGame()
{
	http_request request;
	request.set_method(methods::GET);
	request.set_request_uri(U("rooms/get-new-room"));

	http_response response = client.request(request).get();
	string responseBody = response.extract_utf8string().get();
	int equalsSignIndex = responseBody.find('=');
	roomId = responseBody.substr(equalsSignIndex + 1, responseBody.length() - equalsSignIndex - 1);
	return roomId;
}

void CommunicationManager::joinGame(string _roomId)
{
	roomId = _roomId;
}

void CommunicationManager::sendMessage(string messageBody)
{
	wstring wroomId(roomId.begin(), roomId.end());
	wstring requestUri = U("/rooms/" + wroomId);

	http_request request;
	request.set_method(methods::POST);
	request.set_request_uri(requestUri);
	request.set_body(messageBody);

	http_response response = client.request(request).get();
	string responseBodyText = response.extract_utf8string().get();
}

string CommunicationManager::receiveMessage()
{
	wstring wroomId(roomId.begin(), roomId.end());
	wstring requestUri = U("/rooms/" + wroomId);

	http_request request;
	request.set_method(methods::GET);
	request.set_request_uri(requestUri);

	http_response response = client.request(request).get();
	return response.extract_utf8string().get();
}
