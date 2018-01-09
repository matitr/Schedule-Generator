#pragma once
#include <string>
#include <list>

using namespace std;

class CourseClass;

class Group{
	int _id;
	string _name;
	int _numberOfStudents;
	string configLine;

public:
	inline int getId() { return _id; }
	inline int numberOfStudents() { return _numberOfStudents;  }
	inline string getName() { return _name; }
	void setConfigLine(string line) { configLine = line; }
	inline string getConfigLine() { return configLine; }
	Group(int, string, int);
	~Group();
};

