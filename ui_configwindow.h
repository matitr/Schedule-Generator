/********************************************************************************
** Form generated from reading UI file 'configwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGWINDOW_H
#define UI_CONFIGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "LineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_ConfigWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QTreeWidget *showConfig_treeW;
    QWidget *widget_5;
    QLabel *show_label;
    QWidget *widget_2;
    QTreeWidget *classes_treeW;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_14;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QWidget *widget_3;
    QStackedWidget *editor_stackedW;
    QWidget *addClass;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_13;
    QSpinBox *addClass_duration;
    QCheckBox *addClass_everyWeek_checkB;
    LineEdit *addClass_roomTags;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *addClass_defNumOfRooms_checkB;
    QLineEdit *addClass_nOfRooms;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout;
    QLineEdit *addClass_subject;
    LineEdit *addClass_teachers;
    LineEdit *addClass_groups;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_13;
    QCheckBox *addClass_addTaG_checkB;
    QSpacerItem *horizontalSpacer_14;
    QWidget *widget2;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_17;
    QLabel *label_15;
    QLineEdit *addSubject_name;
    QSpacerItem *horizontalSpacer_18;
    QWidget *addTeacher;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *addTeacher_name;
    QSpacerItem *horizontalSpacer_6;
    QWidget *addGroup;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_8;
    QLabel *label_9;
    QVBoxLayout *verticalLayout_6;
    QLineEdit *addGroup_name;
    QLineEdit *addGroup_numOfStudents;
    QSpacerItem *horizontalSpacer_8;
    QWidget *addCourse;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_10;
    QLabel *label_11;
    QVBoxLayout *verticalLayout_8;
    LineEdit *addCourse_name;
    LineEdit *addCourse_groups;
    QSpacerItem *horizontalSpacer_10;
    QWidget *addRoom;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QVBoxLayout *verticalLayout_10;
    QLineEdit *addRoom_name;
    QLineEdit *addRoom_size;
    LineEdit *addRoom_tags;
    QSpacerItem *horizontalSpacer_12;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *add_btn;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *clear_btn;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *edit_btn;
    QSpacerItem *horizontalSpacer_16;
    QPushButton *del_btn;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget_4;
    QPlainTextEdit *plainTextEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ConfigWindow)
    {
        if (ConfigWindow->objectName().isEmpty())
            ConfigWindow->setObjectName(QStringLiteral("ConfigWindow"));
        ConfigWindow->resize(1124, 701);
        centralwidget = new QWidget(ConfigWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(230, 0, 881, 511));
        showConfig_treeW = new QTreeWidget(widget);
        showConfig_treeW->headerItem()->setText(0, QString());
        showConfig_treeW->setObjectName(QStringLiteral("showConfig_treeW"));
        showConfig_treeW->setGeometry(QRect(10, 40, 861, 461));
        widget_5 = new QWidget(widget);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setGeometry(QRect(10, 10, 861, 21));
        show_label = new QLabel(widget_5);
        show_label->setObjectName(QStringLiteral("show_label"));
        show_label->setGeometry(QRect(10, 0, 841, 20));
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(10, 0, 201, 511));
        classes_treeW = new QTreeWidget(widget_2);
        classes_treeW->setObjectName(QStringLiteral("classes_treeW"));
        classes_treeW->setGeometry(QRect(10, 40, 181, 461));
        widget1 = new QWidget(widget_2);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(20, 10, 161, 22));
        horizontalLayout_14 = new QHBoxLayout(widget1);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(widget1);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setChecked(true);

        horizontalLayout_14->addWidget(radioButton);

        radioButton_2 = new QRadioButton(widget1);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        horizontalLayout_14->addWidget(radioButton_2);

        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(20, 510, 551, 151));
        editor_stackedW = new QStackedWidget(widget_3);
        editor_stackedW->setObjectName(QStringLiteral("editor_stackedW"));
        editor_stackedW->setGeometry(QRect(10, 40, 531, 111));
        addClass = new QWidget();
        addClass->setObjectName(QStringLiteral("addClass"));
        layoutWidget = new QWidget(addClass);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(300, 10, 224, 80));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_4->addWidget(label_5);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_4->addWidget(label_6);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_4->addWidget(label_7);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        addClass_duration = new QSpinBox(layoutWidget);
        addClass_duration->setObjectName(QStringLiteral("addClass_duration"));
        addClass_duration->setMinimum(15);
        addClass_duration->setMaximum(300);
        addClass_duration->setSingleStep(15);
        addClass_duration->setValue(90);

        horizontalLayout_13->addWidget(addClass_duration);

        addClass_everyWeek_checkB = new QCheckBox(layoutWidget);
        addClass_everyWeek_checkB->setObjectName(QStringLiteral("addClass_everyWeek_checkB"));
        addClass_everyWeek_checkB->setChecked(true);

        horizontalLayout_13->addWidget(addClass_everyWeek_checkB);


        verticalLayout_2->addLayout(horizontalLayout_13);

        addClass_roomTags = new LineEdit(layoutWidget);
        addClass_roomTags->setObjectName(QStringLiteral("addClass_roomTags"));

        verticalLayout_2->addWidget(addClass_roomTags);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        addClass_defNumOfRooms_checkB = new QCheckBox(layoutWidget);
        addClass_defNumOfRooms_checkB->setObjectName(QStringLiteral("addClass_defNumOfRooms_checkB"));
        addClass_defNumOfRooms_checkB->setChecked(true);

        horizontalLayout_3->addWidget(addClass_defNumOfRooms_checkB);

        addClass_nOfRooms = new QLineEdit(layoutWidget);
        addClass_nOfRooms->setObjectName(QStringLiteral("addClass_nOfRooms"));
        addClass_nOfRooms->setEnabled(false);

        horizontalLayout_3->addWidget(addClass_nOfRooms);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout_2->addLayout(verticalLayout_2);

        layoutWidget1 = new QWidget(addClass);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 10, 281, 76));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_3->addWidget(label);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_3->addWidget(label_2);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_3->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        addClass_subject = new QLineEdit(layoutWidget1);
        addClass_subject->setObjectName(QStringLiteral("addClass_subject"));

        verticalLayout->addWidget(addClass_subject);

        addClass_teachers = new LineEdit(layoutWidget1);
        addClass_teachers->setObjectName(QStringLiteral("addClass_teachers"));

        verticalLayout->addWidget(addClass_teachers);

        addClass_groups = new LineEdit(layoutWidget1);
        addClass_groups->setObjectName(QStringLiteral("addClass_groups"));

        verticalLayout->addWidget(addClass_groups);


        horizontalLayout->addLayout(verticalLayout);

        layoutWidget2 = new QWidget(addClass);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 90, 521, 22));
        horizontalLayout_15 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_13);

        addClass_addTaG_checkB = new QCheckBox(layoutWidget2);
        addClass_addTaG_checkB->setObjectName(QStringLiteral("addClass_addTaG_checkB"));

        horizontalLayout_15->addWidget(addClass_addTaG_checkB);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_14);

        editor_stackedW->addWidget(addClass);
        widget2 = new QWidget();
        widget2->setObjectName(QStringLiteral("widget2"));
        widget3 = new QWidget(widget2);
        widget3->setObjectName(QStringLiteral("widget3"));
        widget3->setGeometry(QRect(0, 30, 531, 31));
        horizontalLayout_16 = new QHBoxLayout(widget3);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_17);

        label_15 = new QLabel(widget3);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_16->addWidget(label_15);

        addSubject_name = new QLineEdit(widget3);
        addSubject_name->setObjectName(QStringLiteral("addSubject_name"));

        horizontalLayout_16->addWidget(addSubject_name);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_18);

        editor_stackedW->addWidget(widget2);
        addTeacher = new QWidget();
        addTeacher->setObjectName(QStringLiteral("addTeacher"));
        layoutWidget3 = new QWidget(addTeacher);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(11, 30, 511, 31));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(layoutWidget3);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_5->addWidget(label_4);

        addTeacher_name = new QLineEdit(layoutWidget3);
        addTeacher_name->setObjectName(QStringLiteral("addTeacher_name"));

        horizontalLayout_5->addWidget(addTeacher_name);


        horizontalLayout_6->addLayout(horizontalLayout_5);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        editor_stackedW->addWidget(addTeacher);
        addGroup = new QWidget();
        addGroup->setObjectName(QStringLiteral("addGroup"));
        layoutWidget4 = new QWidget(addGroup);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(13, 10, 511, 52));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_8 = new QLabel(layoutWidget4);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_5->addWidget(label_8);

        label_9 = new QLabel(layoutWidget4);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_5->addWidget(label_9);


        horizontalLayout_7->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        addGroup_name = new QLineEdit(layoutWidget4);
        addGroup_name->setObjectName(QStringLiteral("addGroup_name"));

        verticalLayout_6->addWidget(addGroup_name);

        addGroup_numOfStudents = new QLineEdit(layoutWidget4);
        addGroup_numOfStudents->setObjectName(QStringLiteral("addGroup_numOfStudents"));

        verticalLayout_6->addWidget(addGroup_numOfStudents);


        horizontalLayout_7->addLayout(verticalLayout_6);


        horizontalLayout_8->addLayout(horizontalLayout_7);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);

        editor_stackedW->addWidget(addGroup);
        addCourse = new QWidget();
        addCourse->setObjectName(QStringLiteral("addCourse"));
        layoutWidget5 = new QWidget(addCourse);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(10, 10, 511, 52));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_9);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        label_10 = new QLabel(layoutWidget5);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_7->addWidget(label_10);

        label_11 = new QLabel(layoutWidget5);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout_7->addWidget(label_11);


        horizontalLayout_9->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        addCourse_name = new LineEdit(layoutWidget5);
        addCourse_name->setObjectName(QStringLiteral("addCourse_name"));

        verticalLayout_8->addWidget(addCourse_name);

        addCourse_groups = new LineEdit(layoutWidget5);
        addCourse_groups->setObjectName(QStringLiteral("addCourse_groups"));

        verticalLayout_8->addWidget(addCourse_groups);


        horizontalLayout_9->addLayout(verticalLayout_8);


        horizontalLayout_10->addLayout(horizontalLayout_9);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_10);

        editor_stackedW->addWidget(addCourse);
        addRoom = new QWidget();
        addRoom->setObjectName(QStringLiteral("addRoom"));
        layoutWidget6 = new QWidget(addRoom);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(15, 10, 501, 78));
        horizontalLayout_12 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_11);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        label_12 = new QLabel(layoutWidget6);
        label_12->setObjectName(QStringLiteral("label_12"));

        verticalLayout_9->addWidget(label_12);

        label_13 = new QLabel(layoutWidget6);
        label_13->setObjectName(QStringLiteral("label_13"));

        verticalLayout_9->addWidget(label_13);

        label_14 = new QLabel(layoutWidget6);
        label_14->setObjectName(QStringLiteral("label_14"));

        verticalLayout_9->addWidget(label_14);


        horizontalLayout_11->addLayout(verticalLayout_9);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        addRoom_name = new QLineEdit(layoutWidget6);
        addRoom_name->setObjectName(QStringLiteral("addRoom_name"));

        verticalLayout_10->addWidget(addRoom_name);

        addRoom_size = new QLineEdit(layoutWidget6);
        addRoom_size->setObjectName(QStringLiteral("addRoom_size"));

        verticalLayout_10->addWidget(addRoom_size);

        addRoom_tags = new LineEdit(layoutWidget6);
        addRoom_tags->setObjectName(QStringLiteral("addRoom_tags"));

        verticalLayout_10->addWidget(addRoom_tags);


        horizontalLayout_11->addLayout(verticalLayout_10);


        horizontalLayout_12->addLayout(horizontalLayout_11);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_12);

        editor_stackedW->addWidget(addRoom);
        layoutWidget7 = new QWidget(widget_3);
        layoutWidget7->setObjectName(QStringLiteral("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(10, 10, 531, 25));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        comboBox = new QComboBox(layoutWidget7);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_4->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        add_btn = new QPushButton(layoutWidget7);
        add_btn->setObjectName(QStringLiteral("add_btn"));

        horizontalLayout_4->addWidget(add_btn);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        clear_btn = new QPushButton(layoutWidget7);
        clear_btn->setObjectName(QStringLiteral("clear_btn"));

        horizontalLayout_4->addWidget(clear_btn);

        horizontalSpacer_15 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_15);

        edit_btn = new QPushButton(layoutWidget7);
        edit_btn->setObjectName(QStringLiteral("edit_btn"));
        edit_btn->setEnabled(false);

        horizontalLayout_4->addWidget(edit_btn);

        horizontalSpacer_16 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_16);

        del_btn = new QPushButton(layoutWidget7);
        del_btn->setObjectName(QStringLiteral("del_btn"));
        del_btn->setEnabled(false);

        horizontalLayout_4->addWidget(del_btn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        widget_4 = new QWidget(centralwidget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setGeometry(QRect(580, 510, 531, 151));
        plainTextEdit = new QPlainTextEdit(widget_4);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(10, 10, 511, 121));
        plainTextEdit->setReadOnly(true);
        ConfigWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ConfigWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1124, 21));
        ConfigWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ConfigWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ConfigWindow->setStatusBar(statusbar);

        retranslateUi(ConfigWindow);

        editor_stackedW->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ConfigWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ConfigWindow)
    {
        ConfigWindow->setWindowTitle(QApplication::translate("ConfigWindow", "MainWindow", Q_NULLPTR));
        show_label->setText(QApplication::translate("ConfigWindow", "- - -", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = classes_treeW->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("ConfigWindow", "Classes", Q_NULLPTR));
        radioButton->setText(QApplication::translate("ConfigWindow", "Groups", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("ConfigWindow", "Teachers", Q_NULLPTR));
        label_5->setText(QApplication::translate("ConfigWindow", "Duration [min]", Q_NULLPTR));
        label_6->setText(QApplication::translate("ConfigWindow", "Room tags", Q_NULLPTR));
        label_7->setText(QApplication::translate("ConfigWindow", "Number of rooms", Q_NULLPTR));
        addClass_everyWeek_checkB->setText(QApplication::translate("ConfigWindow", "Every week", Q_NULLPTR));
        addClass_defNumOfRooms_checkB->setText(QApplication::translate("ConfigWindow", "Default", Q_NULLPTR));
        label->setText(QApplication::translate("ConfigWindow", "Subject", Q_NULLPTR));
        label_2->setText(QApplication::translate("ConfigWindow", "Teachers", Q_NULLPTR));
        label_3->setText(QApplication::translate("ConfigWindow", "Groups", Q_NULLPTR));
        addClass_addTaG_checkB->setText(QApplication::translate("ConfigWindow", "Add Teachers and Groups if necessary", Q_NULLPTR));
        label_15->setText(QApplication::translate("ConfigWindow", "Name", Q_NULLPTR));
        label_4->setText(QApplication::translate("ConfigWindow", "Name", Q_NULLPTR));
        label_8->setText(QApplication::translate("ConfigWindow", "Name", Q_NULLPTR));
        label_9->setText(QApplication::translate("ConfigWindow", "Number of students", Q_NULLPTR));
        label_10->setText(QApplication::translate("ConfigWindow", "Name", Q_NULLPTR));
        label_11->setText(QApplication::translate("ConfigWindow", "Groups", Q_NULLPTR));
        label_12->setText(QApplication::translate("ConfigWindow", "Name", Q_NULLPTR));
        label_13->setText(QApplication::translate("ConfigWindow", "Size", Q_NULLPTR));
        label_14->setText(QApplication::translate("ConfigWindow", "Tags", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("ConfigWindow", "Add class", Q_NULLPTR)
         << QApplication::translate("ConfigWindow", "Add subject", Q_NULLPTR)
         << QApplication::translate("ConfigWindow", "Add teacher", Q_NULLPTR)
         << QApplication::translate("ConfigWindow", "Add group", Q_NULLPTR)
         << QApplication::translate("ConfigWindow", "Add course", Q_NULLPTR)
         << QApplication::translate("ConfigWindow", "Add room", Q_NULLPTR)
        );
        add_btn->setText(QApplication::translate("ConfigWindow", "Add", Q_NULLPTR));
        clear_btn->setText(QApplication::translate("ConfigWindow", "Clear", Q_NULLPTR));
        edit_btn->setText(QApplication::translate("ConfigWindow", "Edit", Q_NULLPTR));
        del_btn->setText(QApplication::translate("ConfigWindow", "Delete", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConfigWindow: public Ui_ConfigWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGWINDOW_H
