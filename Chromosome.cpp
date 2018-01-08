#include "Chromosome.h"
#include "Configuration.h"
#include "CourseClass.h"
#include "Group.h"
#include <list>

Chromosome* Chromosome::randomChromosome() {
	Chromosome* ch = new Chromosome;
	list <CourseClass*> cC = Configuration::getConfig().getCoursesClasses();

	int rooms = Configuration::getConfig().numberOfRooms();

	for (list <CourseClass*>::iterator it = cC.begin(); it != cC.end(); it++) {

		int randPos = (rand() % NUMBER_OF_DAYS) * (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())
			+ (*it)->getRandomRoom() * (HOURS_IN_DAY * SLOTS_IN_HOUR)
			+ rand() % (HOURS_IN_DAY * SLOTS_IN_HOUR - (*it)->classDuration());

		ch->classes.insert(pair<CourseClass*, int>(*it, randPos));

		// Class not every week
		if (!(*it)->getClassEveryWeek()) {
			ch->classesWeek[*it] = rand() % 2;
		}
	}

	if (!ch->classesWeek.empty()) {
		ClassesTime::createForGroups(&ch->groupsTime[0]);
		ClassesTime::createForGroups(&ch->groupsTime[1]);
		ClassesTime::createForTeachers(&ch->teachersTime[0]);
		ClassesTime::createForTeachers(&ch->teachersTime[1]);
	}
	else {
		ClassesTime::createForTeachers(ch->teachersTime);
		ClassesTime::createForGroups(&ch->groupsTimeWithoutWeek);
	}

	ch->createTimeLine();
	ch->calculateFitness();

	return ch;
}

void Chromosome::copyChromosome(Chromosome* copyFrom) {
	//For every class
	for (unordered_map<CourseClass*, int>::iterator it = copyFrom->classes.begin(); it != copyFrom->classes.end(); it++) {
		classes[it->first] = copyFrom->classes[it->first];
		groupErrors[it->first] = copyFrom->groupErrors[it->first];
		profErrors[it->first] = copyFrom->profErrors[it->first];
		roomErrors[it->first] = copyFrom->roomErrors[it->first];
		timeErrors[it->first] = copyFrom->timeErrors[it->first];
	}

}

void Chromosome::setDefaultValues() {
	//	classes.clear();
	clearAllExceptClasses();
}

void Chromosome::clearAllExceptClasses() {
	goodSchedule = false;
	for (int i = 0; i < 2; i++) {
		for (unordered_map<string, Values>::iterator it_times = groupsTime[i].begin(); it_times != groupsTime[i].end(); it_times++) {
			(*it_times).second.day = -1;
			(*it_times).second.numberOfClasses = 0;
			(*it_times).second.breaksLonger = 0;
			(*it_times).second.totalStartTime = 0;
		}

		for (unordered_map<string, Values>::iterator it_times = teachersTime[i].begin(); it_times != teachersTime[i].end(); it_times++) {
			(*it_times).second.day = -1;
			(*it_times).second.numberOfClasses = 0;
			(*it_times).second.breaksLonger = 0;
			(*it_times).second.totalStartTime = 0;
		}
	}

	for (unordered_map<string, Values>::iterator it_times = groupsTimeWithoutWeek.begin(); it_times != groupsTimeWithoutWeek.end(); it_times++) {
		(*it_times).second.day = -1;
		(*it_times).second.numberOfClasses = 0;
		(*it_times).second.breaksLonger = 0;
		(*it_times).second.totalStartTime = 0;
	}

	for (int i = 0; i < timeLine.size(); i++)
		timeLine[i].clear();

	list<CourseClass*> classesL = Configuration::getConfig().getCoursesClasses();
	for (list<CourseClass*>::iterator it = classesL.begin(); it != classesL.end(); it++) {
		groupErrors[*it] = false;
		profErrors[*it] = false;
		roomErrors[*it] = false;
		timeErrors[*it] = false;

		for (list<Group*>::iterator it_group = (*it)->getGroups().begin(); it_group != (*it)->getGroups().end(); it_group++) {
			groupErrorsDetails[*it][*it_group] = false;
		}
	}

	goodSchedule = false;
	errorCounter = 0;
	fitness = 0;
}

void Chromosome::crossover(Chromosome* parent, Chromosome*& offspring0, Chromosome*& offspring1) {
	offspring0->setDefaultValues();
	offspring1->setDefaultValues();
	int size = classesSize();
	int crossoverPointsSize = rand() % (size);
	if (rand() % 100 < 15) crossoverPointsSize = 0;
	vector <bool> crossoverPoints;
	crossoverPoints.resize(size);

	for (int k = 0; k < crossoverPointsSize; k++) {
		int random;
		do {
			random = rand() % size;
		} while (crossoverPoints[random]);
		crossoverPoints[random] = true;
	}
	bool mainParent = true;

	unordered_map <CourseClass*, int>::iterator it;
	int i = 0;
	for (it = classes.begin(); it != classes.end(); it++, i++) {
		if (crossoverPoints[i]) mainParent = !mainParent;

		if (mainParent) {
			offspring0->classes[it->first] = classes[it->first];
			offspring1->classes[it->first] = parent->classes[it->first];

			if (!it->first->getClassEveryWeek()) {
				offspring0->classesWeek[it->first] = classesWeek[it->first];
				offspring1->classesWeek[it->first] = parent->classesWeek[it->first];
			}
		}
		else {
			offspring1->classes[it->first] = classes[it->first];
			offspring0->classes[it->first] = parent->classes[it->first];

			if (!it->first->getClassEveryWeek()) {
				offspring1->classesWeek[it->first] = classesWeek[it->first];
				offspring0->classesWeek[it->first] = parent->classesWeek[it->first];
			}
		}
	}

	offspring0->mutation();
	offspring1->mutation();
	offspring0->createTimeLine();
	offspring1->createTimeLine();
	offspring0->calculateFitness();
	offspring1->calculateFitness();
}

Chromosome* Chromosome::crossover(Chromosome* parent, Chromosome*& offspring) {
	int size = classesSize();
	int crossoverPoint = rand() % size;
	bool mainParent = rand() % 2;
	//	Chromosome* offspring = new Chromosome;
	unordered_map<CourseClass*, int>::iterator par0 = classes.begin();
	unordered_map<CourseClass*, int>::iterator par1 = parent->classes.begin();
	if (rand() % 100 > 80) crossoverPoint = -1;
	for (int i = 0; i < size; i++) {
		if (i == crossoverPoint) mainParent = !mainParent;

		if (mainParent) {
			offspring->classes.insert(pair<CourseClass*, int>(par0->first, par0->second));
		}
		else {
			offspring->classes.insert(pair<CourseClass*, int>(par1->first, par1->second));
		}

		par0++;
		par1++;
	}
	offspring->mutation();
	offspring->createTimeLine();
	offspring->calculateFitness();
	return offspring;
}

void Chromosome::mutation() {
	if (rand() % 100 < 5) return;

	for (unordered_map<CourseClass*, int>::iterator it = classes.begin(); it != classes.end(); it++) {
		if (rand() % 100 < MUTATION_CHANCE) {
			int randomNumber = rand() % 100;
			if (rand() % 100 < 85) {

				it->second = (rand() % NUMBER_OF_DAYS) * (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())
					+ (*it).first->getRandomRoom() * (HOURS_IN_DAY * SLOTS_IN_HOUR)
					+ rand() % (HOURS_IN_DAY * SLOTS_IN_HOUR - it->first->classDuration());

				if (!it->first->getClassEveryWeek()) {
					classesWeek[it->first] = rand() % 2;
				}
			}
			else if (randomNumber < 10) { // Change only room
				int day = it->second / (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms());
				int time = (it->second % (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())) % (HOURS_IN_DAY * SLOTS_IN_HOUR);

				it->second = day * (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())
					+ (*it).first->getRandomRoom() * (HOURS_IN_DAY * SLOTS_IN_HOUR)
					+ time;

				if (!it->first->getClassEveryWeek()) {
					classesWeek[it->first] = rand() % 2;
				}
			}
			else if (randomNumber < 60) { // Replace 2 classes
				CourseClass* random_class;
				if (rand() % 100 < 50) {
					list <Group*>::iterator it_group = it->first->getGroups().begin();
					randomNumber = rand() % it->first->getGroups().size();
					for (int countGroup = 0; countGroup < randomNumber; it_group++, countGroup++);

					randomNumber = rand() % Configuration::getConfig().getGroupsClasses()[*it_group].size();
					random_class = Configuration::getConfig().getGroupsClasses()[*it_group][randomNumber];
				}
				else {
					list <Teacher*>::iterator it_teacher = it->first->getTeachers().begin();
					randomNumber = rand() % it->first->getTeachers().size();
					for (int countGroup = 0; countGroup < randomNumber; it_teacher++, countGroup++);

					randomNumber = rand() % Configuration::getConfig().getTeachersClasses()[*it_teacher].size();
					random_class = Configuration::getConfig().getTeachersClasses()[*it_teacher][randomNumber];
				}
				int time = (classes[it->first] % (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())) % (HOURS_IN_DAY * SLOTS_IN_HOUR);
				int day = it->second / (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms());
				int daySecond = classes[random_class] / (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms());
				int timeSecond = (classes[random_class] % (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())) % (HOURS_IN_DAY * SLOTS_IN_HOUR);

				classes[random_class] = day * (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())
					+ random_class->getRandomRoom() * (HOURS_IN_DAY * SLOTS_IN_HOUR)
					+ time;

				classes[it->first] = daySecond * (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())
					+ (*it).first->getRandomRoom() * (HOURS_IN_DAY * SLOTS_IN_HOUR)
					+ timeSecond;



				return;
			}
			else { // Change time (+- 4 slots)
				int day = it->second / (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms());
				int time = (it->second % (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())) % (HOURS_IN_DAY * SLOTS_IN_HOUR);
				int room = ((*it).second % (SLOTS_IN_HOUR * HOURS_IN_DAY * Configuration::getConfig().numberOfRooms()) / (SLOTS_IN_HOUR * HOURS_IN_DAY));

				randomNumber = rand() % (SLOTS_IN_HOUR * HOURS_IN_DAY / 10) + 1;
				if (rand() % 2) {
					time = time - randomNumber;
					if (time < 0)
						time = 0;
				}
				else {
					time = time + randomNumber;
					if (time >= (SLOTS_IN_HOUR * HOURS_IN_DAY - it->first->classDuration()))
						time = SLOTS_IN_HOUR * HOURS_IN_DAY - it->first->classDuration() - 1;
				}

				it->second = day * (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())
					+ room * (HOURS_IN_DAY * SLOTS_IN_HOUR)
					+ time;
			}
		}
	}

}

void Chromosome::smartMutation() {
	int counter = 0, randomRoom = 0, randomNumber = 0, random_class = 0;
	int time = 0, roomSecond = 0, day = 0;
	bool roomTagsGood;

	list<pair<CourseClass*, int>>::iterator it_list;
	unordered_map <int, bool>::iterator it_rooms_available;
	map <string, int>::iterator it; //  rooms iterator
	list<pair<CourseClass*, int>>::iterator it_list_second;

#pragma region test
	unordered_map <CourseClass*, bool> groupErrorsTrue;
	unordered_map <CourseClass*, bool>::iterator it_group_errors;
	for (it_group_errors = groupErrors.begin(); it_group_errors != groupErrors.end(); it_group_errors++)
		groupErrorsTrue[it_group_errors->first] = true;
#pragma endregion
	int timeErrorsCounter = 0, timeErrorStop, couterClass = 0;
	for (unordered_map<CourseClass*, int>::iterator it = classes.begin(); it != classes.end(); it++) {
		if (timeErrors[it->first])
			timeErrorsCounter++;
	}

	if (timeErrorsCounter) {
		timeErrorStop = rand() % timeErrorsCounter;
	}

	for (int i = 0; i < timeLine.size(); i++) {
		if (!timeLine[i].empty()) {

			for (it_list = timeLine[i].begin(); it_list != timeLine[i].end(); it_list++) {
				day = i / (SLOTS_IN_HOUR * HOURS_IN_DAY);

				if (roomErrors[it_list->first] && rand() % 100 < 20) {
					unordered_map <int, bool> roomsAvailable;
					for (map <int, Room*>::iterator it_room = Configuration::getConfig().allRooms().begin(); it_room != Configuration::getConfig().allRooms().end(); it_room++) {
						do {
							roomTagsGood = true;
							randomRoom = (rand() % Configuration::getConfig().numberOfRooms()) + 1;

							for (it = it_list->first->getRoomTags().begin(); it != it_list->first->getRoomTags().end(); it++) {
								if (Configuration::getRoomTags(randomRoom).find((*it).first) == Configuration::getRoomTags(randomRoom).end()) {
									roomTagsGood = false;
									break;
								}
							}
						} while (Configuration::getConfig().roomSize(randomRoom) < it_list->first->requiredSize() || !roomTagsGood);

						roomsAvailable[randomRoom] = false;
					}

					// search after main lesson and get taken rooms
					for (int j = i; j < timeLine.size() && (j - i) <= it_list->first->classDuration() && (j / (SLOTS_IN_HOUR * HOURS_IN_DAY)) == day; j++) {

						if (i == j) {
							it_list_second = it_list;
							it_list_second++;
						}
						else
							it_list_second = timeLine[j].begin();

						for (it_list_second; it_list_second != timeLine[j].end(); it_list_second++)
							roomsAvailable.erase(it_list_second->second);
					}
					// Some rooms are not taken
					time = (classes[it_list->first] % (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())) % (HOURS_IN_DAY * SLOTS_IN_HOUR);
					if (!roomsAvailable.empty()) {
						randomRoom = rand() % roomsAvailable.size();
						counter = 0;
						for (it_rooms_available = roomsAvailable.begin(); counter < randomRoom; counter++)
							it_rooms_available++;

						randomRoom = it_rooms_available->first - 1;

						classes[it_list->first] = day * (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())
							+ randomRoom * (HOURS_IN_DAY * SLOTS_IN_HOUR)
							+ time;
					}
					else  // random room
						classes[it_list->first] = day * (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())
						+ it_list->first->getRandomRoom() * (HOURS_IN_DAY * SLOTS_IN_HOUR)
						+ time;
				}

				if (timeErrors[it_list->first] && (couterClass++ == timeErrorStop)) {
					randomNumber = rand() % 100;
					if (randomNumber < 30) { // Replace 2 classes

						CourseClass* random_class;
						if (rand() % 100 < 50) {
							list <Group*>::iterator it_group = it_list->first->getGroups().begin();
							randomNumber = rand() % it_list->first->getGroups().size();
							for (int countGroup = 0; countGroup < randomNumber; it_group++, countGroup++);

							randomNumber = rand() % Configuration::getConfig().getGroupsClasses()[*it_group].size();
							random_class = Configuration::getConfig().getGroupsClasses()[*it_group][randomNumber];
						}
						else {
							list <Teacher*>::iterator it_teacher = it_list->first->getTeachers().begin();
							randomNumber = rand() % it_list->first->getTeachers().size();
							for (int countGroup = 0; countGroup < randomNumber; it_teacher++, countGroup++);

							randomNumber = rand() % Configuration::getConfig().getTeachersClasses()[*it_teacher].size();
							random_class = Configuration::getConfig().getTeachersClasses()[*it_teacher][randomNumber];
						}
						int time = (classes[it_list->first] % (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())) % (HOURS_IN_DAY * SLOTS_IN_HOUR);
						int day = it_list->second / (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms());
						int daySecond = classes[random_class] / (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms());
						int timeSecond = (classes[random_class] % (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())) % (HOURS_IN_DAY * SLOTS_IN_HOUR);

						classes[random_class] = day * (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())
							+ random_class->getRandomRoom() * (HOURS_IN_DAY * SLOTS_IN_HOUR)
							+ time;

						classes[it_list->first] = daySecond * (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())
							+ (*it_list).first->getRandomRoom() * (HOURS_IN_DAY * SLOTS_IN_HOUR)
							+ timeSecond;



						return;
					}
					else if (randomNumber < 60) { // Change time 
						time = (classes[it_list->first] % (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())) % (HOURS_IN_DAY * SLOTS_IN_HOUR);

//						randomNumber = rand() % (SLOTS_IN_HOUR * HOURS_IN_DAY / 10);
						randomNumber = rand() % (8) + 1;
						if (0 || rand() % 2) {
							time = time - randomNumber;
							if (time < 0)
								time = 0;
						}
						else {
							time = time + randomNumber;
							if (time >= (SLOTS_IN_HOUR * HOURS_IN_DAY - it_list->first->classDuration()))
								time = SLOTS_IN_HOUR * HOURS_IN_DAY - it_list->first->classDuration() - 1;
						}

						classes[it_list->first] = day * (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())
							+ (it_list->second - 1) * (HOURS_IN_DAY * SLOTS_IN_HOUR)
							+ time;
						return;
					}
					else {
						classes[it_list->first] = (rand() % NUMBER_OF_DAYS) * (HOURS_IN_DAY * SLOTS_IN_HOUR * Configuration::getConfig().numberOfRooms())
							+ it_list->first->getRandomRoom() * (HOURS_IN_DAY * SLOTS_IN_HOUR)
							+ rand() % (HOURS_IN_DAY * SLOTS_IN_HOUR - it_list->first->classDuration());

						if (!it_list->first->getClassEveryWeek()) {
							classesWeek[it_list->first] = rand() % 2;
						}
						return;
					}

				}
			}
		}
	}

//	clearAllExceptClasses();
//	createTimeLine();
//	calculateFitness();
}

void Chromosome::createTimeLine() {

	for (unordered_map<CourseClass*, int>::iterator it = classes.begin(); it != classes.end(); it++) {
		timeLine[(it->second % (SLOTS_IN_HOUR * HOURS_IN_DAY)) + ((it->second / (Configuration::getConfig().numberOfRooms() * SLOTS_IN_HOUR * HOURS_IN_DAY))) * (HOURS_IN_DAY * SLOTS_IN_HOUR)]
			.push_back(pair<CourseClass*, int>
			(it->first, (it->second / (HOURS_IN_DAY * SLOTS_IN_HOUR) % Configuration::getConfig().numberOfRooms() + 1)));
	}
}

void Chromosome::calculateFitness() {
	fitness = 0;

	long double classCounter = 0; // maximum possible fitness
	long double tempFitness = 0;
	int numberOfRooms = Configuration::getConfig().numberOfRooms();

	int daySize = numberOfRooms * SLOTS_IN_HOUR * HOURS_IN_DAY;
	int counterMain = 0, counterSecond = 0, dayMain = 0, daySecond = 0;
	CourseClass* class_main = nullptr;

	for (int i = 0; i < timeLine.size(); i++) {
		if (!timeLine[i].empty()) {

			// For every class in slot 
			for (list<pair<CourseClass*, int>>::iterator it_list = timeLine[i].begin(); it_list != timeLine[i].end(); it_list++) {
				class_main = it_list->first;
				dayMain = i / (SLOTS_IN_HOUR * HOURS_IN_DAY);
				counterSecond = counterMain + 1;

				if (classesWeek.empty()) {
					CheckGroupsTimeWithoutWeek(class_main, i, classCounter);
				}
				else {
					CheckGroupsTime(class_main, i, classCounter);
					CheckTeachersTime(class_main, i, classCounter);
				}

				if (class_main->getGroups().size() > 2 && (i % (SLOTS_IN_HOUR * HOURS_IN_DAY) > 320))
					fitness += -150;

				// search after main lesson
				list<pair<CourseClass*, int>>::iterator it_list_second;
				for (int j = i; j < timeLine.size() && (j - i) <= class_main->classDuration() && (j / (SLOTS_IN_HOUR * HOURS_IN_DAY)) == dayMain; j++) {

					if (i == j) {
						it_list_second = it_list;
						it_list_second++;
					}
					else
						it_list_second = timeLine[j].begin();

					for (it_list_second; it_list_second != timeLine[j].end(); it_list_second++) {

						// Check classes week
						if (!(!class_main->getClassEveryWeek() && !it_list_second->first->getClassEveryWeek()
							&& ((classesWeek[it_list_second->first] == EVEN && classesWeek[class_main] == ODD)
								|| (classesWeek[it_list_second->first] == ODD && classesWeek[class_main] == EVEN)))) {

							if (it_list->second == it_list_second->second) { //same room
								roomErrors[it_list_second->first] = true;
								roomErrors[class_main] = true;
							}

							for (list<Group*>::iterator it_group_main = class_main->getGroups().begin(); it_group_main != class_main->getGroups().end(); it_group_main++) {
								for (list<Group*>::iterator it_group = it_list_second->first->getGroups().begin(); it_group != it_list_second->first->getGroups().end(); it_group++) {
									if ((*it_group_main) == (*it_group)) {
										groupErrorsDetails[class_main][*it_group] = true; // main error
										groupErrorsDetails[it_list_second->first][*it_group] = true;
									}
								}
							}


							if (class_main->compareTeachers(it_list_second->first)) {
								profErrors[it_list_second->first] = true;
								profErrors[class_main] = true;
							}

							counterSecond++;
						}
					}
				}
				counterMain++;
			}
			//			counterMain++;
		}
	}

	checkLastClassesGroups(classCounter);

	int classGroupsGood;
	long double temp;
	tempFitness = fitness;
	unordered_map<Group*, bool>::iterator it_group_error;
	for (list <CourseClass*>::iterator it = Configuration::getConfig().getCoursesClasses().begin(); it != Configuration::getConfig().getCoursesClasses().end(); it++) {
		classGroupsGood = 0;
		for (it_group_error = groupErrorsDetails[*it].begin(); it_group_error != groupErrorsDetails[*it].end(); it_group_error++)
			if (it_group_error->second == false) {
				classGroupsGood++;
				groupErrors[*it] = true;
			}


		temp = fitness;
		//		if (!groupErrors[*it]) fitness += 10 * ((*it)->groupsSize());

		fitness += 15 * classGroupsGood;
		if (!profErrors[*it]) fitness += 15 * ((*it)->groupsSize());
		if (!roomErrors[*it]) fitness += 15 * ((*it)->groupsSize()) + 20;
		classCounter += 45 * (*it)->groupsSize() + 20;

		if ((temp + 45 * (*it)->groupsSize()) + 20 != fitness)
			errorCounter++;
	}

	fitness = fitness / (classCounter);
}
// Check breakes and classes start time
void Chromosome::CheckGroupsTime(CourseClass* class_main, int i, long double &classCounter) {
	int breakSize = 0, week;
	long double tempFitness = 0, tempClassCounter = 0;
	int dayMain = i / (SLOTS_IN_HOUR * HOURS_IN_DAY);
	unordered_map<string, Values>::iterator it_group_time;
	for (list <Group*>::iterator group = class_main->getGroups().begin(); group != class_main->getGroups().end(); group++) {
		if (!class_main->getClassEveryWeek() && classesWeek[class_main] == ODD)
			week = 1;
		else
			week = 0;
		for (week; week < 2; week++) {
			it_group_time = groupsTime[week].find((*group)->getName()); // Always will find
			if ((*it_group_time).second.day != dayMain) { // First class in day
				 //Check number of classes
				if (!((*it_group_time).second.numberOfClasses > 0 && (*it_group_time).second.numberOfClasses < Settings::getMinNumberOfClasses()))
					tempFitness += 4;
//				else
//					tempFitness -= 70;
				it_group_time->second.totalStartTime += (i % (SLOTS_IN_HOUR * HOURS_IN_DAY));
				tempClassCounter += 4;
				if (((i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) >= Settings::getStudentStartMin() && (i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) <= Settings::getStudentStartMax()))
					tempFitness += 16+ (((SLOTS_IN_HOUR * HOURS_IN_DAY) - i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) / 10);
//				else if ((i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) < Settings::getStudentStartMin()) { /// ////////////////////
//					tempFitness += -90;
//				}
				else if (1) {
					tempFitness += -1600;
					timeErrors[class_main] = true;
				}
				else if (1) {
					timeErrors[class_main] = true;
					int temp;
					if ((i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) < Settings::getStudentStartMin())
						temp = Settings::getStudentStartMin() - (i % (SLOTS_IN_HOUR * HOURS_IN_DAY));
					else
						temp = (i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) - Settings::getStudentStartMax();

					tempFitness += 60 / (temp + 6);
//					tempFitness += (((SLOTS_IN_HOUR * HOURS_IN_DAY) - i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) / 20);
				}

				(*it_group_time).second.day = dayMain;
				(*it_group_time).second.numberOfClasses = 1;
				tempClassCounter += 16+ (((SLOTS_IN_HOUR * HOURS_IN_DAY) - i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) / 10);
			}
			else { // Not first class in day
				breakSize = (i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) - (*it_group_time).second.time;
				if (breakSize >= Settings::getStudentBreaksMin() && breakSize <= Settings::getStudentBreaksMax()) {
					tempFitness += 11;
					tempFitness += (((SLOTS_IN_HOUR * HOURS_IN_DAY) - i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) / 10);
				}
				else {
					timeErrors[class_main] = true;
					timeErrors[(*it_group_time).second.prevClass] = true;
					int temp = 0;
					if (breakSize >= 0) {
						(*it_group_time).second.breaksLonger += breakSize;// / 2;
						if (breakSize < Settings::getStudentBreaksMin())
							temp = (-0.6 * ((Settings::getStudentBreaksMin() - breakSize) * 1.5) + 8);
						else
							temp = -0.6 * (breakSize - Settings::getStudentBreaksMax()) + 8;
					}
					if (breakSize > 15) {
						tempFitness += -4;
					}
					else if (temp > 0 && temp <= 10)
						tempFitness += temp;// +(((SLOTS_IN_HOUR * HOURS_IN_DAY) - i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) / 20);
				}
				(*it_group_time).second.numberOfClasses += 1;
				tempClassCounter += 11;
				tempClassCounter += (((SLOTS_IN_HOUR * HOURS_IN_DAY) - i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) / 10);
			}
			(*it_group_time).second.prevClass = class_main;
			(*it_group_time).second.time = i % (SLOTS_IN_HOUR * HOURS_IN_DAY) + class_main->classDuration();

			if (!class_main->getClassEveryWeek() && classesWeek[class_main] == EVEN)
				week = 3;
		}

	}
	if (class_main->getClassEveryWeek()) {
		fitness += tempFitness / 2;
		classCounter += tempClassCounter / 2;
	}
	else {
		fitness += tempFitness / 2;
		classCounter += tempClassCounter / 2;
	}
}

void Chromosome::CheckTeachersTime(CourseClass* class_main, int i, long double &classCounter) {
	int breakSize = 0, week;
	int dayMain = i / (SLOTS_IN_HOUR * HOURS_IN_DAY);
	long double tempFitness = 0, tempClassCounter = 0;
	unordered_map<string, Values>::iterator it_teacher_time;

	for (list <Teacher*>::iterator it_teacher = class_main->getTeachers().begin(); it_teacher != class_main->getTeachers().end(); it_teacher++) {
		if (!class_main->getClassEveryWeek() && classesWeek[class_main] == ODD)
			week = 1;
		else
			week = 0;
		for (week; week < 2; week++) {
			it_teacher_time = teachersTime[week].find((*it_teacher)->getName()); // Always will find
			if ((*it_teacher_time).second.day != dayMain) { // First class in day
				//Check number of classes
				if (!((*it_teacher_time).second.numberOfClasses > 0 && (*it_teacher_time).second.numberOfClasses < Settings::getMinNumberOfClasses()))
					tempFitness += 2;
				else {
					timeErrors[class_main] = true;

				}
				tempClassCounter += 2;
				(*it_teacher_time).second.day = dayMain;
				(*it_teacher_time).second.numberOfClasses = 1;

			}
			else { // Not first class in day
				breakSize = (i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) - (*it_teacher_time).second.time;
				if (breakSize >= Settings::getTeacherBreaksMin() && breakSize <= Settings::getTeacherBreaksMax())
					tempFitness += 10;
				else {
					timeErrors[class_main] = true;
					timeErrors[(*it_teacher_time).second.prevClass] = true;
					int temp = 0;
					if (breakSize >= 0) {
						(*it_teacher_time).second.breaksLonger += breakSize;// / 2;
						if (breakSize < Settings::getStudentBreaksMin())
							temp = (-0.6 * ((Settings::getStudentBreaksMin() - breakSize) * 1.5) + 7);
						else
							temp = -0.6 * (breakSize - Settings::getStudentBreaksMax()) + 7;
					}
					if (temp > 0)
						tempFitness += temp;

				}
				(*it_teacher_time).second.numberOfClasses += 1;
				tempClassCounter += 10;
			}
			(*it_teacher_time).second.prevClass = class_main;

			(*it_teacher_time).second.time = i % (SLOTS_IN_HOUR * HOURS_IN_DAY) + class_main->classDuration();
		}
	}
	if (class_main->getClassEveryWeek()) {
		fitness += tempFitness / 2;
		classCounter += tempClassCounter / 2;
	}
	else {
		fitness += tempFitness / 2;
		classCounter += tempClassCounter / 2;
	}
}

void Chromosome::CheckGroupsTimeWithoutWeek(CourseClass* class_main, int i, long double &classCounter) {
	int breakSize = 0;
	int dayMain = i / (SLOTS_IN_HOUR * HOURS_IN_DAY);
	unordered_map<string, Values>::iterator it_group_time;
	for (list <Group*>::iterator group = class_main->getGroups().begin(); group != class_main->getGroups().end(); group++) {
		it_group_time = groupsTimeWithoutWeek.find((*group)->getName()); // Always will find
		if ((*it_group_time).second.day != dayMain) { // First class in day
			//Check number of classes
			if (!((*it_group_time).second.numberOfClasses > 0 && (*it_group_time).second.numberOfClasses < Settings::getMinNumberOfClasses()))
				fitness += 4;

			classCounter += 4;
			if (((i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) >= Settings::getStudentStartMin() && (i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) <= Settings::getStudentStartMax()))
				fitness += 16;
			else if (0 && (i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) - Settings::getStudentStartMax() > 210)
				fitness -= 1150;
			else if (1) {
				timeErrors[class_main] = true;
				int temp;
				if ((i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) < Settings::getStudentStartMin())
					temp = Settings::getStudentStartMin() - (i % (SLOTS_IN_HOUR * HOURS_IN_DAY));
				else
					temp = (i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) - Settings::getStudentStartMax();

				fitness += 60 / (temp + 6);
			}

			(*it_group_time).second.day = dayMain;
			(*it_group_time).second.numberOfClasses = 1;
			classCounter += 16;
		}
		else { // Not first class in day
			breakSize = (i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) - (*it_group_time).second.time;
			if (breakSize >= Settings::getStudentBreaksMin() && breakSize <= Settings::getStudentBreaksMax()) {
				fitness += 10;
				fitness += (((SLOTS_IN_HOUR * HOURS_IN_DAY) - i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) / 10);
			}
			else {
				timeErrors[class_main] = true;
				int temp = 0;
				if (breakSize >= 0) { // if after previous class
					(*it_group_time).second.breaksLonger += breakSize;
					if (breakSize < Settings::getStudentBreaksMin())
						temp = -0.6 * ((Settings::getStudentBreaksMin() - breakSize) * 1.6 ) + 8;
					else
						temp = -0.6 * (breakSize - Settings::getStudentBreaksMin()) + 8;
				}
				if (breakSize > 77) {
					fitness = fitness - 1140;
				}
				else if (temp <= 10)
					fitness += temp;
//				(*it_group_time).second.breaksLonger += breakSize;
			}
			(*it_group_time).second.numberOfClasses += 1;
			classCounter += 10;
			classCounter += (((SLOTS_IN_HOUR * HOURS_IN_DAY) - i % (SLOTS_IN_HOUR * HOURS_IN_DAY)) / 10);
		}

		(*it_group_time).second.time = i % (SLOTS_IN_HOUR * HOURS_IN_DAY) + class_main->classDuration();

	}
}

void Chromosome::checkLastClassesGroups(long double &classCounter) {
//	unordered_map<string, Values>::iterator it_time;
//	int breaks = 0;
	/*
	for (int i = 0; i < 2; i++) { // odd and even
		for (it_time = groupsTime[i].begin(); it_time != groupsTime[i].end(); it_time++) {

			if (!(groupsTime[i][it_time->first].numberOfClasses > 0 && groupsTime[i][it_time->first].numberOfClasses < Settings::getMinNumberOfClasses()))
				fitness += 4 / 2;
//			else
//				fitness += -5555;

			classCounter += 4 / 2;

			if (groupsTime[i][it_time->first].totalStartTime > 25)
				fitness -= groupsTime[i][it_time->first].totalStartTime * 450;

			//			breaks += groupsTime[0][it_time->first].breaksLonger;
//			if (groupsTime[i][it_time->first].breaksLonger > 25)
//				fitness -= groupsTime[i][it_time->first].breaksLonger * 333;
		}


	}
	*/

	map <int, Group*> groups = Configuration::getConfig().groupsAll();
	int i, startAndBreak;

	for (auto it_groups = groups.begin(); it_groups != groups.end(); it_groups++) {
		startAndBreak = 0;
		for (i = 0; i < 2; i++) {

			if (!(groupsTime[i][it_groups->second->getName()].numberOfClasses > 0 && groupsTime[i][it_groups->second->getName()].numberOfClasses < Settings::getMinNumberOfClasses()))
				fitness += 4 / 2;

			classCounter += 4 / 2;

			if (groupsTime[i][it_groups->second->getName()].totalStartTime > 25)
				fitness -= groupsTime[i][it_groups->second->getName()].totalStartTime * 450;

			startAndBreak += groupsTime[i][it_groups->second->getName()].totalStartTime + groupsTime[i][it_groups->second->getName()].breaksLonger;

			//			breaks += groupsTime[0][it_time->first].breaksLonger;
			//			if (groupsTime[i][it_time->first].breaksLonger > 25)
			//				fitness -= groupsTime[i][it_time->first].breaksLonger * 333;
		}
		if (startAndBreak > 40)
			fitness -= startAndBreak * 1323;
	}


	unordered_map<string, Values>::iterator it_time;

	for (int i = 0; i < 2; i++) { // odd and even
		for (it_time = teachersTime[i].begin(); it_time != teachersTime[i].end(); it_time++) {

			if (!(teachersTime[i][it_time->first].numberOfClasses > 0 && teachersTime[i][it_time->first].numberOfClasses < Settings::getMinNumberOfClasses()))
				fitness += 4 / 2;
//			else
//				fitness += -5555;

			classCounter += 4 / 2;

//			if (teachersTime[i][it_time->first].totalStartTime > 30)
//				fitness -= teachersTime[i][it_time->first].totalStartTime * 450;

			//			breaks += groupsTime[0][it_time->first].breaksLonger;
//			if (teachersTime[i][it_time->first].breaksLonger > 11)
//				fitness -= teachersTime[i][it_time->first].breaksLonger * 5444;
		}


	}

	for (it_time = groupsTimeWithoutWeek.begin(); it_time != groupsTimeWithoutWeek.end(); it_time++) {
		for (int i = 0; i < 2; i++) { // odd and even
			if (!(groupsTimeWithoutWeek[it_time->first].numberOfClasses > 0 &&
				groupsTimeWithoutWeek[it_time->first].numberOfClasses < Settings::getMinNumberOfClasses()))
				fitness += 4 / 2;

			classCounter += 4 / 2;

			if (groupsTimeWithoutWeek[it_time->first].breaksLonger > 17)
				fitness -= groupsTimeWithoutWeek[it_time->first].breaksLonger * 333;
		}


	}

		/*
				for (it_time = teachersTime[i].begin(); it_time != teachersTime[i].end(); it_time++) {
					if (!(it_time->second.numberOfClasses > 0 && it_time->second.numberOfClasses < Settings::getMinNumberOfClasses()))
						fitness += 2 / 2;

					classCounter += 2 / 2;
				}
				*/
//	}


	/*
	for (it_time = groupsTimeWithoutWeek.begin(); it_time != groupsTimeWithoutWeek.end(); it_time++) {
		if (!(it_time->second.numberOfClasses > 0 && it_time->second.numberOfClasses < Settings::getMinNumberOfClasses()))
			fitness += 4;

		classCounter += 4;

//		if (it_time->second.breaksLonger > 13)
//			fitness = fitness - it_time->second.breaksLonger * 35;
	}*/
}

void Chromosome::saveResult() {
	ofstream file;
	file.open("data.txt");
	int numberOfRooms = Configuration::getConfig().numberOfRooms();
	for (unordered_map<CourseClass*, int>::iterator it = classes.begin(); it != classes.end(); it++) {
		int daySize = numberOfRooms * SLOTS_IN_HOUR * HOURS_IN_DAY;
		int pointer = it->second;
		int room = ((*it).second % (SLOTS_IN_HOUR * HOURS_IN_DAY * numberOfRooms) / (SLOTS_IN_HOUR * HOURS_IN_DAY)) + 1;
		int time = pointer % (SLOTS_IN_HOUR * HOURS_IN_DAY);
		int hourS = (time / SLOTS_IN_HOUR) + 8;
		int minuteS = (time % SLOTS_IN_HOUR) * (60 / SLOTS_IN_HOUR);
		int dayInt = pointer / daySize;
		string hourSstring = "00";
		if (hourS < 10) {
			hourSstring[1] = hourS + '0';
		}
		else {
			int s = hourS % 10;
			hourSstring[0] = ((hourS - s) / 10) + '0';
			hourSstring[1] = '0' + s;
		}
		string minuteSstring = "00";
		if (minuteS < 10) {
			minuteSstring[1] = minuteS + '0';
		}
		else {
			int a = minuteS % 10;
			minuteSstring[0] = ((minuteS - a) / 10) + '0';
			minuteSstring[1] = a + '0';
		}

		int minuteF = minuteS + (*it).first->classDuration() * (60 / SLOTS_IN_HOUR);
		int hourF = hourS;
		while (minuteF > 45) {
			minuteF -= 60;
			hourF++;
		}
		//
		string hourFstring = "00";
		if (hourF < 10) {
			hourFstring[1] = hourF + '0';
		}
		else {
			int s = hourF % 10;
			hourFstring[0] = ((hourF - s) / 10) + '0';
			hourFstring[1] = '0' + s;
		}
		string minuteFstring = "00";
		if (minuteF < 10) {
			minuteFstring[1] = minuteF + '0';
		}
		else {
			int a = minuteF % 10;
			minuteFstring[0] = ((minuteF - a) / 10) + '0';
			minuteFstring[1] = a + '0';
		}
		//int dayMain = it->second / daySize;
		//int timeMain = it->second % daySize;
		string day;
		if (dayInt == 0) day = "pn";
		else if (dayInt == 1) day = "wt";
		else if (dayInt == 2) day = "sr";
		else if (dayInt == 3) day = "cz";
		else if (dayInt == 4) day = "pt";

		if (!(*it).first->getClassEveryWeek()) {
			if (classesWeek[(*it).first] == EVEN)
				day += "Even";
			else
				day += "Odd";
		}


		//	string roup it->first->
		//list<Group*> groups
		list<Group*>::iterator groups = it->first->getGroups().begin();

		InOut::saveLineFile(file, hourSstring + ":" + minuteSstring + "-" + hourFstring + ":" + minuteFstring
			+ " " + day + " ");

		int moreGroups = 0;
		for (groups; groups != it->first->getGroups().end(); groups++) {
			if (moreGroups)
				InOut::saveLineFile(file, ",");

			InOut::saveLineFile(file, (*groups)->getName());
			moreGroups++;
		}
		//		auto k = Configuration::getConfig().allRooms().at(room)->getName();
		InOut::saveLineFile(file, " ");

		int moreTeachers = 0;
		for (list<Teacher*>::iterator it_teacher = it->first->getTeachers().begin(); it_teacher != it->first->getTeachers().end(); it_teacher++) {
			if (moreTeachers)
				InOut::saveLineFile(file, ",");

			InOut::saveLineFile(file, (*it_teacher)->getName());
			moreTeachers++;
		}

		InOut::saveLineFile(file, " " + it->first->getSubject()->getName() + " " + Configuration::getConfig().allRooms().at(room)->getName() + "\n");
	}
	file.close();
}

Chromosome::Chromosome() {
	timeLine.resize(Settings::getTimeLineSize());




	list<CourseClass*> classesL = Configuration::getConfig().getCoursesClasses();
	/*
	for (list<CourseClass*>::iterator it = classes.begin(); it != classes.end(); it++)
	roomErrors[*it] = false;

	for (list<CourseClass*>::iterator it = classes.begin(); it != classes.end(); it++)
	groupErrors[*it] = false;
	*/

	for (list<CourseClass*>::iterator it = classesL.begin(); it != classesL.end(); it++) {
		groupErrors[*it] = false;
		profErrors[*it] = false;
		roomErrors[*it] = false;
		timeErrors[*it] = false;

		for (list<Group*>::iterator it_group = (*it)->getGroups().begin(); it_group != (*it)->getGroups().end(); it_group++) {
			groupErrorsDetails[*it][*it_group] = false;
		}
	}
}

Chromosome::~Chromosome() {

}