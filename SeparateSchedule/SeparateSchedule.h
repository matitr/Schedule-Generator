#pragma once
#ifndef SEPARATE_SCHEDULE_H
#define SEPARATE_SCHEDULE_H

#include "List.h"
#include "InOut.h"
#include <list>
#include <map>
#define FAIL 0
#define SUCCESS 1

using namespace std;

class List;
class MainWindow;
class InOut;
struct Lesson;

class SeparateSchedule
{
	struct s {
		string hour = "";
		string day = "";
		string groupString = "";
		string teachersString = "";
		string subject = "";
		string room = "";
		string week = "Every";
		list<string> groups;
		list<string> teachers;
		void divideGroups();
		void divideTeachers();
	};
    MainWindow *window;
	InOut IOStream;
	List *teachers;
	List *groups;
	List *rooms;
//	bool getFromFile(string fileDir = "data.txt");
	bool fileInput(string fileDir, int&, string&);
	void consoleEdit();
	int consoleGetChoice();
	bool consoleAdd();
	bool consoleDelLesson();
	bool strToInt(string, int&);
	bool consoleDelTeacher();
	bool consoleDelGroup();
	bool checkText(string, s*, string&);
	bool extractText(string, s*);
	
	void prepareToSave();

	bool checkHour(string);
	bool checkDay(string);
	bool checkGroup(string);
	bool checkName(string);
	bool checkSubject(string&);
public:
	void run();
	bool getFromFile(string fileDir = "data.txt");
    map<string, list<Lesson*>>* createMapGroups() { return groups->createStandardList(); }
    map<string, list<Lesson*>>* createMapTeachers() { return teachers->createStandardList(); }
    map<string, list<Lesson*>>* createMapRooms() { return rooms->createStandardList(); }
	SeparateSchedule();
    SeparateSchedule(MainWindow*);
	~SeparateSchedule();
};

#endif
