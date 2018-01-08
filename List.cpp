#include "List.h"
#include "InOut.h"
#include <string>
#include <iostream>
#include <fstream>
#include <list>

#define PLACED 1
#define NOTPLACED -1
#define CANPLACE 0
#define CANTPLACE -1

void List::addMainBeg(string text) {
	node * temp = new node;
	temp->dataMain = text;
	temp->next = nullptr;
	temp->prev = nullptr;
	if (head == nullptr) {
		head = tail = temp;
	}
	else {
		temp->next = head;
		head->prev = temp;
		head = temp;
		head->infoSize = 0;
	}
	sizeL++;
}

// Try add lesson. If it is first lesson in dataMain add to list and return PLACED, else return NOTPLACED
short List::addInformations(string n, List::node* &temp, Lesson* &lesson) {
	if (findData(n) == nullptr) {
		addMainBeg(n);
		head->infoHead = nullptr;
		head->infoTail = nullptr;
		head->infoSize = 0;
	}
	temp = findData(n);
	short canPlace = NOTPLACED;
	if (temp->infoHead == nullptr) {
		temp->infoHead = lesson;
		temp->infoTail = lesson;
		temp->infoSize++;
		canPlace = PLACED;
	}
	return canPlace;
}
// Find position to insert lesson
bool List::findPosition(List::node* namePtr, Lesson* lesson, Lesson* &positionPtr) {
	if (namePtr->infoHead == nullptr) {
		positionPtr = nullptr;
		return true;
	}
	Lesson* temp = namePtr->infoHead;
	while (temp != nullptr) {
		if (dayValue(temp->day) == dayValue(lesson->day)) {
			if (findTimePointer(namePtr, lesson, temp)) {
				//if (positionPtr == nullptr) positionPtr = namePtr->infoTail;
				positionPtr = temp;
				return true;
			}
			else {
				positionPtr = temp;
				return false;
			}
		}
		else if (dayValue(temp->day) > dayValue(lesson->day)) break;
		temp = temp->infoNext;
	}
	positionPtr = temp;
	return true;
}

//  10:00-12:00 wt gr2 Nowak Fizyka

// Find pointer before which you can insert lesson
// Find where time can be insert
bool List::findTimePointer(List::node* namePtr, Lesson* lesson, Lesson* &temp) {
	string infoHour = lesson->hour;
	string infoDay = lesson->day;
	string infoWeek = lesson->week;
	Lesson* fromPrevious = temp;

	// while temp is before lesson 
	while (temp != nullptr && (((temp->week == "Odd" && infoWeek == "Even") || (temp->week == "Even" && infoWeek == "Odd")) ||
		(timeCompare(temp->hour, infoHour) && dayValue(temp->day) == dayValue(infoDay))))
		temp = temp->infoNext;
	if (temp == nullptr) {
		if (((namePtr->infoTail->week == "Odd" && infoWeek == "Even") || (namePtr->infoTail->week == "Even" && infoWeek == "Odd")) ||
			(timeCompare(namePtr->infoTail->hour, infoHour) && dayValue(namePtr->infoTail->day) == dayValue(infoDay))){
//		if (timeCompare(namePtr->infoTail->hour, infoHour)
//			&& dayValue(namePtr->infoTail->day) == dayValue(infoDay)) {
			//temp = namePtr->infoHead;
			return true;
		}
		else if (timeCompare(infoHour, fromPrevious->hour)) {
			temp = fromPrevious;
			return true;
		}
		else {
			temp = fromPrevious;
			return false;
		}
	}

	// Right now temp is after lesson
/*
	while (temp != nullptr && timeCompare(infoHour, temp->hour)
		&& dayValue(temp->day) == dayValue(infoDay)) {
		temp = temp->infoNext;
	}
	*/
	while (temp != nullptr && (((temp->week == "Odd" && infoWeek == "Even") || (temp->week == "Even" && infoWeek == "Odd"))))
		temp = temp->infoNext;

	if (temp == nullptr) {
		if (timeCompare(namePtr->infoTail->hour, infoHour) /// !!!!!!
			&& dayValue(namePtr->infoTail->day) == dayValue(infoDay))
			return true;
		else 
			return false;
	}
	else if (dayValue(temp->day) == dayValue(infoDay)) {
		if (timeCompare(infoHour, temp->hour))
			return true;
		else 
			return false;
	}
}
// 08:30-10:00   size = 11

// Comparing times
// True if first time is before second
bool List::timeCompare(string timeList, string timeToInsert) { //timeList is in the list
	if (timeList[6] < timeToInsert[0]) return true;
	else if (timeList[6] > timeToInsert[0]) return false;
	else { // ==
		if (timeList[7] < timeToInsert[1]) return true;
		else if (timeList[7] > timeToInsert[1]) return false;
		else { // ==
			if (timeList[9] < timeToInsert[3]) return true;
			else if (timeList[9] > timeToInsert[3]) return false;
			else { // ==
				if (timeList[10] <= timeToInsert[4]) return true;
				else if (timeList[10] > timeToInsert[4]) return false;
			}
		}
	}
	return true;
}

short List::dayValue(string group) {
	if (group == "pn") return 0;
	if (group == "wt") return 1;
	if (group == "sr") return 2;
	if (group == "cz") return 3;
	else return 4; // pt
}

Lesson* List::createLesson(string hour, string day, string group, string teacher, string subject, string room, string week) {
	Lesson* lesson = new Lesson;
    lesson->hour = hour;
    lesson->day = day;
	lesson->group.push_back(group);
	lesson->teachers.push_back(teacher);
	lesson->subject = subject;
	lesson->room = room;
	lesson->week = week;
	lesson->infoNext = nullptr;
	lesson->infoPrev = nullptr;
	return lesson;
}

Lesson* List::createLesson(string hour, string day, list<string> groups, string teacher, string subject, string room, string week) {
	Lesson* lesson = new Lesson;
	lesson->day = day;
	for (list<string>::iterator it = groups.begin(); it != groups.end(); it++)
		lesson->group.push_back(*it);
	lesson->hour = hour;
    lesson->teachers.push_back(teacher);
	lesson->subject = subject;
	lesson->room = room;
	lesson->week = week;
	lesson->infoNext = nullptr;
	lesson->infoPrev = nullptr;
	return lesson;
}

Lesson* List::createLesson(string hour, string day, string group, list<string> teacher, string subject, string room, string week) {
	Lesson* lesson = new Lesson;
	lesson->day = day;
	for (list<string>::iterator it = teacher.begin(); it != teacher.end(); it++)
		lesson->teachers.push_back(*it);
	lesson->hour = hour;
	lesson->group.push_back(group);
	lesson->subject = subject;
	lesson->room = room;
	lesson->week = week;
	lesson->infoNext = nullptr;
	lesson->infoPrev = nullptr;
	return lesson;
}

Lesson* List::createLesson(string hour, string day, list<string> groups, list<string> teachers, string subject, string room, string week) {
	Lesson* lesson = new Lesson;
	lesson->day = day;
	for (list<string>::iterator it_teacher = teachers.begin(); it_teacher != teachers.end(); it_teacher++)
		lesson->teachers.push_back(*it_teacher);
	for (list<string>::iterator it_group = groups.begin(); it_group != groups.end(); it_group++)
		lesson->group.push_back(*it_group);
	lesson->hour = hour;
	lesson->subject = subject;
	lesson->room = room;
	lesson->week = week;
	lesson->infoNext = nullptr;
	lesson->infoPrev = nullptr;
	return lesson;
}

void List::delLessonNode(node* dataMain, Lesson* lesson) {
//	Lesson* temp1 = lesson->infoPrev;
//	Lesson* temp = lesson;
	if (!lesson) return;
	if (lesson == dataMain->infoHead) dataMain->infoHead = dataMain->infoHead->infoNext;
	if (lesson == dataMain->infoTail) dataMain->infoTail = dataMain->infoTail->infoPrev;
	if (lesson->infoNext != nullptr) lesson->infoNext->infoPrev = lesson->infoPrev;
	if (lesson->infoPrev != nullptr) lesson->infoPrev->infoNext = lesson->infoNext;

//	delete lesson->infoNext;
//	delete lesson->infoPrev;
//	delete lesson->otherListPtr;
	if (lessonRemovability)
		delete lesson;
	lesson = nullptr;
	dataMain->infoSize--;
}
// O = O = O = O
void List::delDataMainNode(node* toDel) {
	if (toDel == head) head = head->next;
	if (toDel == tail) tail = tail->prev;
	if (toDel->next != nullptr) toDel->next->prev = toDel->prev;
	if (toDel->prev != nullptr) toDel->prev->next = toDel->next;
	delete toDel;
	toDel = nullptr;
	sizeL--;
}
// Delete all empty lists
void List::delEmptyData() {
	node* temp = head;
	node* previous = head;
	while (temp != nullptr)	{
		if (temp->infoSize == 0) {
			if (temp == head && temp == tail) {
				delDataMainNode(temp);
				delete head;
				return;
			}
			else if (temp == head) {
				delDataMainNode(temp);
				previous = head;
				temp = head;
				continue;
			}
			else delDataMainNode(temp);
			temp = previous;
		}
		previous = temp;
		temp = temp->next;
	}
}
// true if the same
bool List::compareLists(list<string>* first, list<string>*second) {
	bool good = true;
	list<string>::iterator it_second;

	for (list<string>::iterator it_first = first->begin(); it_first != first->end(); it_first++) {
		good = false;
		for (it_second = second->begin(); it_second != second->end(); it_second++) {
			if ((*it_first) == (*it_second))
				good = true;
		}
		if (!good)
			return false;
	}

	return true;
}

void List::printText(string text) {
	cout << text;
}

// public
bool List::addSmart(string h, string d, list<string> group, list<string> teachers, string s, string room, string week, List* list1) {
	list<Lesson*> groupClassesAdded;

	for (list<string>::iterator it = group.begin(); it != group.end(); it++) {
		string g = (*it);
		node* temp1 = list1->findData(g);
        Lesson* info1 = createLesson(h, d, g, teachers, s, room, week);

		short canPlaceSecond = list1->addInformations(g, temp1, info1); // 1 if first lesson 

		if (canPlaceSecond != PLACED) {
			Lesson* positionToInsert1 = nullptr;

			if (canPlaceSecond == -1 && list1->findPosition(temp1, info1, positionToInsert1)) canPlaceSecond = CANPLACE;

			if (canPlaceSecond == CANTPLACE) {
				if (canPlaceSecond == PLACED) delLessonNode(temp1, info1);
				else delete info1;
				for (list<Lesson*>::iterator it_class = groupClassesAdded.begin(); it_class != groupClassesAdded.end(); it_class++) {
					delLessonNode(list1->findData(*(*it_class)->group.begin()), *it_class);
				}
				delEmptyData();
				list1->delEmptyData();
				return false;
			}

			if (canPlaceSecond == CANPLACE) {
				list1->insertBeforePointer(g, info1, positionToInsert1);
				temp1->infoSize++;
			}
		}

		groupClassesAdded.push_back(info1);
	}

	for (list<string>::iterator it_teacher = teachers.begin(); it_teacher != teachers.end(); it_teacher++) {
		string t = (*it_teacher);
		node* temp = findData(t);
		Lesson* lesson = createLesson(h, d, group, t, s, room, week);
		short canPlaceFirst = addInformations(t, temp, lesson); // 1 if first lesson 
		Lesson* positionToInsert = nullptr;
		if (canPlaceFirst == -1 && findPosition(temp, lesson, positionToInsert)) canPlaceFirst = CANPLACE;
		if (canPlaceFirst == CANTPLACE) {
			if (canPlaceFirst == PLACED) delLessonNode(temp, lesson);
			else delete lesson;
			delEmptyData();
			return false;

		}
		if (canPlaceFirst == CANPLACE) {
			insertBeforePointer(t, lesson, positionToInsert);
			temp->infoSize++;
		}
	}

	return true;
}

bool List::addSmartRoom(string hour, string day, list<string> group, list<string> teacher, string subject, string room, string week) {
	node* temp = findData(room);
	Lesson* lesson = createLesson(hour, day, group, teacher, subject, room, week);
	short canPlaceFirst = addInformations(room, temp, lesson); // 1 if first lesson 
	Lesson* positionToInsert = nullptr;
	if (canPlaceFirst == -1 && findPosition(temp, lesson, positionToInsert)) canPlaceFirst = CANPLACE;
	if (canPlaceFirst == CANTPLACE) {
		if (canPlaceFirst == PLACED) delLessonNode(temp, lesson);
		else delete lesson;
		delEmptyData();
		return false;

	}
	if (canPlaceFirst == CANPLACE) {
		insertBeforePointer(room, lesson, positionToInsert);
		temp->infoSize++;
	}

	return true;
}

void List::addLessonBeg(List::node* iterator, Lesson* lesson) {
	if (iterator->infoHead == nullptr) {
		lesson->infoNext = nullptr;
		lesson->infoPrev = nullptr;
		iterator->infoHead = iterator->infoTail;
	}
	else {
		lesson->infoNext = iterator->infoHead;
		iterator->infoHead->infoPrev = lesson;
		lesson->infoPrev = nullptr;
		iterator->infoHead = lesson;
	}
}

void List::addLessonEnd(List::node* iterator, Lesson* lesson) {
	if (iterator->infoTail == nullptr) {
		lesson->infoNext = nullptr;
		lesson->infoPrev = nullptr;
		iterator->infoHead = iterator->infoTail;
		return;
	}
	else {
		lesson->infoNext = nullptr;
		lesson->infoPrev = iterator->infoTail;
		iterator->infoTail->infoNext = lesson;
		iterator->infoTail = lesson;
	}
}
// 0 1 2 3 4  size 5   position 2
void List::insertBeforePointer(string name, Lesson* lesson, Lesson* position) {
	node* iterator = findData(name);
	if (position == nullptr) {
		addLessonEnd(iterator, lesson);
	}
	else if (position == iterator->infoHead) {
		addLessonBeg(iterator, lesson);
	}
	else {
		//Lesson* temp = new Lesson;
		lesson->infoNext = position;
		lesson->infoPrev = position->infoPrev;
		Lesson* temp = position->infoPrev;
		temp->infoNext = lesson;
		position->infoPrev = lesson;
	}
}
//  10:15-11:45 wt gr2 Nowak Fizyka

List::node* List::findData(string text) {
	node* temp = head;
	while (temp != nullptr) {
		if (temp->dataMain == text) return temp;
		temp = temp->next;
	}
	return nullptr;
}

int List::size() {
	return sizeL;
}

int List::infoSize(string name) {
	node* found = findData(name);
	if (found == nullptr) return 0;
	return findData(name)->infoSize;
}
/*
bool List::deleteLesson(string dataMain, int lessonNumber, List* groups) {
	return false;
}

bool List::deleteDataMain(string dataMain, List* groups) {
	return false;
}
*/
bool List::deleteLesson(string dataMain, int lessonNumber, List* groups) {
	if (lessonNumber < 0) return false;
	node* foundData = findData(dataMain);
	if (foundData == nullptr || lessonNumber >= foundData->infoSize) return false;
	Lesson* lessonToDel = foundData->infoHead;
	for (int i = 0; i < lessonNumber; i++) lessonToDel = lessonToDel->infoNext;
	Lesson* otherList = lessonToDel->otherListPtr;
	
	delLessonNode(foundData, lessonToDel);
	delEmptyData();
	
	for (list<string>::iterator it = lessonToDel->group.begin(); it != lessonToDel->group.end(); it++) {
		string g = (*it);
		node* foundGroup = groups->findData(g);
		groups->delLessonNode(foundGroup, otherList);

	}
	groups->delEmptyData();

	return true;
}
// from teachers
void List::deleteLessonTeachers(string hour, string day, list<string>*group, list<string>* teachers, string subject, string room, string week, List* groups) {
	for (list<string>::iterator it_teachers = teachers->begin(); it_teachers != teachers->end(); it_teachers++) {

		node* main = head;

		while (main && main->dataMain != *it_teachers)
			main = main->next;

		//delete from teachers
		if (main) {
			Lesson* lesson = main->infoHead;

			// find lesson
			while (lesson && !(lesson->hour == hour && lesson->day == day && lesson->subject == subject && lesson->week == week
				&& lesson->room == room && compareLists(&lesson->group, group)))

				lesson = lesson->infoNext;

			if (lesson)
				delLessonNode(main, lesson);
		}
	}

	groups->deleteLessonGroups(hour, day, group, teachers, subject, room);
}
// from groups
void List::deleteLessonGroups(string hour, string day, list<string>*group, list<string>* teachers, string subject, string room) {
	for (list<string>::iterator it_group = group->begin(); it_group != group->end(); it_group++) {

		node* main = head;

		while (main && main->dataMain != (*it_group))
			main = main->next;

		//delete from groups
		if (main) {
			Lesson* lesson = main->infoHead;

			// find lesson
			while (lesson && !(lesson->hour == hour && lesson->day == day && lesson->subject == subject
				&& lesson->room == room && compareLists(&lesson->teachers, teachers)))

				lesson = lesson->infoNext;

			if (lesson)
				delLessonNode(main, lesson);
		}
	}
}

bool List::deleteDataMain(string dataMain, List* groups) {
	if (sizeL < 0) return false;
	node* foundData = findData(dataMain);
	if (foundData == nullptr) return false;
	Lesson* toDel = foundData->infoHead;
	Lesson* toDelNext;
	int size = foundData->infoSize;
	for (int i = 0; i < size; i++) {
		Lesson* toDelNext = toDel->infoNext;
		delLessonNode(foundData, toDel);

		toDel = toDelNext;
	}

	if (groups) {
		node* groupsNode = groups->head;
		size = groups->sizeL;
		for (int i = 0; i < size; i++) {
			Lesson* groupLesson = groupsNode->infoHead;
			for (int j = 0; j < groupsNode->infoSize; j++) { // for every lesson
				Lesson* nextLesson = groupLesson->infoNext;
				// for every group(teacher)
				bool found = false;
				int counter = 0;
				int groupSize = groupLesson->group.size();
				for (list<string>::iterator it_group = groupLesson->group.begin(); !found && counter < groupSize; it_group++, counter++)
					if (*it_group == dataMain) {
						groups->delLessonNode(groupsNode, groupLesson);
						found = true;
						break;
					}

				groupLesson = nextLesson;
			}
			groupsNode = groupsNode->next;
		}
		groups->delEmptyData();
	}

	delEmptyData();
	foundData->infoSize = 0;
	//delDataMainNode(foundData);
	return true;
}

void List::deleteAll(List* groups) {
	node* toDel = head;
	int size = sizeL;
	for (int i = 0; i < size; i++) {
		node* toDelTemp = toDel->next;
		deleteDataMain(toDel->dataMain, groups);
		toDel = toDelTemp;
	}
	sizeL = 0;
}

map<string, list<Lesson*>>* List::createStandardList() {
	map<string, list<Lesson*>>* myData = new map<string, list<Lesson*>>;

	node* mainNode = head;
	for (int i = 0; i < sizeL; i++) {
		list<Lesson*> lessons;
		Lesson* lesson = mainNode->infoHead;

		for (int j = 0; j < mainNode->infoSize; j++) {
			lessons.push_back(lesson);

			lesson = lesson->infoNext;
		}

		(*myData)[mainNode->dataMain] = lessons;

		mainNode = mainNode->next;
	}

    return myData;
}

void List::printForward() {
	node* temp = head;
	while (temp != nullptr) {
		cout << temp->dataMain << " ";
		temp = temp->next;
	}
}

void List::printBackward() {
	node* temp = tail;
	while (temp != nullptr) {
		cout << temp->dataMain << " ";
		temp = temp->prev;
	}
}

void List::printInformations(string Name, bool printIndex) {
	node* foundPtr = findData(Name);
	if (foundPtr == nullptr) printText("Nauczyciel nie istnieje\n");
	Lesson* lesson = foundPtr->infoHead;
	int line = 0;
	while (lesson != nullptr) {
//		ostringstream ss;
//		ss << line;
//		string str = ss.str();
		string str = to_string(line);
		if (printIndex) printText("[" + str + "]     ");
		printText(lesson->hour + " ");
		printText(lesson->day + " ");
		for (list<string>::iterator it = lesson->group.begin(); it != lesson->group.end();) {
			string groupString = (*it);
			list<string>::iterator next = ++it;
			if (next != lesson->group.end())
				printText(groupString + ",");
			else
				printText(groupString + " ");
		}

		printText(lesson->subject + " " + lesson->room + "\n");
		lesson = lesson->infoNext;
		line++;
	} // problem z infoHead !!!
}

void List::printAll() {
	if (head == nullptr) {
		printText("Lista jest pusta");
		return;
	}
	node* temp = head;
	int line = 0;
	while (temp != nullptr) {
		printText("\n\n" + temp->dataMain + "\n");
		printInformations(temp->dataMain, 1);
		temp = temp->next;
	}
}

void List::saveMainFile() {
	ofstream file;
	file.open("data.txt");
	node* temp = tail;
	while (temp != nullptr) {
		Lesson* lesson = temp->infoHead;
		while (lesson != nullptr) {
			InOut::saveLineFile(file, lesson->hour + " " + lesson->day + " ");

			for (list<string>::iterator it = lesson->group.begin(); it != lesson->group.end();) {
				string groupString = (*it);
				list<string>::iterator next = ++it;
				if (next != lesson->group.end())
					InOut::saveLineFile(file, groupString + ",");
				else
					InOut::saveLineFile(file, groupString + " ");
			}

			InOut::saveLineFile(file, temp->dataMain + " " + lesson->subject + " " + lesson->room);

			if (temp->prev != nullptr || lesson->infoNext != nullptr) InOut::saveLineFile(file, "\n");
			lesson = lesson->infoNext;
		}
		temp = temp->prev;
	}
	file.close();
}

void List::saveAllToFiles() {
	if (sizeL == 0) return;
	int a = sizeL;
	ofstream file;
	node* temp = head;
	for (int i = 0; i < sizeL; i++) {
		file.open("Schedule\\" + label + "\\" + temp->dataMain + ".txt");
		Lesson* lesson = temp->infoHead;
		for (int j = 0; j < temp->infoSize; j++) {
			a = temp->infoSize;

			InOut::saveLineFile(file, lesson->hour + " " + lesson->day + " ");

			for (list<string>::iterator it = lesson->group.begin(); it != lesson->group.end();) {
				string groupString = (*it);
				list<string>::iterator next = ++it;
				if (next != lesson->group.end())
					InOut::saveLineFile(file, groupString + ",");
				else
					InOut::saveLineFile(file, groupString + " ");
			}

			InOut::saveLineFile(file, lesson->subject + " " + lesson->room);

			if (j + 1 != temp->infoSize) {
				InOut::saveLineFile(file, "\n");
				if (lesson->day != lesson->infoNext->day)
					InOut::saveLineFile(file, "\n");
			}
			lesson = lesson->infoNext;
		}
		temp = temp->next;
		file.close();
	}
}

List::node::node() {
	infoHead = nullptr;
	infoTail = nullptr;
	next = nullptr;
	prev = nullptr;
	infoSize = 0;
}

List::node::~node() {

}

Lesson::Lesson() {
    hour = "";
    day = "";
    subject = "";
    room = "";
	week = "Every";

	infoNext = nullptr;
	infoPrev = nullptr;
	otherListPtr = nullptr;
}

Lesson::~Lesson() {

}

List::List() {
	head = nullptr;
	tail = nullptr;
	sizeL = 0;
	label = "";
	lessonRemovability = true;
}

List::List(string _label) {
	head = nullptr;
	tail = nullptr;
	sizeL = 0;
	label = _label;
	lessonRemovability = true;
}


List::~List() {

}
