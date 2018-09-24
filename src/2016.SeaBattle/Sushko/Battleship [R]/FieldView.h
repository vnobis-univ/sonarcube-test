#pragma once
#include <vector>
#include "View.h"
#include "Field.h"
#include "ServerManager.h"

using std::vector;

class FieldView : public View {

	Field playerFld;
	Field rivalFld;

	bool master;

	ServerManager server;
	ShipManager shipManager;

	void makeMove(vector<COORD>& illegal, int& i, int& score);
	void listen(int& shipCount);
protected:

	FieldView(ServerManager sm, bool _isMaster = false);

	vector<string> info;

	void drawFields();

	virtual void draw();
	virtual View* handle();
};

class EngGameView : public FieldView {
public:
	EngGameView(ServerManager sm, bool _isMaster = false);
};

class UkrGameView : public FieldView {
public:
	UkrGameView(ServerManager sm, bool _isMaster = false);
};