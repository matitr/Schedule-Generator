#pragma once
#include <string>

using namespace std;

class Subject{
	int _id;
	string _name;
	string configLine;
public:
	inline int getId() { return _id; }
	inline string getName() { return _name; }
	void setConfigLine(string line) { configLine = line; }
	inline string getConfigLine() { return configLine; }
	Subject(int ,string);
	~Subject();
};

