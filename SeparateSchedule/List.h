#pragma once
#include <string>
#include <list>
#include <map>

using namespace std;

struct Lesson { // in memory +5
	string hour;
	string day;
	list<string> group;
	string subject;
    string room;
	list<string> teachers;
	string week;
	Lesson * infoNext;
	Lesson * infoPrev;
	Lesson * otherListPtr;
	Lesson();
	~Lesson();
};

class List {

	struct node { // in memory +2
		string dataMain;
		Lesson* infoHead;
		Lesson* infoTail;
		node* next;
		node* prev;
		int infoSize;
		node();
		~node();
	};
	//typedef node* node_ptr;
	node* head;
	node* tail;
	int sizeL;
	string label;
	bool lessonRemovability;

	void addMainBeg(string);
	short addInformations(string n, node*&, Lesson*&);
	bool findPosition(node*, Lesson*, Lesson*&);
	bool findTimePointer(node*, Lesson*, Lesson*&);
	bool timeCompare(string, string); // true when can place after this
	short dayValue(string);
	Lesson* createLesson(string h, string d, string g, string n, string s, string room, string week);
	Lesson* createLesson(string h, string d, list<string> groups, string n, string s, string room, string week);
	Lesson* createLesson(string hour, string day, string groups, list<string> teacher, string subject, string room, string week);
	Lesson* createLesson(string hour, string day, list<string> groups, list<string> teachers, string subject, string room, string week);
	void delLessonNode(node*, Lesson*);
	void delDataMainNode(node*);
	bool compareLists(list<string>*, list<string>*);
	//  \/    output    \/
	void printText(string);
	//void saveLineFile(ofstream&, string);
public:
	void delEmptyData();
	bool addSmart(string h, string d, list<string>, list<string> teachers, string s, string room, string week, List*);
	bool addSmartRoom(string h, string d, list<string>, list<string> n, string s, string room, string week);
	void addLessonBeg(node*, Lesson*);
	void addLessonEnd(node*, Lesson*);
	void insertBeforePointer(string, Lesson*, Lesson*);
	node* findData(string);
	int size();
	int infoSize(string);
	bool deleteLesson(string, int, List*);
	void deleteLessonTeachers(string hour, string day, list<string>*group, list<string>* teacher, string subject, string room, string week, List* groups);
	void deleteLessonGroups(string hour, string day, list<string>*group, list<string>* teacher, string subject, string room);
	bool deleteDataMain(string, List*);
	void deleteAll(List*);
    map<string, list<Lesson*>>* createStandardList();
	void setLessonRemovability(bool x) { lessonRemovability = x; }
	//  \/    output    \/
	void printForward();
	void printBackward();
	void printInformations(string, bool = false);
	void printAll();
	void saveMainFile();
	void saveAllToFiles();
	List();
	List(string);
	~List();
};
