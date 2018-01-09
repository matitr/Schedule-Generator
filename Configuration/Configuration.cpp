#include "Configuration.h"
#include "Teacher.h"
#include "Subject.h"
#include "CourseClass.h"
#include "Group.h"
#include "Course.h"
#include "Room.h"
#include "Settings.h"
#include <fstream>
#include <cctype>
#include <algorithm>

Configuration Configuration::config;

void Configuration::printText(string text) {
	cout << text;
}

bool Configuration::configuration(ifstream& file, int& lineNumber, configFunctionPtr funPtr) {
	string line;
	lineNumber = 0;
	getLineFile(file, line);
	while (line != "#end" && !file.eof()) {
		lineNumber++;
		delSpaces(line);
		delComments(line);


		if (line.length() > 2 && !(this->*funPtr)(line))
			return false;
		getLineFile(file, line);
	}
	return true;
}

// id name
bool Configuration::addProf(string line) {
	string configLine = line;
	string idStr = divideText(line);
	int id = atoi(idStr.c_str());
	string name = divideText(line);
	if (id == 0 || name == "") return false;

	Teacher* t = new Teacher(id, name);
	teachers.insert(pair<int, Teacher*>(id, t));

	teachersClasses[t];
	t->setConfigLine(configLine);
	return true;
}

bool Configuration::addSubject(string line) {
	string configLine = line;
	string idStr = divideText(line);
	int id = atoi(idStr.c_str());
	string name = divideText(line);
	if (id == 0 || name == "") return false;

	Subject* c = new Subject(id, name);
	subjects.insert(pair<int, Subject*>(id, c));

	c->setConfigLine(configLine);
	return true;
}

bool Configuration::addGroup(string line) {
	string configLine = line;
	string idStr, name, sizeStr;

	idStr = divideText(line);
	name = divideText(line);
	sizeStr = divideText(line);
	if (name == "" || sizeStr == "") return false;
	int size = atoi(sizeStr.c_str());
	int id = atoi(idStr.c_str());
	Group* g = new Group(id, name, size);
	groups.insert(pair<int, Group*>(id, g));

	groupsClasses[g];
	g->setConfigLine(configLine);
	return true;
}

bool Configuration::addCourse(string line) {
	string configLine = line;
	string idStr, name;
	idStr = divideText(line);
	name = divideText(line);
	int id = atoi(idStr.c_str());

	if (id == 0 || name == "")
		return false;

	list<Group*> listGroup;
	
	

	//Multiple groups
	if (line[0] == '[') {
		if (line.find(']') == string::npos)
			return false;
		line.erase(0, 1);
	}

	for (int counter = 0, counterBreak = 0; counter <= counterBreak; counter++) {
		if ((line.find(',') < line.find(']')) && line.find(']') != string::npos)
			counterBreak = counter + 1;
			
		if (counter == counterBreak && line.find(']') != string::npos)
			line.erase(line.find(']'));

		string group = divideText(line);
		int idGroup = atoi(group.c_str());
		map<int, Group*>::iterator itGroup = groups.find(idGroup);
		if (itGroup == groups.end())
			return false;

		listGroup.push_back((*itGroup).second);
	}

	Course* c = new Course(id, name, listGroup);
	courses.insert(pair<int, Course*>(id, c));
	c->setConfigLine(configLine);
	return true;
}

bool Configuration::addRoom(string line) {
	string configLine = line;
	string name, sizeStr;

	name = divideText(line);
	sizeStr = divideText(line);
	if (name == "" || sizeStr == "") return false;
	int size = atoi(sizeStr.c_str());
	int id = getLowestIdRooms();
	Room* r = new Room(id, name, size);
	rooms.insert(pair<int, Room*>(id, r));

	getBeforeSymbol(line, '\"'); // delete first "
	string roomTags = getBeforeSymbol(line, '\"');
	getBeforeSymbol(roomTags, ':'); // delete #room_tags
	string tag = divideText(roomTags);
	while (tag != "") {
		r->addTag(tag);
		tag = divideText(roomTags);
	}

	r->setConfigLine(configLine);
	return true;
}
//subject,prof,duration,group group 
bool Configuration::addClass(string line) {
	string configLine = line;
	string subjectIdStr = divideText(line);
	int subjectId = atoi(subjectIdStr.c_str());
	if (subjects.find(subjectId) == subjects.end()) return false;
	Subject* c = (*subjects.find(subjectId)).second;

	string teachersString = "";
	if (line.size() && line[0] == '[')
		teachersString = getBeforeSymbol(line, ']');


	//Add teachers
	list<Teacher*> listTeachers;
	if (teachersString == "")
		teachersString = divideText(line);
	else if (teachersString.find('[') != string::npos) {
		teachersString.erase(teachersString.find('['), teachersString.find('[') + 1);
		if (line.find(',') != string::npos)
			line.erase(line.find(','), line.find(',') + 1);
	}
	else
		return false;

	while (teachersString != "") {
		string teachersIdStr = divideText(teachersString);
		int teacherId = atoi(teachersIdStr.c_str());

		if (teachers.find(teacherId) == teachers.end()) return false;
		Teacher* teacher = (*teachers.find(teacherId)).second;
		listTeachers.push_back(teacher);
	}

	string durationStr = divideText(line);
	//	int teacherId = atoi(teacherIdStr.c_str());
	int duration = atoi(durationStr.c_str());
	//	if (teachers.find(teacherId) == teachers.end())  return false;

	//	Teacher* t = (*teachers.find(teacherId)).second;
	// Add groups
	list<Group*> listGroup;
	string groupsString = "";
	groupsString = getBeforeSymbol(line, ']');
	if (groupsString == "")
		groupsString = divideText(line);
	else if (groupsString.find('[') != string::npos) {
		groupsString.erase(groupsString.find('['), groupsString.find('[') + 1);
		if (line.find(',') != string::npos)
			line.erase(line.find(','), line.find(',') + 1);
	}
	else
		return false;

	while (groupsString != "") {
		string groupsIdStr = divideText(groupsString);
		int groupId = atoi(groupsIdStr.c_str());

		if (groups.find(groupId) == groups.end()) return false;
		Group* group = (*groups.find(groupId)).second;
		listGroup.push_back(group);
	}

	CourseClass* cC = new CourseClass(c, listTeachers, listGroup, duration);
	coursesClasses.push_back(cC);

	while (line != "") {
		getBeforeSymbol(line, '\"');
		string classRequrements = getBeforeSymbol(line, '\"');
		string requrementsType = getBeforeSymbol(classRequrements, ':');

		if (requrementsType == "#room_tags") {
			while (classRequrements != "") {
				string roomTag = divideText(classRequrements);
				cC->addRoomTag(roomTag);
			}
		}
		else if (requrementsType == "#once_in_two_weeeks") {
			if (classRequrements == "false")
				cC->setClassEveryWeek(false);
			else if (classRequrements == "true") {
				cC->setClassEveryWeek(true);
			}
			else 
				return false;
		}
	}

	addToClassCounter(cC);
	cC->setConfigLine(configLine);
	return true;
}

bool Configuration::setSettings(string line) {
	string settingsType = getBeforeSymbol(line, ':');

	if (settingsType == "students_breaks_range") {
		int min = atoi(divideText(line).c_str());
		int max = atoi(divideText(line).c_str());

		if (!Settings::getSettings().setStudentBreaksRange(min, max))
			return false;
	}
	else if (settingsType == "students_start_range") {
		int min = atoi(divideText(line).c_str());
		int max = atoi(divideText(line).c_str());

		if (!Settings::getSettings().setStudentStartRange(min, max))
			return false;
	}
	else if (settingsType == "teachers_breaks_range") {
		int min = atoi(divideText(line).c_str());
		int max = atoi(divideText(line).c_str());

		if (!Settings::getSettings().setTeacherBreaksRange(min, max))
			return false;
	}
	else if (settingsType == "minimum_number_of_classes_per_day") {
		int min = atoi(divideText(line).c_str());

		if (!Settings::getSettings().setMinClassesPerDay(min))
			return false;
	}

	return true;
}

void Configuration::delSpaces(string& text) {
	if (text.size() < 2) return;
	for (int I = 0; I < text.size(); I++) {
		if (isspace(text[I])) {
			text.erase(text.begin() + I);
			I--;
		}
	}
}

void Configuration::delComments(string& line) {
	size_t found = line.find("//");
	if (found == string::npos)
		return;

	line.erase(found, line.length() - 1);
}

string Configuration::divideText(string& line) {
	size_t found = line.find(',');
	if (found == string::npos) {
		string temp = line;
		line = "";
		return temp;
	}
	if (found == 0) return "";
	string extracted(line.begin(), line.begin() + found);
	line.erase(line.begin() ,line.begin() + found + 1);
	return extracted;
}

string Configuration::getBeforeSymbol(string& line, char symbol) {
	size_t found = line.find(symbol);
	if (found == string::npos) {
//		string temp = line;
//		line = "";
		return "";
	}

//	if (found == 0) return "";
	string extracted(line.begin(), line.begin() + found);
	line.erase(line.begin(), line.begin() + found + 1);
	return extracted;
}
// public
bool Configuration::getFromFile(string& errorMessage, string fileDir) {
	if (alreadyGotFromFile)
		return true;
	ifstream file;
	string line;
	file.open(fileDir);
	if (file.good()) {
		int lineNumber = 1, fileLineNumber = 1;
		getLineFile(file, line);
		delSpaces(line);
		while (!file.eof()){
			if (line == "#prof") {
				if (!configuration(file, lineNumber, &Configuration::addProf)) {
					errorMessage = "Config file error in #prof in " + to_string(lineNumber) + " line, " + to_string(fileLineNumber + lineNumber) + " file line";
					printText(errorMessage + "\n");
					return false;
				}
			}
			else if (line == "#subject") {
				if (!configuration(file, lineNumber, &Configuration::addSubject)) {
					errorMessage = "Config file error in #subject in " + to_string(lineNumber) + " line, " + to_string(fileLineNumber + lineNumber) + " file line";
					printText(errorMessage + "\n");
					return false;
				}
			}
			else if (line == "#group") {
				if (!configuration(file, lineNumber, &Configuration::addGroup)) {
					errorMessage = "Config file error in #group in " + to_string(lineNumber) + " line, " + to_string(fileLineNumber + lineNumber) + " file line";
					printText(errorMessage + "\n");
					return false;
				}
			}
			else if (line == "#course") {
				if (!configuration(file, lineNumber, &Configuration::addCourse)) {
					errorMessage = "Config file error in #course in " + to_string(lineNumber) + " line, " + to_string(fileLineNumber + lineNumber) + " file line";
					printText(errorMessage + "\n");
					return false;
				}
			}
			else if (line == "#room") {
				if (!configuration(file, lineNumber, &Configuration::addRoom)) {
					errorMessage = "Config file error in #room in " + to_string(lineNumber) + " line, " + to_string(fileLineNumber + lineNumber) + " file line";
					printText(errorMessage + "\n");
					return false;
				}
			}
			else if (line == "#class") {
				if (!configuration(file, lineNumber, &Configuration::addClass)) {
					errorMessage = "Config file error in #class in " + to_string(lineNumber) + " line, " + to_string(fileLineNumber + lineNumber) + " file line";
					printText(errorMessage + "\n");
					return false;
				}
			}
			else if (line == "#settings") {
				if (!configuration(file, lineNumber, &Configuration::setSettings)) {
					errorMessage = "Config file error in #settings in " + to_string(lineNumber) + " line, " + to_string(fileLineNumber + lineNumber) + " file line";
					printText(errorMessage + "\n");
					return false;
				}
			}
			else
				fileLineNumber++;
			if (lineNumber > 0)
				fileLineNumber += lineNumber + 2;
			lineNumber = 0;
			getLineFile(file, line);
		}
	}
	else {
		printText("Blad pliku config\n");
		return false;
	}
	alreadyGotFromFile = true;
	return true;
}

void Configuration::saveConfig(string fileDir) {
	ofstream file;
	file.open(fileDir);

	if (!file.is_open())
		return;

	file << "#prof\n";
	for (map <int, Teacher*>::iterator it = teachers.begin(); it != teachers.end(); it++)
		file << "\t" + it->second->getConfigLine() + "\n";
	file << "#end\n\n";

	file << "#subject\n";
	for (map <int, Subject*>::iterator it = subjects.begin(); it != subjects.end(); it++)
		file << "\t" + it->second->getConfigLine() + "\n";
	file << "#end\n\n";

	file << "#group\n";
	for (map <int, Group*>::iterator it = groups.begin(); it != groups.end(); it++)
		file << "\t" + it->second->getConfigLine() + "\n";
	file << "#end\n\n";

	file << "#course\n";
	for (map <int, Course*>::iterator it = courses.begin(); it != courses.end(); it++)
		file << "\t" + it->second->getConfigLine() + "\n";
	file << "#end\n\n";

	file << "#class\n";
	for (list <CourseClass*>::iterator it = coursesClasses.begin(); it != coursesClasses.end(); it++)
		file << "\t" + (*it)->getConfigLine() + "\n";
	file << "#end\n\n";

	file << "#room\n";
	for (map <int, Room*>::iterator it = rooms.begin(); it != rooms.end(); it++)
		file << "\t" + it->second->getConfigLine() + "\n";
	file << "#end\n\n";


	saveSettings(file);

	file.close();
}

void Configuration::saveSettings(ofstream &file) {
	file << "#settings\n";
	file << "// 1 = 15 min\n";
	file << "\tstudents_breaks_range : 1, 2\n";
	file << "\tstudents_start_range : 1, 15\n";
	file << "\tteachers_breaks_range : 1, 1\n";
	file << "\tminimum_number_of_classes_per_day : 2\n";
	file << "#end";
}

int Configuration::getLowestIdTeachers() {
	if (teachers.empty())
		return 1;

	if (teachers.begin()->first > 1)
		return 1;

	int id = 0;

	for (map <int, Teacher*>::iterator it = teachers.begin(); it != teachers.end(); it++) {
		if (it->first != ++id)
			return id;
	}

	return id + 1;
}

int Configuration::getLowestIdGroups() {
	if (groups.empty())
		return 1;

	if (groups.begin()->first > 1)
		return 1;

	int id = 0;

	for (map <int, Group*>::iterator it = groups.begin(); it != groups.end(); it++) {
		if (it->first != ++id)
			return id;
	}

	return id + 1;
}

int Configuration::getLowestIdSubjects() {
	if (subjects.empty())
		return 1;

	if (subjects.begin()->first > 1)
		return 1;

	int id = 0;

	for (map <int, Subject*>::iterator it = subjects.begin(); it != subjects.end(); it++) {
		if (it->first != ++id)
			return id;
	}

	return id + 1;
}

int Configuration::getLowestIdCourses() {
	if (courses.empty())
		return 1;

	if (courses.begin()->first > 1)
		return 1;

	int id = 0;

	for (map <int, Course*>::iterator it = courses.begin(); it != courses.end(); it++) {
		if (it->first != ++id)
			return id;
	}

	return id + 1;
}

int Configuration::getLowestIdRooms() {
	if (rooms.empty())
		return 1;

	if (rooms.begin()->first > 1)
		return 1;

	int id = 0;

	for (map <int, Room*>::iterator it = rooms.begin(); it != rooms.end(); it++) {
		if (it->first != ++id)
			return id;
	}

	return id + 1;
}

bool Configuration::vatidateSafeDelProf(int id) {
	for (list<CourseClass*>::iterator it_class = coursesClasses.begin(); it_class != coursesClasses.end(); it_class++) {
		for (list<Teacher*>::iterator it_teacher = (*it_class)->getTeachers().begin(); it_teacher != (*it_class)->getTeachers().end(); it_teacher++)
			if ((*it_teacher)->getId() == id)
				return false;
	}

	return true;
}

bool Configuration::vatidateSafeDelSubject(int id) {
	for (list<CourseClass*>::iterator it_class = coursesClasses.begin(); it_class != coursesClasses.end(); it_class++) {
		if ((*it_class)->getSubject()->getId() == id)
			return false;
	}

	return true;
}

bool Configuration::vatidateSafeDelGroup(int id) {
	for (list<CourseClass*>::iterator it_class = coursesClasses.begin(); it_class != coursesClasses.end(); it_class++) {
		for (list<Group*>::iterator it_group = (*it_class)->getGroups().begin(); it_group != (*it_class)->getGroups().end(); it_group++)
			if ((*it_group)->getId() == id)
				return false;
	}

	return true;
}

bool Configuration::removeProf(int id, bool safeRemove) {
	if (!safeRemove) {
		list<CourseClass*> toDel;
		for (list<CourseClass*>::iterator it_class = coursesClasses.begin(); it_class != coursesClasses.end(); it_class++) {
			for (list<Teacher*>::iterator it_teacher = (*it_class)->getTeachers().begin(); it_teacher != (*it_class)->getTeachers().end(); it_teacher++)
				if ((*it_teacher)->getId() == id)
					toDel.push_back(*it_class);
		}

		for (auto it = toDel.begin(); it != toDel.end(); it++)
			removeClass(*it);
	}
	Teacher* t = teachers[id];
	teachers.erase(id);
	delete t;

	return true;
}

bool Configuration::removeSubject(int id, bool safeRemove) {
	Subject* s = subjects[id];
	subjects.erase(id);
	delete s;

	return true;
}

bool Configuration::removeGroup(int id, bool safeRemove) {
	if (!safeRemove) {
		list<CourseClass*> toDel;
		for (list<CourseClass*>::iterator it_class = coursesClasses.begin(); it_class != coursesClasses.end(); it_class++) {
			for (list<Group*>::iterator it_group = (*it_class)->getGroups().begin(); it_group != (*it_class)->getGroups().end(); it_group++)
				if ((*it_group)->getId() == id)
					toDel.push_back(*it_class);
		}

		for (auto it = toDel.begin(); it != toDel.end(); it++)
			removeClass(*it);
	}
	Group *g = groups[id];
	groups.erase(id);
	delete g;

	return true;
}

bool Configuration::removeCourse(int id) {
	Course *c = courses[id];
	courses.erase(id);
	delete c;

	return true;
}

bool Configuration::removeRoom(int id) {
	Room *r = rooms[id];
	rooms.erase(id);
	delete r;

	return true;
}

bool Configuration::removeClass(CourseClass* classC) {
	vector<CourseClass*>::iterator temp;

	for (list<Group*>::iterator it_group = classC->getGroups().begin(); it_group != classC->getGroups().end(); it_group++) {
		groupsClasses[*it_group].erase(std::find(groupsClasses[*it_group].begin(), groupsClasses[*it_group].end(), classC));
	}

	for (list<Teacher*>::iterator it_teacher = classC->getTeachers().begin(); it_teacher != classC->getTeachers().end(); it_teacher++) {
		teachersClasses[*it_teacher].erase(std::find(teachersClasses[*it_teacher].begin(), teachersClasses[*it_teacher].end(), classC));
	}

	coursesClasses.remove(classC);
	delete classC;
	return true;
}


void Configuration::addToClassCounter(CourseClass* c) {
	for (list<Group*>::iterator it_group = c->getGroups().begin(); it_group != c->getGroups().end(); it_group++)
		groupsClasses[*it_group].push_back(c);

	for (list<Teacher*>::iterator it_teacher = c->getTeachers().begin(); it_teacher != c->getTeachers().end(); it_teacher++)
		teachersClasses[*it_teacher].push_back(c);
}

int Configuration::roomSize(int id) {
	return rooms.at(id)->getSize(); 
}

Configuration::Configuration(){
	alreadyGotFromFile = false;
}


Configuration::~Configuration() {
	if (teachers.size() > 0)
		for (map<int, Teacher*>::iterator it = teachers.begin(); it != teachers.end(); it++)
			if (it->second)
				delete it->second;

	if (subjects.size() > 0)
		for (map<int, Subject*>::iterator it = subjects.begin(); it != subjects.end(); it++)
			if (it->second)
				delete it->second;

	if (groups.size() > 0)
		for (map<int, Group*>::iterator it = groups.begin(); it != groups.end(); it++)
			if (it->second)
				delete it->second;

	if (rooms.size() > 0)
		for (map<int, Course*>::iterator it = courses.begin(); it != courses.end(); it++)
			if (it->second)
				delete it->second;

	if (rooms.size() > 0)
		for (map<int, Room*>::iterator it = rooms.begin(); it != rooms.end(); it++)
			if (it->second)
				delete it->second;

	if (coursesClasses.size() > 0)
		for (list <CourseClass*>::iterator it = coursesClasses.begin(); it != coursesClasses.end(); it++)
			if (*it)
				delete *it;
}

