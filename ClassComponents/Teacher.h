#pragma once
#include <string>
#include <list>

using namespace std;

class courseClass;
class Teacher{
	int _id;
	string _name;
	string configLine;

public:
	inline int getId() { return _id; }
	inline string getName() { return _name; }
	void setConfigLine(string line) { configLine = line; }
	inline string getConfigLine() { return configLine; }
	Teacher(int, string);
	~Teacher();
};

