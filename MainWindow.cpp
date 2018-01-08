#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "SeparateSchedule.h"
#include "Configuration.h"
#include "ConfigWindow.h"

#include <QPushButton>
#include <QMessageBox>
#include <QToolButton>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QObject>
#include <QFileDialog>
#include <string>
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){

	srand(time(NULL));
    ui->setupUi(this);
    schedule = nullptr;
    groups = nullptr;
    teachers = nullptr;
    rooms = nullptr;
	generator = nullptr;
    pairWeeks = true;
    columnWidth = 73;
    rowHeight = 9;
    startColumn = 1;
    startRow = 2 + 2 * pairWeeks;

	QSize windowSize = size();
	setMaximumHeight(windowSize.height());
	setMaximumWidth(windowSize.width());
	setMinimumHeight(windowSize.height());
	setMinimumWidth(windowSize.width());

	this->setWindowTitle("Schedule");
	qRegisterMetaType<string>("string");
    createMenus();
    createEmptyTimeTable();
	setDefaultGenSettings();
	createRoomsColors();

    if(!ui->info->layout())
        ui->info->setLayout(new QVBoxLayout);

    ui->info->layout()->addWidget(ui->info_field);
    ui->info->layout()->setContentsMargins(QMargins());
	
	ui->applyGenSettings_btn->setEnabled(false);
	QObject::connect(ui->maxGen_checkB, &QCheckBox::clicked, this, &MainWindow::enableApplyGenButton);
	QObject::connect(ui->maxGen_lineE, &QLineEdit::textEdited, this, &MainWindow::enableApplyGenButton);
	QObject::connect(ui->maxTime_checkB, &QCheckBox::clicked, this, &MainWindow::enableApplyGenButton);
	QObject::connect(ui->maxTime_lineE, &QLineEdit::textEdited, this, &MainWindow::enableApplyGenButton);
}

MainWindow::~MainWindow(){
	if (generator && !generator->isFinished()) {
		stopGenerator();
		while (!generator->isFinished())
			QThread::msleep(100);
	}

    delete ui;
	delete generator;
	delete schedule;
}

void MainWindow::printTest(){
    ui->info_field->appendPlainText(QString::fromStdString("test\n"));
}

void MainWindow::printInfo(string text){
    ui->info_field->appendPlainText(QString::fromStdString(text));
}

void MainWindow::printGeneration(std::string text) {
	ui->generation_field->setText(QString::fromStdString(text));
}

void MainWindow::printFitness(std::string text) {
	ui->fitness_field->setText(QString::fromStdString(text));
}

void MainWindow::printErrors(std::string text) {
	ui->errors_field->setText(QString::fromStdString(text));
}

void MainWindow::createMenus(){
    QMenu *menuWindow;
    QAction *action;

    menuWindow = menuBar()->addMenu("Schedule");
    action = new QAction("Open schedule", this);
    connect (action, &QAction::triggered, this, [this]{ openSchedule(); });
    menuWindow->addAction(action);

	action = new QAction("Open schedule...", this);
	connect(action, &QAction::triggered, this, [this] { openScheduleFileDir(); });
	menuWindow->addAction(action);

	action = new QAction("Use ", this);
	action->setCheckable(true);
	action->setChecked(false);
//	connect(action, &QAction::triggered, this, [this] { openSchedule(); });
	menuWindow->addAction(action);

    // Window
    menuWindow = menuBar()->addMenu("Window");
    action = new QAction("Generator", this);
    action->setCheckable(true);
    action->setChecked(true);
    connect (action, &QAction::triggered, this, [this]{ hideGeneratorWindow(); });
    menuWindow->addAction(action);

    action = new QAction("Right bar", this);
    action->setCheckable(true);
    action->setChecked(true);
    connect (action, &QAction::triggered, this, [this]{ hideWindow(ui->rightMenu); });
    menuWindow->addAction(action);

    action = new QAction("Bottom bar", this);
    action->setCheckable(true);
    action->setChecked(true);
    connect (action, &QAction::triggered, this, [this]{ hideWindow(ui->bottomMenu); });
    menuWindow->addAction(action);

	// Window
	menuWindow = menuBar()->addMenu("Config");
	action = new QAction("Edit", this);
	connect(action, &QAction::triggered, this, [this] { configEdit(); });
	menuWindow->addAction(action);


}

void MainWindow::setDefaultGenSettings() {
	checkMaxGeneration = false;
	maxGeneration = 0;
	checkMaxTime = true;
	maxTime = 120;

	QFont font = ui->showGenSettings_btn->font();
	font.setPointSize(12);
	ui->showGenSettings_btn->setFont(font);
	ui->showGenSettings_btn->setText(QChar(9668));

	ui->maxGen_lineE->setValidator(new QIntValidator(0, 9999999, this));
	QDoubleValidator *doubleVal = new QDoubleValidator(0.0, 9999999, 2, this);
	doubleVal->setNotation(QDoubleValidator::StandardNotation);
	ui->maxTime_lineE->setValidator(doubleVal);

	if (checkMaxGeneration)
		ui->maxGen_checkB->setChecked(true);

	if (checkMaxTime)
		ui->maxTime_checkB->setChecked(true);

	ui->maxGen_lineE->setText(QString::fromStdString(to_string(maxGeneration)));

	string textTime = to_string(maxTime);
	if (textTime.find('.') != string::npos) {
		textTime.erase(textTime.begin() + textTime.find('.') + 3, textTime.end());
		textTime.replace(textTime.begin() + textTime.find('.'), textTime.begin() + textTime.find('.') + 1, ",");
	}

	ui->maxTime_lineE->setText(QString::fromStdString(textTime));
}

void MainWindow::createRoomsColors() {
	string errorMessage;
//	Configuration::getConfig().getFromFile(errorMessage);
	Configuration configuration;
	configuration.getFromFile(errorMessage);
	map <int, Room*>::iterator it;
	map <string, int>::iterator it_rooomTags;

	for (it = configuration.allRooms().begin(); it != configuration.allRooms().end(); it++) {
		string roomTags = "";
		
		for (it_rooomTags = it->second->getTags().begin(); it_rooomTags != it->second->getTags().end(); it_rooomTags++) {
			roomTags += it_rooomTags->first;
		}

		roomsTags[it->second->getName()] = roomTags;

		unordered_map<string, QColor>::iterator found = roomsColors.find(it->second->getName());
		if (found == roomsColors.end()) {
			roomsColors[roomTags] = QColor(40 + rand() % 170, 40 + rand() % 170, 40 + rand() % 170); // range <40,210)
		}
	}
}

void MainWindow::hideWindow(QWidget* widget){
    if (widget->isVisible())
        widget->hide();
    else
        widget->show();
}

void MainWindow::hideGeneratorWindow() {
	static bool genSettingsHidden = ui->generator_settings_W->isVisible();

	if (ui->generator->isVisible()) {
		ui->generator->hide();
		genSettingsHidden = ui->generator_settings_W->isHidden();
		ui->generator_settings_W->hide();
	}
	else {
		ui->generator->show();
		if (!genSettingsHidden)
			ui->generator_settings_W->show();
	}
}

void MainWindow::configEdit() {
	if (!configWindow)
		configWindow = new ConfigWindow(this);

	configWindow->show();
	connect(configWindow, SIGNAL(destroyed()), this, SLOT(configExited()));
}

void MainWindow::configExited() {
	configWindow = nullptr;
}

void MainWindow::openSchedule(){
    if (schedule){
        QMessageBox::StandardButton button;
        button = QMessageBox::question(this,"Open schedule" , "Do you want to open new schedule?", QMessageBox::Yes | QMessageBox::No);
        if (button == QMessageBox::No)
            return;

		clearScheduleTable();
        delete schedule;
        schedule = nullptr;
    }

    schedule = new SeparateSchedule(this);
    schedule->run();

    groups = schedule->createMapGroups();
    teachers = schedule->createMapTeachers();
    rooms = schedule->createMapRooms();

    createRightMenuButtons();
}

void MainWindow::openScheduleFileDir() {
	if (schedule) {
		QMessageBox::StandardButton button;
		button = QMessageBox::question(this, "Open schedule", "Do you want to open new schedule?", QMessageBox::Yes | QMessageBox::No);
		if (button == QMessageBox::No)
			return;

		clearScheduleTable();
		delete schedule;
		schedule = nullptr;
	}


	QString fileName = QFileDialog::QFileDialog::getOpenFileName(this, QString(), QString(), QString("*.txt"));
	if (fileName.isEmpty())
		return;

	schedule = new SeparateSchedule(this);
	schedule->getFromFile(fileName.toStdString());

	groups = schedule->createMapGroups();
	teachers = schedule->createMapTeachers();
	rooms = schedule->createMapRooms();

	createRightMenuButtons();
}

void MainWindow::createRightMenuButtons(){
	ui->groups_treeW->clear();
	ui->teachers_treeW->clear();
	ui->rooms_treeW->clear();

    map<string, list<Lesson*>>::iterator it_map;

    for (it_map = groups->begin(); it_map != groups->end(); it_map++){
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->groups_treeW);
        item->setText(0, QString::fromStdString(it_map->first));
    }

    for (it_map = teachers->begin(); it_map != teachers->end(); it_map++){
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->teachers_treeW);
        item->setText(0, QString::fromStdString(it_map->first));
    }

    for (it_map = rooms->begin(); it_map != rooms->end(); it_map++){
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->rooms_treeW);
        item->setText(0, QString::fromStdString(it_map->first));
    }

    connect(ui->groups_treeW, &QTreeWidget::itemClicked, this, [this] { showScheduleGroup(); } );
    connect(ui->teachers_treeW, &QTreeWidget::itemClicked, this, [this] { showScheduleTeacher(); } );
    connect(ui->rooms_treeW, &QTreeWidget::itemClicked, this, [this] { showScheduleRoom(); } );
}

void MainWindow::createEmptyTimeTable(){
    ui->timeTable_tableW->clear();

    ui->timeTable_tableW->setColumnCount(1 + 5 + 5 * pairWeeks);
    ui->timeTable_tableW->setRowCount(4 * 12 + 2 + 2 * pairWeeks);
    for (int i = 0; i < ui->timeTable_tableW->rowCount(); i++){
        ui->timeTable_tableW->setRowHeight(i, rowHeight);
    }

    for (int i = 0; i < ui->timeTable_tableW->columnCount(); i++){
        ui->timeTable_tableW->setColumnWidth(i, columnWidth);
    }

    ui->timeTable_tableW->setStyleSheet("gridline-color: #999994");
    ui->timeTable_tableW->horizontalHeader()->hide();
    ui->timeTable_tableW->verticalHeader()->hide();
    ui->timeTable_tableW->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->timeTable_tableW->setFocusPolicy(Qt::NoFocus);
    ui->timeTable_tableW->setSelectionMode(QAbstractItemView::NoSelection);

    // set central text
    for (int i = 0; i < ui->timeTable_tableW->rowCount(); i++)
        for (int j = 0; j < ui->timeTable_tableW->columnCount(); j++){
            ui->timeTable_tableW->setItem(i, j, new QTableWidgetItem);
            ui->timeTable_tableW->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }

    QFont font;
    font.setBold(false);
    font.setPointSize(8);
    ui->timeTable_tableW->setFont(font);

    createTableNotations();
}

void MainWindow::createTableNotations(){
    // setup left corner
    ui->timeTable_tableW->setSpan(0,0,2,1);
    ui->timeTable_tableW->item(0,0)->setText("Day");

    if (pairWeeks){
        ui->timeTable_tableW->setSpan(2,0,2,1);
        ui->timeTable_tableW->item(2,0)->setText("Week");
    }

    // setup first column (info)
    for (int i = 0; i < 12; i++){ // 12 hours
        ui->timeTable_tableW->setSpan((i + 1) * 4,0,4,1);
        ui->timeTable_tableW->item((i + 1) * 4,0)->setBackgroundColor(QColor(220,220,220,255));
        int startTime = 8;
        string text = "";

        if (startTime + i < 10)
            text += "0";

        text += to_string(startTime + i);
        text += ":00-";

        if (startTime + i + 1 < 10)
            text += "0";

        text += to_string(startTime + i + 1);
        text += ":00";
        ui->timeTable_tableW->item((i + 1) * 4,0)->setText(QString::fromStdString((text)));

    }

    // setup first row (info)
    for (int column = 1; column < ui->timeTable_tableW->columnCount(); column += 2){
        ui->timeTable_tableW->setSpan(0,column,2,2);

        if(pairWeeks){
            ui->timeTable_tableW->setSpan(2,column,2,1);
            ui->timeTable_tableW->item(2,column)->setText("Even");
            ui->timeTable_tableW->setSpan(2,column + 1,2,1);
            ui->timeTable_tableW->item(2,column + 1)->setText("Odd");
        }
    }

    ui->timeTable_tableW->item(0,startColumn)->setText("Monday");

    ui->timeTable_tableW->item(0,1 * (pairWeeks + 1) + startColumn)->setText("Tuesday");
    ui->timeTable_tableW->item(0,2 * (pairWeeks + 1) + startColumn)->setText("Wednesday");
    ui->timeTable_tableW->item(0,3 * (pairWeeks + 1) + startColumn)->setText("Thursday");
    ui->timeTable_tableW->item(0,4 * (pairWeeks + 1) + startColumn)->setText("Friday");
}

void MainWindow::clearScheduleTable(){
    for (int i = startRow; i < ui->timeTable_tableW->rowCount(); i++)
        for (int j = startColumn; j < ui->timeTable_tableW->columnCount(); j++){
			if (ui->timeTable_tableW->columnSpan(i, j) > 1 || ui->timeTable_tableW->rowSpan(i, j) > 1) {
				ui->timeTable_tableW->item(i, j)->setText("");
				ui->timeTable_tableW->item(i, j)->setBackground(QColor(250, 250, 250, 255));
				ui->timeTable_tableW->setSpan(i, j, 1, 1);
			}
        }
}

void MainWindow::showScheduleGroup(){
    QTreeWidgetItem *item = *(ui->groups_treeW->selectedItems().begin());

    if(item->childCount() != 0)
        return;

    string text = item->text(0).toUtf8().constData();
    printInfo(text);
    showSchedule(groups, text);
}

void MainWindow::showScheduleTeacher(){
    QTreeWidgetItem *item = *(ui->teachers_treeW->selectedItems().begin());

    if(item->childCount() != 0)
        return;

    string text = item->text(0).toUtf8().constData();
    printInfo(text);
    showSchedule(teachers, text);
}

void MainWindow::showScheduleRoom(){
    QTreeWidgetItem *item = *(ui->rooms_treeW->selectedItems().begin());

    if(item->childCount() != 0)
        return;

    string text = item->text(0).toUtf8().constData();
    printInfo(text);
    showSchedule(rooms, text);
}

void MainWindow::showSchedule(map<string, list<Lesson*>>* data, string name){
    clearScheduleTable();

    list<Lesson*>::iterator it;
    Lesson* lesson;
	int column = 0, startTime = 0, endTime, columnSize = 0;
    int startHour, startMin, endHour, endMin;

    for (it = (*data)[name].begin(); it != (*data)[name].end(); it++){
        lesson = (*it);

        // string lesson->hour is checked before, so it is correct
        startHour = stoi(string (lesson->hour, 0, 2)) - 8;
        startMin = stoi(string (lesson->hour, 3, 2));
        endHour = stoi(string (lesson->hour, 6, 2)) - 8;
        endMin = stoi(string (lesson->hour.begin() + 9, lesson->hour.end()));
		columnSize = (pairWeeks + 1);

        // 4 slots in 1 hour
        startTime = startHour * 4 + startMin / 15 + startRow;
        endTime = endHour * 4 + endMin / 15 + startRow;

        if (lesson->day == "pn")
            column = startColumn;
        else if (lesson->day == "wt")
            column = 1 * (pairWeeks + 1) + startColumn;
        else if (lesson->day == "sr")
            column = 2 * (pairWeeks + 1) + startColumn;
        else if (lesson->day == "cz")
            column = 3 * (pairWeeks + 1) + startColumn;
        else if (lesson->day == "pt")
            column = 4 * (pairWeeks + 1) + startColumn;

		if (lesson->week == "Even") {
			columnSize = 1;
		}
		else if (lesson->week == "Odd") {
			columnSize = 1;
			column += 1;
		}

        ui->timeTable_tableW->setSpan(startTime, column, endTime - startTime, columnSize);

		// use roomsColors
		if (roomsColors.find(roomsTags[lesson->room]) != roomsColors.end())
			ui->timeTable_tableW->item(startTime, column)->setBackgroundColor(roomsColors[roomsTags[lesson->room]]);
		else
			ui->timeTable_tableW->item(startTime, column)->setBackgroundColor(QColor(0, 120, 0, 155));

        string text = lesson->subject;
        if (data == groups)
            text += "\n" + *lesson->teachers.begin() + "\n" + lesson->room;
        else if (data == teachers)
            text += "\n" + *lesson->group.begin() + "\n" + lesson->room;
        else if (data == rooms)
            text += "\n" + *lesson->teachers.begin() + "\n" + *lesson->group.begin();

        ui->timeTable_tableW->item(startTime,column)->setText(QString::fromStdString(text));
    }


}

void MainWindow::generatorEnded() {
	ui->generate_btn->setEnabled(true);
	ui->stopGenerate_btn->setEnabled(false);
	delete generator;
	generator = nullptr;
//	on_generate_btn_clicked(); test loop
}

void MainWindow::enableApplyGenButton() {
	ui->applyGenSettings_btn->setEnabled(true);
}

void MainWindow::on_generate_btn_clicked(){
	if (generator)
		delete generator;

	ThreadsConnection *con = new ThreadsConnection(checkMaxGeneration, maxGeneration, checkMaxTime, maxTime);
	generator = new GeneratorThread(new Population(POPULATION, PERCENTAGE_OF_CROSSOVERS, con));

	QObject::connect(generator->window, &ThreadsConnection::printGeneration, this, &MainWindow::printGeneration);
	QObject::connect(generator->window, &ThreadsConnection::printFitness, this, &MainWindow::printFitness);
	QObject::connect(generator->window, &ThreadsConnection::printErrors, this, &MainWindow::printErrors);
	QObject::connect(generator->window, &ThreadsConnection::printInfo, this, &MainWindow::printInfo);

	QObject::connect(this, &MainWindow::stopGenerator, generator->window, &ThreadsConnection::setStopGenerator);
	QObject::connect(generator->window, &ThreadsConnection::generatorEnded, this, &MainWindow::generatorEnded);

	generator->start();


	ui->generate_btn->setEnabled(false);
	ui->stopGenerate_btn->setEnabled(true);
}

void MainWindow::on_stopGenerate_btn_clicked(){
	if (!generator) {
		return;
	}

	QMessageBox::StandardButton button;
	button = QMessageBox::question(this, "Generator", "Do you want to stop the generator?", QMessageBox::Yes | QMessageBox::No);
	if (button == QMessageBox::No)
		return;

	stopGenerator();
	ui->generate_btn->setEnabled(true);
	ui->stopGenerate_btn->setEnabled(false);
}

void MainWindow::on_showGenSettings_btn_clicked(){
	if (ui->generator_settings_W->isVisible()) {
		ui->generator_settings_W->hide();
		ui->showGenSettings_btn->setText(QChar(9658));
	}
	else {
		ui->generator_settings_W->show();
		ui->showGenSettings_btn->setText(QChar(9668));
	}
}

void MainWindow::on_applyGenSettings_btn_clicked(){
	if (ui->maxGen_checkB->isChecked()) {
		checkMaxGeneration = true;
		maxGeneration = std::stoi(ui->maxGen_lineE->text().toUtf8().constData());
	}
	else
		checkMaxGeneration = false;

	if (ui->maxTime_checkB->isChecked()) {
		checkMaxTime = true;
		string maxTimeStr = ui->maxTime_lineE->text().toUtf8().constData();
		if (maxTimeStr.find('.') != string::npos)
			maxTimeStr.replace(maxTimeStr.begin() + maxTimeStr.find('.'), maxTimeStr.begin() + maxTimeStr.find('.') + 1, ",");

		maxTime = std::stod(maxTimeStr);
	}
	else
		checkMaxTime = false;

	if (generator)
		generator->window->setSettings(checkMaxGeneration, maxGeneration, checkMaxTime, maxTime);

	ui->applyGenSettings_btn->setEnabled(false);
}
