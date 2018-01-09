#pragma once
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class Room
{
	int _id;
	string _name;
	int _size;
	map <string, int> tags;
	string configLine;
public:
	void addTag(string);

	inline int getId() { return _id; }
	inline int getSize() { return _size; }
	inline map <string, int>& getTags() { return tags; }
	inline string getName() { return _name; }
	void setConfigLine(string line) { configLine = line; }
	inline string getConfigLine() { return configLine; }
	Room(int, string, int);
	~Room();
};

