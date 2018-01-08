#ifndef CONFIG_WINDOW_H
#define CONFIG_WINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <map>
#include <unordered_map>
#include <list>

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QListWidget>
#include "Teacher.h"

class Teacher;
class Subject;
class Group;
class Course;
class Room;
class CourseClass;
class CoursesTree;
class LineEdit;

enum CurrenltyShowing {Classes, Subjects, Teachers, Groups, Courses, Rooms, None};

namespace Ui {
	class ConfigWindow;
}

class Configuration;

class ConfigWindow : public QMainWindow {
	Q_OBJECT

private:
	Ui::ConfigWindow *ui;
	Configuration* config;
	QMenu *menuShow;
	QAction *actionSave;
	QAction *actionClose;
	QStringList teachersNames;
	QStringList groupsNames;
	QStringList coursesNames;
	QStringList subjectsNames;
	QStringList roomsTags;

	map<string, Teacher*> teachers;
	map<string, Subject*> subjects;
	map<string, Group*> groups;
	map<string, Course*> courses;
	map<string, Room*> rooms;

	map <string, list<CourseClass*>> groupClasses;
	map <string, list<CourseClass*>> teacherClasses;

	unordered_map <QTreeWidgetItem*, int> itemsId;
	unordered_map <QTreeWidgetItem*, CourseClass*> itemsClass;
	CurrenltyShowing curShowing;
	string curGroupClasses;
	bool configSaved;
	string configFileDir;

	bool editing;
	QTreeWidgetItem* itemClickedShowT;
	QTreeWidgetItem* editingItemShowT;

	void createMenus();
	void createLeftMenuTree();
	void createGroupsClasses(); // Left side menu
	void createTeachersClasses(); // Left side menu
	void addGroupsClassesToTree(CoursesTree* coursesTree, QTreeWidget *parent);
	void addGroupsClassesToTree(CoursesTree* coursesTree, QTreeWidgetItem *parent);
	void setEditorValidators();
	void setTreeWidgetColWidth();

	void createAllCompleters();
	void createCompleter(LineEdit*, QStringList*);

	bool addClass();
	bool addSubject(QString nameText = "", bool getFromField = true);
	bool addTeacher(QString nameText = "", bool getFromField = true);
	bool addGroup(QString nameText = "", QString numOfStudentsText = "",  bool getFromField = true);
	bool addCourse();
	bool addRoom();

	bool validateAddClass();
	bool validateAddSubject(QString nameText = "", bool getFromField = true);
	bool validateAddTeacher(QString nameText = "", bool getFromField = true);
	bool validateAddGroup(QString nameText = "", QString numOfStudentsText = "", bool getFromField = true);
	bool validateAddCourse();
	bool validateAddRoom();

	void fillFields(CurrenltyShowing, QTreeWidgetItem*);

	void printInfo(std::string);
	void printInfoQS(QString);
	void clearShowConfigTree();
	void clearContent();

private slots:
	void newConfig();
	void openConfig(QString fileDir = "config.txt");
	void openFileConfig();
	void saveConfig();
	void saveAsConfig();
	bool closeConfigFile();

	void showTeachers();
	void showSubjects();
	void showGroups();
	void showCourses();
	void showRooms();
	void showGroupClassesSlot(QTreeWidgetItem * item, int column);
	void showGroupClasses(string group);

	void getItemClickedShowT(QTreeWidgetItem * item, int column);

	void on_add_btn_clicked(); // Add / save changes
    void on_addClass_defNumOfRooms_checkB_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_clear_btn_clicked();

	void on_edit_btn_clicked();
	void on_del_btn_clicked();
public:
	explicit ConfigWindow(QWidget *parent = 0);
	~ConfigWindow();
};


struct CoursesTree {
	list <string> groups;
	map<string, CoursesTree*> course;

	CoursesTree() {}
	~CoursesTree() {
		for (auto it = course.begin(); it != course.end(); it++)
			delete (it->second);
	}
};

#endif
