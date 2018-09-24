#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include "Color.h"
#include "SetConsoleSize.h"
#include "StartMenu.h"
#include <cpprest/http_client.h>
#include "InternetConnection.h"
using namespace std;
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

extern HANDLE hConsole;
extern StartMenu menu;

int main()
{/*
	http_client client(U("https://developer.mbed.org"));
	http_response res = client.request(methods::GET, U("/media/uploads/mbed_official/hello.txt")).get();

	string resBodyText = res.extract_utf8string().get();

	cout << resBodyText << endl;

	system("PAUSE");
	*/



	setConsoleSize();
	menu.draw();

	return 0;
}