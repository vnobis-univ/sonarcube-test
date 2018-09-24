#pragma once
#include <vector>
#include "View.h"
#include "ServerManager.h"

using std::vector;

class RoomsView : public View {

	ServerManager server;
	void printOptions(int margin, int line, int curr = 0);
protected:
	RoomsView();
	vector<string> info;
	vector<string> options;

	virtual void draw();
	virtual View* handle();


};

class EngRoomsView : public RoomsView {
public:
	EngRoomsView();

};

class UkrRoomsView : public RoomsView {
public:
	UkrRoomsView();

};