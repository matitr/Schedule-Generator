#include "SeparateSchedule.h"
#include "MainWindow.h"
#include "List.h"
#include <Windows.h>
#include <string>


void SeparateSchedule::run() {
	if (getFromFile()) {
//		teachers->printAll();
		//groups->printAll();
/*
		consoleEdit();
		prepareToSave();
		teachers->saveMainFile();
		teachers->saveAllToFiles();
		groups->saveAllToFiles();
*/
	}
}

bool SeparateSchedule::getFromFile(string fileDir) {
	int failLine;
	string failName;
	if (fileInput(fileDir, failLine, failName)) {
		IOStream.printText("File found");
		return true;
	}
	else {
		if (failLine != 0) {
			string strFailLine = to_string(failLine);
			IOStream.printText("Error in \"" + failName + "\" in " + strFailLine + " line.");
		}
		return false;
	}
}

bool SeparateSchedule::fileInput(string fileDir, int &failLine, string &failName) {
	fstream file;
	string line = "";
	int errorsCounter = 0;
	bool addSmartError = false;
	failLine = 0;
	file.open(fileDir, ios::in);
//	file.flush();
	if (file.good()) {
		failLine = 1;
		while (!file.eof()){
			s* lesson = new s;
			line = IOStream.getLineFile(file);
			if (line == "") { failLine++; continue; }
			if (!checkText(line, lesson, failName)) {
				delete lesson;
				file.close();
				return FAIL;
			}
			lesson->divideGroups();
			lesson->divideTeachers();
			addSmartError = false;
			if (!teachers->addSmart(lesson->hour, lesson->day, lesson->groups, lesson->teachers, lesson->subject, lesson->room, lesson->week, groups)) {
				IOStream.printText("Error: " +
					lesson->hour + " " + lesson->day + " " + lesson->groupString + " " + lesson->teachersString + " " + lesson->subject + " " + lesson->room);
				addSmartError = true;
				teachers->deleteLessonTeachers(lesson->hour, lesson->day, &lesson->groups, &lesson->teachers, lesson->subject, lesson->room, lesson->week, groups);
			}
			else {
				if (!rooms->addSmartRoom(lesson->hour, lesson->day, lesson->groups, lesson->teachers, lesson->subject, lesson->room, lesson->week)) {
					IOStream.printText("Room error: " +
						lesson->hour + " " + lesson->day + " " + lesson->groupString + " " + lesson->teachersString + " " + lesson->subject + " " + lesson->room);
					addSmartError = true;
					teachers->deleteLessonTeachers(lesson->hour, lesson->day, &lesson->groups, &lesson->teachers, lesson->subject, lesson->room, lesson->week, groups);
				}
			}

			if (addSmartError)
				errorsCounter++;

			failLine++;

			delete lesson;
		}
		teachers->delEmptyData();
		groups->delEmptyData();
		rooms->delEmptyData();
	}
	else {
		IOStream.printText("data.txt error");
//		delete lesson;
		file.close();
		return FAIL;
	}
//	delete lesson;
	if (errorsCounter > 0)
		IOStream.printText("Number of errors: " + to_string(errorsCounter));
	file.close();
	return SUCCESS;
}

void SeparateSchedule::consoleEdit() {
	bool quitEdit = false;
	int choice = -1;
	do {
		IOStream.printMenu();
		choice = consoleGetChoice();
		switch (choice) {
		case 0:
			teachers->printAll();
			break;
		case 1:
			if (consoleAdd())
				IOStream.printText("Zajecia dodane.");
			else IOStream.printText("Nie udalo sie wpisac do listy.\n");
			break;
		case 2:
			if (consoleDelLesson())
				IOStream.printText("Lekcja zostala usunieta.\n");
			else IOStream.printText("Nie mozna usunac podanej lekcji.\n");
			break;
		case 3:
			consoleDelTeacher();
			break;
		case 4:
			consoleDelGroup();
			break;
		case 5:
			prepareToSave();
			teachers->saveMainFile();
			teachers->saveAllToFiles();
			groups->saveAllToFiles();
			rooms->saveAllToFiles();
			IOStream.printText("Zapisano\n");
			break;
		case 6:
			quitEdit = true;
			break;
		default:
			IOStream.printText("Wybierz poprawnie\n");
			break;
		}
		IOStream.printText("-----------------------------\n");
	} while (!quitEdit);
}

int SeparateSchedule::consoleGetChoice() {
	bool success = false;
	int choice = -1;
	string pick = "";
	do {
		pick = IOStream.getLineIostream();
		if (pick.size() == 1) {
			if (isdigit(pick[0])) {
				choice = pick[0] - '0';
				success = true;
			}
		}
		if (!success) IOStream.printText("Wybierz poprawnie\n");
		IOStream.cinSync();
	} while (!success);
	return choice;
}

bool SeparateSchedule::consoleAdd() {
	IOStream.printText("Podaj lekcje wedlug przykladu: 10:15-11:45 pn gr2 Nowak Fizyka\n");
	string line = IOStream.getLineIostream();
	s* lesson = new s;
	string failName = "";
	if (!checkText(line, lesson, failName)) {
		delete lesson;
		return false;
	}
	lesson->divideGroups();
	if (!teachers->addSmart(lesson->hour, lesson->day, lesson->groups, lesson->teachers, lesson->subject, "room", lesson->week, groups)) {
		delete lesson;
		return false;
	}
	else {
		delete lesson;
		return true;
	}
}

bool SeparateSchedule::consoleDelLesson() {
	IOStream.printText("Podaj nazwisko nauczyciela i numer lekcji np. Nowak 0\n");
	string line = IOStream.getLineIostream(), name = "";
	int which = -1;
	size_t foundPos = 0, foundPosPrev = 0;
	if ((foundPos = line.find(" ")) != string::npos) {
		name = line.substr(0, foundPos);
		foundPosPrev = foundPos;
	}
	else {
		return false;
	}
	if ((foundPos = line.find(' ', foundPos + 1)) != string::npos) {
		return false;
	}
	else {
		string whichToConvert;
		whichToConvert = line.substr(foundPosPrev + 1, foundPos - foundPosPrev - 1);
		if (!strToInt(whichToConvert, which)) {
			return false;
		}
	}
	if (teachers->deleteLesson(name, which, groups)) {
		return true;
	}
	else return false;
}

bool SeparateSchedule::strToInt(string toConvert, int &converted) {
	converted = 0;
	if (toConvert.size() > 9 || toConvert.size() < 0) return false;
	for (int i = 0; i < toConvert.size(); i++) {
		if (isdigit(toConvert[i])) {
			int end = 1;
			for (int j = 0; j < toConvert.size() - i - 1; j++) end *= 10;
			converted += (toConvert[i] - '0') * end;
		}
		else return false;
	}

	return true;
}

bool SeparateSchedule::consoleDelTeacher() {
	IOStream.printText("Podaj nazwisko nauczyciela: ");
	string line = IOStream.getLineIostream();
	if (teachers->deleteDataMain(line, groups)) {
		IOStream.printText("Usunieto nauczyciela: " + line + ".\n");
		return true;
	}
	else {
		IOStream.printText("Nie mozna usunac podanego nauczyciela.\n");
		return false;
	}
}

bool SeparateSchedule::consoleDelGroup() {
	IOStream.printText("Podaj nazewe grupy: ");
	string line = IOStream.getLineIostream();
	if (groups->deleteDataMain(line, teachers)) {
		IOStream.printText("Usunieto grupe: " + line + "\n");
		return true;
	}
	else {
		IOStream.printText("Nie mozna usunac podanej grupy\n");
		return false;
	}
}

bool SeparateSchedule::checkText(string line, s* lesson, string& failName) {
	extractText(line, lesson);
	if (!checkHour(lesson->hour)) {
		failName = "godzina";
		return false;
	}

	if (lesson->day.find("Even") != string::npos) {
		lesson->day.erase(lesson->day.begin() + lesson->day.find("Even"), lesson->day.end());
		lesson->week = "Even";
	}
	if (lesson->day.find("Odd") != string::npos) {
		lesson->day.erase(lesson->day.begin() + lesson->day.find("Odd"), lesson->day.end());
		lesson->week = "Odd";
	}

	if (!checkDay(lesson->day)) {
		failName = "dzien tygodnia";
		return false;
	}
/*
	if (!checkGroup(lesson->group)) {
		failName = "grupa";
		return false;
	}
	
	if (!checkName(lesson->name)) {
		failName = "nazwisko";
		return false;
	}
	if (!checkSubject(lesson->subject)) {
		failName = "przedmiot";
		return false;
	}
	*/
	return true;
}

bool SeparateSchedule::extractText(string line, s* lesson) {
	size_t foundPos = 0, foundPosPrev = 0;
	if ((foundPos = line.find(' ')) != string::npos) {
		lesson->hour = line.substr(0, foundPos);
		foundPosPrev = foundPos;
	}
	else return false;
	if ((foundPos = line.find(' ', foundPos + 1)) != string::npos) {
		lesson->day = line.substr(foundPosPrev + 1, foundPos - foundPosPrev - 1);
		foundPosPrev = foundPos;
	}
	else return false;
	if ((foundPos = line.find(' ', foundPos + 1)) != string::npos) {
		lesson->groupString = line.substr(foundPosPrev + 1, foundPos - foundPosPrev - 1);
		foundPosPrev = foundPos;
	}
	else return false;
	if ((foundPos = line.find(' ', foundPos + 1)) != string::npos) {
		lesson->teachersString = line.substr(foundPosPrev + 1, foundPos - foundPosPrev - 1);
		foundPosPrev = foundPos;
	}
	else return false;
	if ((foundPos = line.find(' ', foundPos + 1)) != string::npos) {
		lesson->subject = line.substr(foundPosPrev + 1, foundPos - foundPosPrev - 1);
		foundPosPrev = foundPos;
	}
	else return false;

	lesson->room = line.substr(foundPos + 1);
	if (lesson->subject.size() == 0) return false;

	return true;
}

void SeparateSchedule::s::divideGroups() {
	size_t found;
	while ((found = groupString.find(',')) != string::npos) {
		string extracted(groupString.begin(), groupString.begin() + found);
		groupString.erase(groupString.begin(), groupString.begin() + found + 1);
		groups.push_back(extracted);
	}

	groups.push_back(groupString);
}

void SeparateSchedule::s::divideTeachers() {
	size_t found;
	while ((found = teachersString.find(',')) != string::npos) {
		string extracted(teachersString.begin(), teachersString.begin() + found);
		teachersString.erase(teachersString.begin(), teachersString.begin() + found + 1);
		teachers.push_back(extracted);
	}

	teachers.push_back(teachersString);
}

void SeparateSchedule::prepareToSave() {
	DWORD attribs = ::GetFileAttributesA("Schedule");
	if (attribs == INVALID_FILE_ATTRIBUTES) {
		system("mkdir Schedule");
	}

	attribs = ::GetFileAttributesA("Schedule/Teachers");
	if (attribs == INVALID_FILE_ATTRIBUTES) {
		system("cd Schedule & mkdir Teachers");
	}

	attribs = ::GetFileAttributesA("Schedule/Groups");
	if (attribs == INVALID_FILE_ATTRIBUTES) {
		system("cd Schedule & mkdir Groups");
	}

	attribs = ::GetFileAttributesA("Schedule/Rooms");
	if (attribs == INVALID_FILE_ATTRIBUTES) {
		system("cd Schedule & mkdir Rooms");
	}

	system("del /q Schedule\\*.txt");
	system("del /q Schedule\\Teachers\\*.txt");
	system("del /q Schedule\\Groups\\*.txt");
	system("del /q Schedule\\Rooms\\*.txt");
}

// 08:00-20:00    max range
// 0123456789
bool SeparateSchedule::checkHour(string text) {
	if (text.size() == 11) {
		for (int k = 0; k < 2; k++) {
			int pos = k * 6; // position = 0 or 6
			if (!(text[pos] >= '0' && text[pos] <= '2')) return false;
			if (!(text[1 + pos] >= '0' && text[1 + pos] <= '9')) return false;
			if (!(text[4 + pos] >= '0' && text[4 + pos] <= '9')) return false;
			if (text[2 + pos] != ':') return false;
			if (!(text[3 + pos] >= '0' && text[3 + pos] <= '5')) return false;
			// eceptions
			if (text[pos] == '2' && text[1 + pos] > '2') return false;
			if (text[pos] == '2' && text[1 + pos] == '2' && (text[3 + pos] != '0'
				|| text[4 + pos] != '0')) return false;
			if (text[pos] == '0' && text[1 + pos] < '8') return false;
		}
		if (text[5] != '-') return false;
	}
	else return false;

	if (text[0] < text[6]) return true;
	else if (text[0] > text[6]) return false;
	else { // ==
		if (text[1] < text[7]) return true;
		else if (text[1] > text[7]) return false;
		else { // ==
			if (text[3] < text[9]) return true;
			else if (text[3] > text[9]) return false;
			else return false; // lesson must be longer than 10 minutes
		}
	}
}
// 08:00-20:00    
// 0123456789

//pt
bool SeparateSchedule::checkDay(string text) {
	if (!(text == "pn" || text == "wt" || text == "sr" || text == "cz" ||
		text == "pt" || text == "sb" || text == "nd")) return false;
	return true;
}
//gr1
bool SeparateSchedule::checkGroup(string text) {
	if (text.size() == 3) {
		if (text[0] != 'g' || text[1] != 'r' || !isdigit(text[2]))
			return false;
	}
	else return false;

	return true;
}
//Kowalski
bool SeparateSchedule::checkName(string text) {
	if (!isupper(text[0])) return false;
	for (int i = 1; i < text.size(); i++) {
		if (!iswlower(text[i])) return false;
	}
	return true;
}
//Podstay Programowania
bool SeparateSchedule::checkSubject(string &text) {
	if (!isupper(text[0])) return false;
	for (int i = 1; i < text.size(); i++) {
		if (!islower(text[i])) {
			if ((text[i] == ' ' && ((i + 1) < text.size()) && islower(text[i + 1]))
				|| (text[i] == ' ' && ((i + 1) < text.size()) && text[i + 1] == 'i')) {
				i++;
			}
			else return false;
		}
	}
	return true;
}

SeparateSchedule::SeparateSchedule(){
	teachers = new List("Teachers");
	groups = new List("Groups");
	rooms = new List("Rooms");
}

SeparateSchedule::SeparateSchedule(MainWindow* _window){
    teachers = new List("Teachers");
    groups = new List("Groups");
    rooms = new List("Rooms");
//    IOStream = new InOut(_window);
    IOStream.setWindow(_window);
	window = _window;
}


SeparateSchedule::~SeparateSchedule(){
	teachers->deleteAll(groups);
	delete teachers;
	delete groups;
	delete rooms;
    //delete IOStream;
}
