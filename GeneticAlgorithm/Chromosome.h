#pragma once
#include <map>
#include <unordered_map>
#include "Settings.h"
#include "ClassesTime.h"

#define HOURS_IN_DAY 10
#define SLOTS_IN_HOUR 4
#define MUTATION_CHANCE 1
#define NUMBER_OF_DAYS 5

#define EVEN 0
#define ODD 1

using namespace std;

class CourseClass;
class Settings;
class ClassesTime;
class Group;
//class ClassesTime;

class Chromosome : private Settings {
	long double fitness;
	bool goodSchedule = false;

	ClassesTime_t groupsTimeWithoutWeek;
	ClassesTime_t groupsTime[2]; // <string name, values>  values - time, day, number of lessons
	ClassesTime_t teachersTime[2]; // <string name, values>  values - time, day, number of lessons
	vector <list<pair<CourseClass*, int>>> timeLine; // <CourseClass*, roomId>

	unordered_map <CourseClass*, int> classes;

	unordered_map <CourseClass*, int> classesWeek;
	unordered_map <CourseClass*, unordered_map<Group*, bool>> groupErrorsDetails;
	unordered_map <CourseClass*, bool> groupErrors;
	unordered_map <CourseClass*, bool> profErrors;
	unordered_map <CourseClass*, bool> roomErrors;

	unordered_map <CourseClass*, bool> timeErrors;

	void CheckGroupsTime(CourseClass*, int i, long double &classCounter);
	void CheckTeachersTime(CourseClass*, int i, long double &classCounter);
	void Chromosome::CheckGroupsTimeWithoutWeek(CourseClass* class_main, int i, long double &classCounter);

	void checkLastClassesGroups(long double &classCounter);
	void checkLastClassesTeachers();
//	void checkLastClassesTeachers();
public:
	int errorCounter = 0;
	Chromosome* randomChromosome();
	void copyChromosome(Chromosome*);
	void setDefaultValues();
	void clearAllExceptClasses();
	void crossover(Chromosome*, Chromosome*&, Chromosome*&);
	Chromosome* crossover(Chromosome* parent, Chromosome*& offspring);
	void mutation();
	void smartMutation();
	void createTimeLine();
	void calculateFitness();

	inline bool getValidSchedule() { return goodSchedule; }
	inline float getFitness() { return fitness; }
	unordered_map<CourseClass*, int> getClasses() { return classes; }
	inline int classesSize() { return classes.size(); }
	void saveResult();

	Chromosome();
	~Chromosome();
	//test
	void printChromosome();

};
