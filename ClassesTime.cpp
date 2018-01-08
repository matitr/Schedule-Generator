#include "ClassesTime.h"
#include "CourseClass.h"
#include "Group.h"
#include "Teacher.h"
#include "Configuration.h"
#include <unordered_map>
#include <map>


Values::Values() {
	time = 0;
	day = -1;
	numberOfClasses = 0;
	breaksLonger = 0;
	totalStartTime = 0;
	prevClass = nullptr;
}


Values::~Values(){

}

void ClassesTime::createForGroups(unordered_map<string, Values>* times) {
	map <int, Group*>::iterator it_groups = Configuration::getConfig().groupsAll().begin();

	for (it_groups; it_groups != Configuration::getConfig().groupsAll().end(); it_groups++) {
		times->insert(pair<string, Values>((*it_groups).second->getName(), Values()));
	}
}

void ClassesTime::createForTeachers(unordered_map<string, Values>* times) {
	map <int, Teacher*>::iterator it_teachers = Configuration::getConfig().teachersAll().begin();

	for (it_teachers; it_teachers != Configuration::getConfig().teachersAll().end(); it_teachers++) {
		times->insert(pair<string, Values>((*it_teachers).second->getName(), Values()));
	}
}


ClassesTime::ClassesTime() {

}


ClassesTime::~ClassesTime(){

}

