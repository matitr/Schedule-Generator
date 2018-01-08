#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTreeWidgetItem>
#include <QThread>
#include <unordered_map>
#include <map>
#include "List.h"
#include "Population.h"

class SeparateSchedule;
class Population;
struct Lesson;
class GeneratorThread;
class ConfigWindow;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    SeparateSchedule* schedule;
    map<string, list<Lesson*>>* groups;
    map<string, list<Lesson*>>* teachers;
    map<string, list<Lesson*>>* rooms;
	unordered_map<string, QColor> roomsColors;
	unordered_map<string, string> roomsTags; // <roomName, tags>

	GeneratorThread *generator;
	ConfigWindow* configWindow;
    bool pairWeeks;
    int columnWidth;
    int rowHeight;
    int startColumn;
    int startRow;

	bool checkMaxGeneration;
	int maxGeneration;
	bool checkMaxTime;
	double maxTime;

    void createMenus();
	void setDefaultGenSettings();
	void createRoomsColors();
    void hideWindow(QWidget*);
	void hideGeneratorWindow();
	void configEdit();

    void openSchedule();
	void openScheduleFileDir();
    void createRightMenuButtons();
    void createEmptyTimeTable();
    void createTableNotations();
    void clearScheduleTable();

    void showScheduleGroup();
    void showScheduleTeacher();
    void showScheduleRoom();
    void showSchedule(map<string, list<Lesson*>>*, string);


	void generatorEnded();
public:
    void printTest();
    void printInfo(std::string text);

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
	void stopGenerator();

public slots:
	void printGeneration(string text);
	void printFitness(string text);
	void printErrors(string text);
	void configExited();

private slots:
	void enableApplyGenButton();
    void on_generate_btn_clicked();
    void on_stopGenerate_btn_clicked();
    void on_showGenSettings_btn_clicked();
    void on_applyGenSettings_btn_clicked();
};


// connection between threads
class ThreadsConnection : public QObject {
	Q_OBJECT

	bool stopGenerator;

	bool checkMaxGeneration;
	int maxGeneration;
	bool checkMaxTime;
	double maxTime;
public:
	void setStopGenerator() { stopGenerator = true; }

	bool getStopGenerator(int generation, double time) { 
		if (stopGenerator)
			return true;

		if ((checkMaxGeneration && generation >= maxGeneration) || (checkMaxTime && time >= maxTime))
			return true;

		return false;
	}

	void setSettings(bool _checkMaxGeneration, int _maxGeneration, bool _checkMaxTime, double _maxTime) {
		checkMaxGeneration = _checkMaxGeneration;
		maxGeneration = _maxGeneration;
		checkMaxTime = _checkMaxTime;
		maxTime = _maxTime;
	}

	ThreadsConnection(bool _checkMaxGeneration, int _maxGeneration, bool _checkMaxTime, double _maxTime) {
		stopGenerator = false;
		checkMaxGeneration = _checkMaxGeneration;
		maxGeneration = _maxGeneration;
		checkMaxTime = _checkMaxTime;
		maxTime = _maxTime;
	}
	~ThreadsConnection() {  }

signals :
	void printGeneration(string text);
	void printFitness(string text);
	void printErrors(string text);
	void printInfo(string text);
	void generatorEnded();
};


// GeneratorThread
class GeneratorThread : public QThread {
	Q_OBJECT


	void run() {
		p->run();
		window->generatorEnded();
	}
public:
	Population* p;
	ThreadsConnection* window;
	GeneratorThread(Population* _p) {
		p = _p;
		window = p->window;
	}

	~GeneratorThread() {
		if (p)
			delete p;
	}
};

#endif // MAINWINDOW_H
