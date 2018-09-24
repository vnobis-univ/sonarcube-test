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
private:
	http_client id_client;
	http_client communication_client;
	wstring id;
public:
	InternetConnection() :
		id_client(U("http://ec2-54-171-91-182.eu-west-1.compute.amazonaws.com:3000/")),
		communication_client(U("http://ec2-54-171-91-182.eu-west-1.compute.amazonaws.com:3000/rooms/"))
	{
	}

	wstring getNewRoom()
	{
		http_client client(U("http://ec2-54-171-91-182.eu-west-1.compute.amazonaws.com:3000"));
		http_response response = client.request(methods::GET, U("/rooms/get-new-room")).get();
		string respond = response.extract_utf8string(true).get();
		wstring ident(L"");

		for (size_t i = 3; i < respond.length(); ++i)
		{
			ident.push_back(respond[i]);
		}

		return ident;
	}

	void setID(wstring s)
	{
		id = s;
	}
	
	string get()
	{
		http_client client(U("http://ec2-54-171-91-182.eu-west-1.compute.amazonaws.com:3000"));
		http_response response = client.request(methods::GET, U("/rooms/" + id)).get();

		return response.extract_utf8string().get();
	}

	void postMessage(string _post)
	{
		http_client client(U("http://ec2-54-171-91-182.eu-west-1.compute.amazonaws.com:3000/rooms/" + id));
		client.request(methods::POST, L"", wstring(_post.begin(), _post.end()));
	}
};