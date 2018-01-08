#pragma once
#include <list>
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include "InOut.h"
#include "Room.h"

using namespace std;

class Teacher;
class Subject;
class Group;
class Course;
class Room;
class CourseClass;


class Configuration : private InOut {

	static Configuration config;

	map <int, Teacher*> teachers;
	map <int, Subject*> subjects;
	map <int, Group*>	groups;
	map <int, Course*>	courses;
	map <int, Room*>	rooms;

	list <CourseClass*> coursesClasses;

	unordered_map<Teacher*, vector<CourseClass*>> teachersClasses;
	unordered_map<Group*, vector<CourseClass*>> groupsClasses;

	bool alreadyGotFromFile;
	int roomNumber = 1;

	typedef bool (Configuration::*configFunctionPtr)(string);
	void printText(string);
	bool configuration(ifstream&, int&, configFunctionPtr);

	bool setSettings(string);
	void delSpaces(string&);
	void delComments(string&);
	string divideText(string&);
	string getBeforeSymbol(string&, char);

	void addToClassCounter(CourseClass*);
public:
	bool getFromFile(string& errorMessage, string fileDir = "config.txt");
	void saveConfig(string fileDir = "config.txt");
	void saveSettings(ofstream &);

	bool addProf(string);
	bool addSubject(string);
	bool addGroup(string);
	bool addCourse(string);
	bool addRoom(string);
	bool addClass(string);

	int getLowestIdTeachers();
	int getLowestIdGroups();
	int getLowestIdSubjects();
	int getLowestIdCourses();
	int getLowestIdRooms();

	bool vatidateSafeDelProf(int id);
	bool vatidateSafeDelSubject(int id);
	bool vatidateSafeDelGroup(int id);

	bool removeProf(int id, bool safeRemove);
	bool removeSubject(int id, bool safeRemove);
	bool removeGroup(int id, bool safeRemove);
	bool removeCourse(int id);
	bool removeRoom(int id);
	bool removeClass(CourseClass*);

	inline Teacher* getTeacherById(int x) { return teachers[x]; }
	inline Group* getGroupById(int x) { return groups[x]; }
	inline Subject* getSubjectById(int x) { return subjects[x]; }
	inline Course* getCourseById(int x) { return courses[x]; }
	inline Room* getRoomById(int x) { return rooms[x]; }

	inline int numberOfRooms() { return rooms.size(); }
	int roomSize(int);

	inline map <int, Teacher*>& teachersAll() { return teachers; }
	inline map <int, Group*>& groupsAll() { return groups; }
	inline map <int, Room*>& allRooms() { return rooms; }
	inline map <int, Subject*>& subjectsAll() { return subjects; }
	inline map <int, Course*>& coursesAll() { return courses; }

	inline CourseClass* lastAddedClass() { return coursesClasses.back(); }
	inline unordered_map<Teacher*, vector<CourseClass*>>& getTeachersClasses() { return teachersClasses; }
	inline unordered_map<Group*, vector<CourseClass*>>& getGroupsClasses() { return groupsClasses; }
	inline static Configuration& getConfig() { return config; }
	inline static map <string, int>& getRoomTags(int x) { return config.rooms.find(x)->second->getTags(); }
	inline list <CourseClass*>& getCoursesClasses(){ return coursesClasses; }
	inline int numberOfClasses() { return coursesClasses.size(); }
	Configuration();
	~Configuration();
};

