#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;

class Score{
private:
	string name;
	int point;
public:
	Score(): name("Noname"), point(0) {}

	Score(string n, int p){
		name = n;
		point = p;
	}

	bool operator<(const int el){
		return point < el;
	}

	bool operator<(const Score& s){
		return point < s.point;
	}

	Score operator=(const Score& s){
		name = s.name;
		point = s.point;
		return *this;
	}

	bool operator==(const Score& s){
		return name == s.name;
	}

	friend ifstream& operator>>(ifstream& read, Score& s){
		read>>s.name>>s.point;
		return read;
	}
	friend ostream& operator<<(ostream& cout, Score& s){
		cout<<s.name<<setw(20-s.name.length())<<s.point<<endl;
		return cout;
	}
};