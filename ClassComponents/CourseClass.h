#pragma once
#include "Teacher.h"
#include "Subject.h"
#include "Group.h"
#include <map>
using namespace std;

class CourseClass{
	Subject* subject;
//	Teacher* teacher;
	list <Teacher*> teachers;
	list <Group*> groups;
	map <string, int> roomTags;
	int duration;
	int requiredRoomSize;
	int numOfRooms;
	bool classEveryWeek;
	string configLine;
public:
	inline int classDuration() { return duration; }
	inline int requiredSize() { return requiredRoomSize; }
	int getRandomRoom();
	void addRoomTag(string);
	bool compareTeachers(CourseClass*);
	bool compareGroups(CourseClass*);
	void setClassEveryWeek(bool x) { classEveryWeek = x; }
	inline Subject* getSubject() { return subject; }
	inline list <Teacher*>& getTeachers() { return teachers; }
	inline list <Group*>& getGroups() { return groups; }
	inline int groupsSize() { return groups.size(); }
	inline map <string, int>& getRoomTags() { return roomTags; }
	inline bool getClassEveryWeek() { return classEveryWeek; }
	void setConfigLine(string line) { configLine = line; }
	inline string getConfigLine() { return configLine; }
	CourseClass(Subject*, list <Teacher*>&, list <Group*>&, int);
	~CourseClass();


};

