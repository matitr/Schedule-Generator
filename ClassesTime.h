#pragma once
#include <unordered_map>

using namespace std;

class CourseClass;
class Values;

typedef unordered_map<string, Values> ClassesTime_t;

class Values {
public:
	short time;
	short day;
	short numberOfClasses;
	int breaksLonger;
	int totalStartTime;
	CourseClass* prevClass;
/*
	short timeEven;
	short dayEven;
	short numberOfClassesEven;
	
	short timeOdd;
	short dayOdd;
	short numberOfClassesOdd;
	*/
public:
	Values();
	~Values();
};

class ClassesTime {
public:
//	unordered_map<string, Values> times;

public:
//	typedef void (ClassesTime::*functPointer)();
	static void createForGroups(unordered_map<string, Values>* times);
	static void createForTeachers(unordered_map<string, Values>* times);

	ClassesTime();
	~ClassesTime();
};

