#pragma once
#include "Group.h"
#include <string>
#include <list>

using namespace std;

class Course{
	int id;
	string name;
	list<Group*> groups;
	string configLine;
public:
	inline int getId() { return id; }
	inline string getName() { return name; }
	void addGroup(Group* group) { groups.push_back(group); };
	inline list <Group*>& groupsAll() { return groups; }
	void setConfigLine(string line) { configLine = line; }
	inline string getConfigLine() { return configLine; }
	Course(int, string, list<Group*>);
	~Course();
};

