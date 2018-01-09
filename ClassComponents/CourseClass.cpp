#include "CourseClass.h"
#include "Configuration.h"

int CourseClass::getRandomRoom() {
	int randomRoom, rooms = Configuration::getConfig().numberOfRooms();
	bool roomTagsGood;
	list <string> randomRoomTags;
	map <string, int>::iterator it;
	do {
		roomTagsGood = true;
		randomRoom = (rand() % rooms) + 1;

		for (it = roomTags.begin(); it != roomTags.end(); it++) {
			if (Configuration::getRoomTags(randomRoom).find((*it).first) == Configuration::getRoomTags(randomRoom).end()) {
				roomTagsGood = false;
				break;
			}

		}


	} while (Configuration::getConfig().roomSize(randomRoom) < requiredSize() || !roomTagsGood);
	int a = 0;
	if (randomRoom > 5)
		a = 5;
	randomRoom--;

	return randomRoom;
}

void CourseClass::addRoomTag(string roomTag) {
//	roomTags.push_back(roomTag);
	roomTags.insert(pair<string, int>(roomTag, 0));
}

bool CourseClass::compareTeachers(CourseClass* CC) {
//	if (CC->teacher == teacher) return true;
//	return false;
	for (list <Teacher*>::iterator iter = CC->teachers.begin(); iter != CC->teachers.end(); iter++) {
		for (list <Teacher*>::iterator iter1 = teachers.begin(); iter1 != teachers.end(); iter1++) {
			if (*iter == *iter1) {
				return true;
			}
		}
	}
	return false;
}

bool CourseClass::compareGroups(CourseClass* CC) {
	for (list <Group*>::iterator iter = CC->groups.begin(); iter != CC->groups.end(); iter++) {
		for (list <Group*>::iterator iter1 = groups.begin(); iter1 != groups.end(); iter1++) {
			if (*iter == *iter1) {
				return true;
			}
		}
	}
	return false;
}

CourseClass::CourseClass(Subject* _course, list <Teacher*>& _teachers , list <Group*>& _groups, int _duration) {
	subject = _course;
	duration = _duration;
	numOfRooms = 1;
	for (list <Group*>::iterator it = _groups.begin(); it != _groups.end(); it++) {
		groups.push_back(*it);
		requiredRoomSize += (*it)->numberOfStudents();
	}

	for (list <Teacher*>::iterator it = _teachers.begin(); it != _teachers.end(); it++) {
		teachers.push_back(*it);
	}

	classEveryWeek = true;
	configLine = "";
}


CourseClass::~CourseClass(){

}
