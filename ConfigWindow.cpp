#include "ConfigWindow.h"
#include "ui_configwindow.h"
#include "Configuration.h"
#include "Subject.h"
#include "Group.h"
#include "Course.h"
#include "Room.h"
#include "CourseClass.h"
#include "LineEdit.h"

#include <QPoint>
#include <QCompleter>
#include <QFileDialog>
#include <QMessageBox>

#define COLUMNS_GAP 10
#define CLASS 0
#define SUBJECT 1
#define TEACHER 2
#define GROUP 3
#define COURSE 4
#define ROOM 5

ConfigWindow::ConfigWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::ConfigWindow) {

	setAttribute(Qt::WA_DeleteOnClose, true);
	ui->setupUi(this);
	config = nullptr;
	this->setWindowTitle("Configuration");
	ui->editor_stackedW->setCurrentIndex(0);

	QSize windowSize = size();
	setMaximumHeight(windowSize.height());
	setMaximumWidth(windowSize.width());
	setMinimumHeight(windowSize.height());
	setMinimumWidth(windowSize.width());

	curShowing = None;
	configSaved = true;
	configFileDir = "";
	editing = false;
	itemClickedShowT = nullptr;

	createAllCompleters();
	ui->show_label->setAlignment(Qt::AlignHCenter);
	ui->show_label->setText("-");

	createMenus();
	setEditorValidators();

	connect(ui->classes_treeW, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(showGroupClassesSlot(QTreeWidgetItem*, int)));
	connect(ui->showConfig_treeW, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(getItemClickedShowT(QTreeWidgetItem*, int)));
}


ConfigWindow::~ConfigWindow() {
	delete ui;
	delete config;
}

void ConfigWindow::createMenus() {
	QMenu *menu;
	QAction *action;

// File menu
	menu = menuBar()->addMenu("File");
	action = new QAction("New", this);
	connect(action, SIGNAL(triggered()), this, SLOT(newConfig()));
	menu->addAction(action);

	action = new QAction("Open", this);
	connect(action, SIGNAL(triggered()), this, SLOT(openConfig()));
	menu->addAction(action);

	action = new QAction("Open file...", this);
	connect(action, SIGNAL(triggered()), this, SLOT(openFileConfig()));
	menu->addAction(action);

	actionSave = new QAction("Save", this);
	connect(actionSave, SIGNAL(triggered()), this, SLOT(saveConfig()));
	menu->addAction(actionSave);
	actionSave->setEnabled(false);

	action = new QAction("Save as...", this);
	connect(action, SIGNAL(triggered()), this, SLOT(saveAsConfig()));
	menu->addAction(action);

	actionClose = new QAction("Close file", this);
	connect(actionClose, SIGNAL(triggered()), this, SLOT(closeConfigFile()));
	menu->addAction(actionClose);
	actionClose->setEnabled(false);

// Show menu
	menu = menuBar()->addMenu("Show");
	menuShow = menu;
	menu->setEnabled(false);

	action = new QAction("Subjects", this);
	connect(action, SIGNAL(triggered()), this, SLOT(showSubjects()));
	menu->addAction(action);

	action = new QAction("Teachers", this);
	connect(action, SIGNAL(triggered()), this, SLOT(showTeachers()));
	menu->addAction(action);

	action = new QAction("Groups", this);
	connect(action, SIGNAL(triggered()), this, SLOT(showGroups()));
	menu->addAction(action);

	action = new QAction("Courses", this);
	connect(action, SIGNAL(triggered()), this, SLOT(showCourses()));
	menu->addAction(action);

	action = new QAction("Rooms", this);
	connect(action, SIGNAL(triggered()), this, SLOT(showRooms()));
	menu->addAction(action);
}	

void ConfigWindow::createGroupsClasses() {
	ui->classes_treeW->clear();

	CoursesTree coursesTreeHead;

	auto courses = config->coursesAll();
	for (auto it_course = courses.begin(); it_course != courses.end(); it_course++) {

		string coursesTxt = it_course->second->getName();
		CoursesTree* temp = &coursesTreeHead;
		size_t found = coursesTxt.find("/");

		while (found != string::npos) {
			string extracted(coursesTxt.begin(), coursesTxt.begin() + found);
			coursesTxt.erase(coursesTxt.begin(), coursesTxt.begin() + found + 1);

			if (temp->course.find(extracted) == temp->course.end())
				temp->course[extracted] = new CoursesTree();

			temp = temp->course[extracted];

			found = coursesTxt.find("/");
		}

		if (temp->course.find(coursesTxt) == temp->course.end())
			temp->course[coursesTxt] = new CoursesTree();

		temp = temp->course[coursesTxt];

		for (list<Group*>::iterator it_group = it_course->second->groupsAll().begin(); it_group != it_course->second->groupsAll().end(); it_group++)
			temp->groups.push_back((*it_group)->getName());

	}

//	show groups

	addGroupsClassesToTree(&coursesTreeHead, ui->classes_treeW);
}

void ConfigWindow::addGroupsClassesToTree(CoursesTree* coursesTree, QTreeWidget *parent) {
	if (!parent)
		return;

	for (list <string>::iterator it_group = coursesTree->groups.begin(); it_group != coursesTree->groups.end(); it_group++) {
		QTreeWidgetItem* groupItem = new QTreeWidgetItem(parent);
		groupItem->setText(0, QString::fromStdString(*it_group));
	}


	for (map<string, CoursesTree*>::iterator it_course = coursesTree->course.begin(); it_course != coursesTree->course.end(); it_course++) {
		QTreeWidgetItem* courseItem = new QTreeWidgetItem(parent);
		courseItem->setText(0, QString::fromStdString(it_course->first));

		addGroupsClassesToTree(it_course->second, courseItem);
	}
		
}

void ConfigWindow::addGroupsClassesToTree(CoursesTree* coursesTree, QTreeWidgetItem *parent) {
	if (!parent)
		return;

	for (list <string>::iterator it_group = coursesTree->groups.begin(); it_group != coursesTree->groups.end(); it_group++) {
		QTreeWidgetItem* item = new QTreeWidgetItem(parent);
		item->setText(0, QString::fromStdString(*it_group));
	}


	for (map<string, CoursesTree*>::iterator it_course = coursesTree->course.begin(); it_course != coursesTree->course.end(); it_course++) {
		QTreeWidgetItem* courseItem = new QTreeWidgetItem(parent);
		courseItem->setText(0, QString::fromStdString(it_course->first));

		addGroupsClassesToTree(it_course->second, courseItem);
	}

}

void ConfigWindow::setEditorValidators() {
	QIntValidator *validNumOfRooms = new QIntValidator(1, 20, this);
	QIntValidator *validNumOfStudents = new QIntValidator(1, 5000, this);
	QIntValidator *validRoomSize = new QIntValidator(1, 2000, this);
	QRegExp rx("[A-Za-z0-9_-]{0,999}");

	ui->addClass_nOfRooms->setValidator(validNumOfRooms);
	ui->addGroup_numOfStudents->setValidator(validNumOfStudents);
	ui->addRoom_size->setValidator(validRoomSize);
	ui->addGroup_name->setValidator(new QRegExpValidator(rx, this));
}

void ConfigWindow::setTreeWidgetColWidth() {
	int numberOfCol = ui->showConfig_treeW->columnCount();

	for (int i = 0; i < numberOfCol; i++) {
		ui->showConfig_treeW->resizeColumnToContents(i);
		ui->showConfig_treeW->setColumnWidth(i, ui->showConfig_treeW->columnWidth(i) + COLUMNS_GAP);
	}

	// Delete additional GAPS
	ui->showConfig_treeW->setColumnWidth(numberOfCol - 1, ui->showConfig_treeW->columnWidth(numberOfCol - 1) - (COLUMNS_GAP * numberOfCol));
}

void ConfigWindow::createAllCompleters() {
	createCompleter(ui->addClass_teachers, &teachersNames);
	createCompleter(ui->addClass_groups, &groupsNames);
	createCompleter(ui->addClass_roomTags, &roomsTags);

	createCompleter(ui->addCourse_name, &coursesNames);
	createCompleter(ui->addCourse_groups, &groupsNames);

	createCompleter(ui->addRoom_tags, &roomsTags);
}

void ConfigWindow::createCompleter(LineEdit* widget, QStringList* list) {
	QCompleter *completer = new QCompleter(this);

//	completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
//	completer->setCaseSensitivity(Qt::CaseSensitive);
	completer->setWrapAround(false);
	completer->setMaxVisibleItems(5);

	widget->setCompleter(completer);
	widget->setList(list);
}

bool ConfigWindow::addClass() {
	QString subjectText = ui->addClass_subject->text(),
		teachersText = ui->addClass_teachers->text(),
		groupsText = ui->addClass_groups->text(),
		durText = ui->addClass_duration->text(),
		roomTagsText = ui->addClass_roomTags->text(),
		numbOfRoomsText = ui->addClass_nOfRooms->text();
	bool defNumOfRooms = ui->addClass_defNumOfRooms_checkB->isChecked(),
		classEveryWeek = ui->addClass_everyWeek_checkB->isChecked(),
		addTaG = ui->addClass_addTaG_checkB->isChecked();

	int numbOfRooms = numbOfRoomsText.toInt();

	QStringList teachersList = teachersText.split(",");
	QStringList groupsList = groupsText.split(",");
	QStringList roomTagsList = roomTagsText.split(",");

	printInfoQS("-");

	string addClassLine = "";
	int id = 1;
	if (subjectsNames.contains(subjectText))
		id = subjects[subjectText.toStdString()]->getId();
	else {
		id = config->getLowestIdSubjects();
		addSubject(subjectText, false);
	}

	addClassLine += to_string(id) + ",[";

	foreach(QString teacher, teachersList) {
		if (teachersNames.contains(teacher))
			id = teachers[teacher.toStdString()]->getId();
		else {
			id = config->getLowestIdTeachers();
			addTeacher(teacher, false);
		}

		addClassLine += to_string(id) + ",";
	}

	addClassLine.pop_back();
	addClassLine += "],";

	int duration = durText.toInt();
	duration = duration / 15; // I want duration in slots not in min; 1 slot = 15min
	addClassLine += to_string(duration) + ",[";

	foreach(QString group, groupsList) {
		if (groupsNames.contains(group))
			id = groups[group.toStdString()]->getId();
		else {
			id = config->getLowestIdGroups();
			addGroup(group, "35", false);
		}

		addClassLine += to_string(id) + ",";
	}

	addClassLine.pop_back();
	addClassLine += "],\"#room_tags:";

	QString tags = "";
	foreach(QString tag, roomTagsList) {
		tags += tag + ",";
	}

	if (!tags.isEmpty())
		tags.chop(1);

	addClassLine += tags.toStdString() + "\", \"#once_in_two_weeeks:";

	if (classEveryWeek)
		addClassLine += "false";
	else
		addClassLine += "true";

	addClassLine += "\"";

	config->addClass(addClassLine);
	foreach(QString group, groupsList)
		groupClasses[group.toStdString()].push_back(config->lastAddedClass());

//	createGroupsClasses();
	printInfoQS("Class has been added");

	return true;
}

bool ConfigWindow::addSubject(QString subjectText, bool getFromField) {
	if (getFromField)
		subjectText = ui->addSubject_name->text();

	int id = config->getLowestIdSubjects();
	config->addSubject(to_string(id) + "," + subjectText.toStdString());
	subjectsNames << subjectText;
	subjects[subjectText.toStdString()] = config->getSubjectById(id);

	printInfoQS("Subject \"" + subjectText + "\" has been added");
	if (curShowing == CurrenltyShowing::Subjects) {
		showSubjects();
	}

	return true;
}

bool ConfigWindow::addTeacher(QString nameText, bool getFromField) {
	int id = config->getLowestIdTeachers();
	string text = to_string(id) + "," + nameText.toStdString();

	config->addProf(text);
	teachers[nameText.toStdString()] = config->getTeacherById(id);
	teachersNames << nameText;

	printInfoQS("Teacher \"" + nameText + "\" has been added");
	if (curShowing == CurrenltyShowing::Teachers) {
		showTeachers();
	}

	return true;
}

bool ConfigWindow::addGroup(QString nameText, QString numOfStudentsText, bool getFromFields) {
	int id = config->getLowestIdGroups();
	string text = to_string(id) + "," + nameText.toStdString() + "," + numOfStudentsText.toStdString();

	config->addGroup(text);
	groups[nameText.toStdString()] = config->getGroupById(id);
	groupsNames << nameText;

	printInfoQS("Group \"" + nameText + "\" has been added");
	if (curShowing == CurrenltyShowing::Groups) {
		showGroups();
	}

	return true;
}

bool ConfigWindow::addCourse() {
	QString nameText = ui->addCourse_name->text(),
		groupsText = ui->addCourse_groups->text();

	int id = config->getLowestIdCourses();
	string textToAdd = to_string(id) + "," + nameText.toStdString() + ",";

	textToAdd += "[";
	QStringList groupsList = groupsText.split(",");
	foreach(QString group, groupsList) {
		Group* g = groups[group.toStdString()];
		int groupId = groups[group.toStdString()]->getId();
		textToAdd += to_string(groupId) + ",";
	}

	textToAdd.pop_back(); // delete ','
	textToAdd += "]";

	config->addCourse(textToAdd);
	courses[nameText.toStdString()] = config->getCourseById(id);
	coursesNames << nameText;
	printInfoQS("Course \"" + nameText + "\" has been added");

	createGroupsClasses();

	return true;
}

bool ConfigWindow::addRoom() {
	QString nameText = ui->addRoom_name->text(),
		sizeText = ui->addRoom_size->text(),
		tagsText = ui->addRoom_tags->text();

	int size = sizeText.toInt();


	QString tags = "";
	QStringList tagsList = tagsText.split(",");

	foreach(QString tag, tagsList) {
		tags += tag + ",";
		if (!roomsTags.contains(tag))
			roomsTags << tag;
	}

	if (!tags.isEmpty())
		tags.chop(1); // Delete last ','

	int id = config->getLowestIdRooms();
	string text = nameText.toStdString() + "," + to_string(size) + ", \"#room_tags: " + tags.toStdString() + "\"";

	config->addRoom(text);
	rooms[nameText.toStdString()] = config->getRoomById(id);

	printInfoQS("Room \"" + nameText + "\" has been added");
	if (curShowing == CurrenltyShowing::Rooms) {
		showRooms();
	}
	return true;
}

bool ConfigWindow::validateAddClass() {
	QString errorMessage = "", subjectText = ui->addClass_subject->text(),
		teachersText = ui->addClass_teachers->text(),
		groupsText = ui->addClass_groups->text(),
		durText = ui->addClass_duration->text(),
		roomTagsText = ui->addClass_roomTags->text(),
		numbOfRoomsText = ui->addClass_nOfRooms->text();
	bool defNumOfRooms = ui->addClass_defNumOfRooms_checkB->isChecked(),
		classEveryWeek = ui->addClass_everyWeek_checkB->isChecked(),
		addTaG = ui->addClass_addTaG_checkB->isChecked();

	int numbOfRooms = numbOfRoomsText.toInt();

	if (subjectText.isEmpty())
		errorMessage += "\"Subject\",";
	if (teachersText.isEmpty())
		errorMessage += "\"Teachers\",";
	if (groupsText.isEmpty())
		errorMessage += "\"Groups\",";
	if (roomTagsText.isEmpty() || numbOfRooms < 0)
		errorMessage += "\"Room tags\",";
	if (!defNumOfRooms && numbOfRoomsText.isEmpty())
		errorMessage += "\"Number of rooms\",";

	if (!errorMessage.isEmpty()) {
		errorMessage.chop(1); // delete ','
		errorMessage += " is incorrect";
		printInfoQS(errorMessage);
		return false;
	}

	QStringList teachersList = teachersText.split(",");
	QStringList groupsList = groupsText.split(",");
	QStringList roomTagsList = roomTagsText.split(",");

	if (!addTaG) {
		QString existErrors = "";
		int errors = 0;
		foreach(QString teacher, teachersList) {
			if (!teachersNames.contains(teacher) && ++errors)
				existErrors += "Teacher: " + teacher + ",";
		}

		foreach(QString group, groupsList) {
			if (!groupsNames.contains(group) && ++errors)
				existErrors += "Group: " + group + ",";
		}

		if (errors) {
			existErrors.chop(1); // Delete last '.'
			if (errors == 1)
				existErrors += " does not exist";
			else
				existErrors += " do not exist";
			printInfoQS(existErrors);
			return false;
		}
	}

	return true;
}

bool ConfigWindow::validateAddSubject(QString nameText, bool getFromField) {
	QString errorMessage = "", subjectText;

	if (getFromField)
		subjectText = ui->addSubject_name->text();

	if (subjectText.isEmpty())
		errorMessage += "\"Subject\",";

	if (!errorMessage.isEmpty()) {
		errorMessage.chop(1); // delete ','
		errorMessage += " is incorrect";
		printInfoQS(errorMessage);
		return false;
	}

	if (subjectsNames.contains(subjectText)) {
		printInfoQS("Subject \"" + subjectText + "\" already exists");
		return false;
	}

	return true;
}

bool ConfigWindow::validateAddTeacher(QString nameText, bool getFromField) {
	QString errorMessage = "";

	if (getFromField)
		nameText = ui->addTeacher_name->text();

	if (nameText.isEmpty())
		errorMessage += "\"Name\",";

	if (!errorMessage.isEmpty()) {
		errorMessage.chop(1); // delete ','
		errorMessage += " is incorrect";
		printInfoQS(errorMessage);
		return false;
	}

	if (teachers.find(nameText.toStdString()) != teachers.end()) { // group already exist
		printInfoQS("Teacher \"" + nameText + "\" already exists");
		return false;
	}

	return true;
}

bool ConfigWindow::validateAddGroup(QString nameText, QString numOfStudentsText, bool getFromFields) {
	QString errorMessage = "";

	if (getFromFields) {
		nameText = ui->addGroup_name->text();
		numOfStudentsText = ui->addGroup_numOfStudents->text();
	}
	int numStudents = numOfStudentsText.toInt();

	if (nameText.isEmpty())
		errorMessage += "\"Name\",";
	if (numOfStudentsText.isEmpty() || numStudents < 1)
		errorMessage += "\"Number of students\",";

	if (!errorMessage.isEmpty()) {
		errorMessage.chop(1); // delete ','
		errorMessage += " is incorrect";
		printInfoQS(errorMessage);
		return false;
	}

	if (groups.find(nameText.toStdString()) != groups.end()) { // group already exist
		printInfoQS("Group \"" + nameText + "\" already exists");
		return false;
	}

	return true;
}

bool ConfigWindow::validateAddCourse() {
	QString errorMessage = "", nameText = ui->addCourse_name->text(),
		groupsText = ui->addCourse_groups->text();

	if (nameText.isEmpty())
		errorMessage += "\"Name\",";

	if (groupsText.isEmpty())
		errorMessage += "\"Groups\",";

	if (!errorMessage.isEmpty()) {
		errorMessage.chop(1); // delete ','
		errorMessage += " is incorrect";
		printInfoQS(errorMessage);
		return false;
	}

	if (courses.find(nameText.toStdString()) != courses.end()) { // group already exist
		printInfoQS("Course \"" + nameText + "\" already exists");
		return false;
	}

	QStringList groupsList = groupsText.split(",");
	foreach(QString group, groupsList) {
		if (groups.find(group.toStdString()) == groups.end()) { // group exist
			printInfoQS("Group \"" + group + "\" does not exist");
			return false;
		}
	}

	return true;
}

bool ConfigWindow::validateAddRoom() {
	QString errorMessage = "", nameText = ui->addRoom_name->text(),
		sizeText = ui->addRoom_size->text(),
		tagsText = ui->addRoom_tags->text();

	int size = sizeText.toInt();

	if (nameText.isEmpty())
		errorMessage += "\"Name\",";
	if (sizeText.isEmpty() || size < 1)
		errorMessage += "\"Size\",";
	if (tagsText.isEmpty())
		errorMessage += "\"Tags\",";

	if (!errorMessage.isEmpty()) {
		errorMessage.chop(1); // delete ','
		errorMessage += " is incorrect";
		printInfoQS(errorMessage);
		return false;
	}

	if (rooms.find(nameText.toStdString()) != rooms.end()) { // group already exist
		printInfoQS("Room \"" + nameText + "\" already exists");
		return false;
	}

	return true;
}

void ConfigWindow::fillFields(CurrenltyShowing curShow, QTreeWidgetItem* item) {
	if (curShow == CurrenltyShowing::Classes && item->columnCount() == 7) {
		ui->addClass_subject->setText(item->text(0));
		ui->addClass_teachers->setText(item->text(1));
		ui->addClass_groups->setText(item->text(2));
		ui->addClass_duration->setValue(item->text(3).toInt());

		if (item->text(4) == "Yes")
			ui->addClass_everyWeek_checkB->setChecked(true);
		else
			ui->addClass_everyWeek_checkB->setChecked(false);

		ui->addClass_roomTags->setText(item->text(5));
	}
	else if (curShow == CurrenltyShowing::Subjects && item->columnCount() == 1) {
		ui->addSubject_name->setText(item->text(0));
	}
	else if (curShow == CurrenltyShowing::Teachers && item->columnCount() == 1) {
		ui->addTeacher_name->setText(item->text(0));
	}
	else if (curShow == CurrenltyShowing::Groups && item->columnCount() == 2) {
		ui->addGroup_name->setText(item->text(0));
		ui->addGroup_numOfStudents->setText(item->text(1));
	}
	else if (curShow == CurrenltyShowing::Courses && item->columnCount() == 2) {
		ui->addCourse_name->setText(item->text(0));
		ui->addCourse_groups->setText(item->text(1));
	}
	else if (curShow == CurrenltyShowing::Rooms && item->columnCount() == 3) {
		ui->addRoom_name->setText(item->text(0));
		ui->addRoom_size->setText(item->text(1));
		ui->addRoom_tags->setText(item->text(2));
	}
}

void ConfigWindow::printInfo(std::string text) {
	ui->plainTextEdit->appendPlainText(QString::fromStdString(text));
}

void ConfigWindow::printInfoQS(QString text) {
	ui->plainTextEdit->appendPlainText(text);
}

void ConfigWindow::clearShowConfigTree() {
	ui->showConfig_treeW->clear();
	itemsId.clear();
	itemsClass.clear();
	if (!editing) {
		ui->edit_btn->setEnabled(false);
		ui->del_btn->setEnabled(false);
	}

	itemClickedShowT = nullptr;
}

void ConfigWindow::clearContent() {
	teachersNames.clear();
	groupsNames.clear();
	roomsTags.clear();

	teachers.clear();
	subjects.clear();
	groups.clear();
	courses.clear();
	rooms.clear();

	ui->classes_treeW->clear();
	clearShowConfigTree();

	for (map <string, list<CourseClass*>>::iterator it = groupClasses.begin(); it != groupClasses.end(); it++)
		(*it).second.clear();

	groupClasses.clear();

	configSaved = true;
	configFileDir = "";
	config = nullptr;
	curShowing = CurrenltyShowing::None;
}

void ConfigWindow::newConfig() {
	if (!closeConfigFile())
		return;

	configSaved = true;
	menuShow->setEnabled(true);
	actionClose->setEnabled(true);
	config = new Configuration;
}

void ConfigWindow::openConfig(QString fileDir) {
	if (!closeConfigFile())
		return;

	config = new Configuration();
	string error = "";
	config->getFromFile(error, fileDir.toStdString());
	menuShow->setEnabled(true);

	for (auto it = config->teachersAll().begin(); it != config->teachersAll().end(); it++) {
		teachers[it->second->getName()] = it->second;
		teachersNames << QString::fromStdString(it->second->getName());
	}

	for (auto it = config->subjectsAll().begin(); it != config->subjectsAll().end(); it++)
		subjects[it->second->getName()] = it->second;

	for (auto it = config->groupsAll().begin(); it != config->groupsAll().end(); it++) {
		groups[it->second->getName()] = it->second;
		groupsNames << QString::fromStdString(it->second->getName());
	}

	for (auto it = config->coursesAll().begin(); it != config->coursesAll().end(); it++)
		courses[it->second->getName()] = it->second;

	for (auto it = config->allRooms().begin(); it != config->allRooms().end(); it++) {
		rooms[it->second->getName()] = it->second;

		for (auto it_tag = it->second->getTags().begin(); it_tag != it->second->getTags().end(); it_tag++)
			if (!roomsTags.contains(QString::fromStdString(it_tag->first)))
				roomsTags << QString::fromStdString(it_tag->first);
	}

	for (auto it_class = config->getCoursesClasses().begin(); it_class != config->getCoursesClasses().end(); it_class++) {
		for (auto it_group = (*it_class)->getGroups().begin(); it_group != (*it_class)->getGroups().end(); it_group++) {
			groupClasses[(*it_group)->getName()].push_back(*it_class);
		}
	}

	actionClose->setEnabled(true);
	configSaved = true;
	configFileDir = fileDir.toStdString();
	createGroupsClasses();
}

void ConfigWindow::openFileConfig() {
	QString fileName = QFileDialog::QFileDialog::getOpenFileName(this,QString(),QString(), QString("*.txt"));
	if (!fileName.isEmpty()) {
		openConfig(fileName);
	}
}

void ConfigWindow::saveConfig() {
	if (configFileDir == "") {
		saveAsConfig();
		return;
	}

	config->saveConfig(configFileDir);
	configSaved = true;
	actionSave->setEnabled(false);
	printInfoQS("File saved");
}

void ConfigWindow::saveAsConfig() {
	QString fileName = QFileDialog::QFileDialog::getSaveFileName(this, QString(), QString(), QString(".txt"));
	if (fileName.isEmpty())
		return;
	config->saveConfig(fileName.toStdString());
	configSaved = true;
	actionSave->setEnabled(false);
	printInfoQS("File saved as " + fileName);
}

bool ConfigWindow::closeConfigFile() {
	if (config) {
		if (!configSaved) {
			QMessageBox::StandardButton button;
			QMessageBox msgBox;
			msgBox.setText("Do you want to save configuration file?");
			msgBox.addButton("Yes", QMessageBox::YesRole);
			msgBox.addButton("No", QMessageBox::NoRole);
			msgBox.addButton("Cancel", QMessageBox::RejectRole);

			int msgResult = msgBox.exec();

			if (msgResult == 0) { // Yes
				saveConfig();
			}
			else if (msgResult == 1) { // No
				;// nothing, just continue
			}
			else if (msgResult == 2) { // Cancel
				return false;
			}
		}
	}

	delete config;
	config = nullptr;
	clearContent();
	menuShow->setEnabled(true);
	actionClose->setEnabled(false);

	return true;
}

void ConfigWindow::showTeachers() {
	clearShowConfigTree();
	ui->showConfig_treeW->setColumnCount(1);
	ui->showConfig_treeW->headerItem()->setText(0, "Name");

	for (auto it_teacher = teachers.begin(); it_teacher != teachers.end(); it_teacher++) {
		QTreeWidgetItem* item = new QTreeWidgetItem(ui->showConfig_treeW);
		item->setText(0, QString::fromStdString(it_teacher->first));
		itemsId[item] = it_teacher->second->getId();
	}

	setTreeWidgetColWidth();
	curShowing = CurrenltyShowing::Teachers;
}

void ConfigWindow::showSubjects() {
	clearShowConfigTree();
	ui->showConfig_treeW->setColumnCount(1);
	ui->showConfig_treeW->headerItem()->setText(0, "Name");

	for (auto it_sub = subjects.begin(); it_sub != subjects.end(); it_sub++) {
		QTreeWidgetItem* item = new QTreeWidgetItem(ui->showConfig_treeW);
		item->setText(0, QString::fromStdString(it_sub->first));
		itemsId[item] = it_sub->second->getId();
	}

	setTreeWidgetColWidth();
	curShowing = CurrenltyShowing::Subjects;
}

void ConfigWindow::showGroups() {
	clearShowConfigTree();
	ui->showConfig_treeW->setColumnCount(2);
	ui->showConfig_treeW->headerItem()->setText(0, "Name");
	ui->showConfig_treeW->headerItem()->setText(1, "Size");

	for (auto it_group = groups.begin(); it_group != groups.end(); it_group++) {
		QTreeWidgetItem* item = new QTreeWidgetItem(ui->showConfig_treeW);
		item->setText(0, QString::fromStdString(it_group->first));
		item->setText(1, QString::fromStdString(to_string(it_group->second->numberOfStudents())));
		itemsId[item] = it_group->second->getId();
	}

	setTreeWidgetColWidth();
	curShowing = CurrenltyShowing::Groups;
}

void ConfigWindow::showCourses() {
	clearShowConfigTree();
	ui->showConfig_treeW->setColumnCount(2);
	ui->showConfig_treeW->headerItem()->setText(0, "Name");
	ui->showConfig_treeW->headerItem()->setText(1, "Groups");

	int groupsSize, i;
	list<Group*>::iterator it_groups;
	string groupsText;

	for (auto it_course = courses.begin(); it_course != courses.end(); it_course++) {
		QTreeWidgetItem* item = new QTreeWidgetItem(ui->showConfig_treeW);
		item->setText(0, QString::fromStdString(it_course->first));

		groupsSize = it_course->second->groupsAll().size();
		it_groups = it_course->second->groupsAll().begin();
		groupsText = "";

		for (i = 0; i < groupsSize; it_groups++) {
			groupsText += (*it_groups)->getName();

			if (++i < groupsSize)
				groupsText += ",";
		}

		item->setText(1, QString::fromStdString(groupsText));
		itemsId[item] = it_course->second->getId();
	}

	setTreeWidgetColWidth();
	curShowing = CurrenltyShowing::Courses;
}

void ConfigWindow::showRooms() {
	clearShowConfigTree();
	ui->showConfig_treeW->setColumnCount(3);
	ui->showConfig_treeW->headerItem()->setText(0, "Name");
	ui->showConfig_treeW->headerItem()->setText(1, "Size");
	ui->showConfig_treeW->headerItem()->setText(2, "Tags");

	int roomTagsSize, i;
	map<string, int>::iterator it_tags;
	string roomTagsText, sizeText;

	for (auto it_room = rooms.begin(); it_room != rooms.end(); it_room++) {
		QTreeWidgetItem* item = new QTreeWidgetItem(ui->showConfig_treeW);
		item->setText(0, QString::fromStdString(it_room->first));
		item->setText(1, QString::fromStdString(to_string(it_room->second->getSize())));

		roomTagsSize = it_room->second->getTags().size();
		it_tags = it_room->second->getTags().begin();
		roomTagsText = "";

		for (i = 0; i < roomTagsSize; it_tags++) {
			roomTagsText += it_tags->first;

			if (++i < roomTagsSize)
				roomTagsText += ",";
		}

		item->setText(2, QString::fromStdString(roomTagsText));
		itemsId[item] = it_room->second->getId();
	}

	setTreeWidgetColWidth();
	curShowing = CurrenltyShowing::Rooms;
}

void ConfigWindow::showGroupClassesSlot(QTreeWidgetItem * item, int column) {
	if (item->child(0))
		return;

	showGroupClasses(item->text(0).toStdString());
}

void ConfigWindow::showGroupClasses(string groupName) {
	clearShowConfigTree();
	ui->showConfig_treeW->setColumnCount(6);
	ui->showConfig_treeW->headerItem()->setText(0, "Subject");
	ui->showConfig_treeW->headerItem()->setText(1, "Teachers");
	ui->showConfig_treeW->headerItem()->setText(2, "Groups");
	ui->showConfig_treeW->headerItem()->setText(3, "Duration [min]");
	ui->showConfig_treeW->headerItem()->setText(4, "Every week");
	ui->showConfig_treeW->headerItem()->setText(5, "Room tags");
	ui->showConfig_treeW->headerItem()->setText(6, "Number of Rooms");

	int roomTagsSize, groupsSize, i;
	list<Group*>::iterator it_groups;
	map<string, int>::iterator it_tags;
	string roomTagsText, groupsText, sizeText;

	for (auto it_class = groupClasses[groupName].begin(); it_class != groupClasses[groupName].end(); it_class++) {
		QTreeWidgetItem* item = new QTreeWidgetItem(ui->showConfig_treeW);
		item->setText(0, QString::fromStdString((*it_class)->getSubject()->getName()));
		//		item->setText(1, QString::fromStdString((*it_class)->getTeacher()->getName()));
		string teachersStr = "";
		for (auto it_teacher = (*it_class)->getTeachers().begin(); it_teacher != (*it_class)->getTeachers().end(); it_teacher++) {
			teachersStr += (*it_teacher)->getName() + ",";
		}

		teachersStr.pop_back();
		item->setText(1, QString::fromStdString(teachersStr));

		// Groups
		groupsSize = (*it_class)->getGroups().size();
		it_groups = (*it_class)->getGroups().begin();
		groupsText = "";

		for (i = 0; i < groupsSize; it_groups++) {
			groupsText += (*it_groups)->getName();

			if (++i < groupsSize)
				groupsText += ",";
		}

		item->setText(2, QString::fromStdString(groupsText));

		// Room tags
		roomTagsSize = (*it_class)->getRoomTags().size();
		it_tags = (*it_class)->getRoomTags().begin();
		roomTagsText = "";

		for (i = 0; i < roomTagsSize; it_tags++) {
			roomTagsText += it_tags->first;

			if (++i < roomTagsSize)
				roomTagsText += ",";
		}


		item->setText(3, QString::fromStdString(to_string((*it_class)->classDuration() * 15)));

		if ((*it_class)->getClassEveryWeek())
			item->setText(4, "Yes");
		else
			item->setText(4, "No");

		item->setText(5, QString::fromStdString(roomTagsText));
		item->setText(6, QString::fromStdString(to_string(1)));
		itemsClass[item] = *it_class;
	}

	setTreeWidgetColWidth();
	ui->showConfig_treeW->sortByColumn(0);
	curGroupClasses = groupName;
	curShowing = CurrenltyShowing::Classes;
}

void ConfigWindow::getItemClickedShowT(QTreeWidgetItem * item, int column) {
	itemClickedShowT = item;
	ui->edit_btn->setEnabled(true);
	ui->del_btn->setEnabled(true);
}

void ConfigWindow::on_add_btn_clicked() { // Add / save changes
	if (!config) {
		printInfo("Config is not opened");
		return;
	}

	int index = ui->editor_stackedW->currentIndex();
	bool added = false;
	if (index == CLASS) {
		if (validateAddClass())
			addClass();
	}
	else if (index == SUBJECT) {
		if (validateAddSubject())
			added = addSubject();
	}
	else if (index == TEACHER) {
		if (validateAddTeacher())
			added = addTeacher();
	}
	else if (index == GROUP) {
		if (validateAddGroup())
			added = addGroup();
	}
	else if (index == COURSE) {
		if (validateAddCourse())
			added = addCourse();
	}
	else if (index == ROOM) {
		if (validateAddRoom())
			added = addRoom();
	}

	if (added) {
		configSaved = false;
		actionSave->setEnabled(true);
	}
}

void ConfigWindow::on_addClass_defNumOfRooms_checkB_clicked() {
	if (ui->addClass_defNumOfRooms_checkB->isChecked()) {
		ui->addClass_nOfRooms->setEnabled(false);
		ui->addClass_nOfRooms->clear();
	}
	else
		ui->addClass_nOfRooms->setEnabled(true);
}

void ConfigWindow::on_comboBox_currentIndexChanged(int index) {
	ui->editor_stackedW->setCurrentIndex(index);
}

void ConfigWindow::on_clear_btn_clicked() {
	int index = ui->editor_stackedW->currentIndex();
	if (index == CLASS) {
		ui->addClass_subject->clear();
		ui->addClass_teachers->clear();
		ui->addClass_groups->clear();
		ui->addClass_roomTags->clear();
		ui->addClass_nOfRooms->clear();
	}
	else if (index == SUBJECT) {
		ui->addSubject_name->clear();
	}
	else if (index == TEACHER) {
		ui->addTeacher_name->clear();
	}
	else if (index == GROUP) {
		ui->addGroup_name->clear();
		ui->addGroup_numOfStudents->clear();
	}
	else if (index == COURSE) {
		ui->addCourse_name->clear();
		ui->addCourse_groups->clear();
	}
	else if (index == ROOM) {
		ui->addRoom_name->clear();
		ui->addRoom_size->clear();
		ui->addRoom_tags->clear();
	}
}

void ConfigWindow::on_edit_btn_clicked() {
	if (!editing) {
		editing = true;
		ui->comboBox->setEnabled(false);
		ui->add_btn->setText("Save changes");
		ui->edit_btn->setText("Cancel editing");
		ui->comboBox->setCurrentIndex(curShowing);
//		ui->editor_stackedW->setCurrentIndex(curShowing);
		editingItemShowT = itemClickedShowT;
		fillFields(curShowing, editingItemShowT);
	}
	else {
		editing = false;
		ui->comboBox->setEnabled(true);
		ui->add_btn->setText("Add");
		ui->edit_btn->setText("Edit");
	}
}

void ConfigWindow::on_del_btn_clicked() {
	if (curShowing == CurrenltyShowing::Classes) {
		CourseClass* classC = itemsClass[itemClickedShowT];

		for (list<Teacher*>::iterator it_teacher = classC->getTeachers().begin(); it_teacher != classC->getTeachers().end(); it_teacher++)
			teacherClasses[(*it_teacher)->getName()].remove(classC);

		for (list<Group*>::iterator it_group = classC->getGroups().begin(); it_group != classC->getGroups().end(); it_group++)
			groupClasses[(*it_group)->getName()].remove(classC);

		config->removeClass(classC);
		delete itemClickedShowT;
	}
	else if (curShowing == CurrenltyShowing::Subjects) {
		int id = subjects[itemClickedShowT->text(0).toStdString()]->getId();
		QString messageQ = "Can not delete subject \"" + itemClickedShowT->text(0) + "\".";
		bool safeDel = config->vatidateSafeDelSubject(id);
		if (!safeDel) {
			QMessageBox::StandardButton button;
			QMessageBox::question(this, "Configuration", messageQ, QMessageBox::Ok);
			return;
		}
		subjectsNames.removeOne(itemClickedShowT->text(0));
		subjects.erase(itemClickedShowT->text(0).toStdString());
		config->removeSubject(id, safeDel);
		delete itemClickedShowT;
	}
	else if (curShowing == CurrenltyShowing::Teachers) {
		int id = teachers[itemClickedShowT->text(0).toStdString()]->getId();
		QString messageQ = "All classes with teacher \"" + itemClickedShowT->text(0) + "\" will be deleted.";
		bool safeDel = config->vatidateSafeDelProf(id);
		if (!safeDel) {
			QMessageBox::StandardButton button;
			button = QMessageBox::question(this, "Configuration", messageQ, QMessageBox::Ok | QMessageBox::Cancel);
			if (button == QMessageBox::Cancel)
				return;

			teacherClasses.erase(itemClickedShowT->text(0).toStdString());
			groupClasses.erase(itemClickedShowT->text(0).toStdString());
		}
		teachersNames.removeOne(itemClickedShowT->text(0));
		teachers.erase(itemClickedShowT->text(0).toStdString());
		config->removeProf(id, safeDel);
		delete itemClickedShowT;
	}
	else if (curShowing == CurrenltyShowing::Groups) {
		int id = groups[itemClickedShowT->text(0).toStdString()]->getId();
		QString messageQ = "All classes with group \"" + itemClickedShowT->text(0) + "\" will be deleted.";
		bool safeDel = config->vatidateSafeDelGroup(id);
		if (!safeDel) {
			QMessageBox::StandardButton button;
			button = QMessageBox::question(this, "Configuration", messageQ, QMessageBox::Ok | QMessageBox::Cancel);
			if (button == QMessageBox::Cancel)
				return;

			teacherClasses.erase(itemClickedShowT->text(0).toStdString());
			groupClasses.erase(itemClickedShowT->text(0).toStdString());
		}
		groupsNames.removeOne(itemClickedShowT->text(0));
		groups.erase(itemClickedShowT->text(0).toStdString());
		config->removeGroup(id, safeDel);
		delete itemClickedShowT;
	}
	else if (curShowing == CurrenltyShowing::Courses) {
		coursesNames.removeOne(itemClickedShowT->text(0));
		courses.erase(itemClickedShowT->text(0).toStdString());
		delete itemClickedShowT;
		createGroupsClasses();
	}
	else if (curShowing == CurrenltyShowing::Rooms) {
		Room* room = rooms[itemClickedShowT->text(0).toStdString()];
		for (auto it_tag = room->getTags().begin(); it_tag != room->getTags().end(); it_tag++)
			roomsTags.removeOne(QString::fromStdString(it_tag->first));

		rooms.erase(itemClickedShowT->text(0).toStdString());
		delete itemClickedShowT;
	}

	ui->del_btn->setEnabled(false);
	if (!editing)
		ui->edit_btn->setEnabled(false);
}