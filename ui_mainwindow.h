/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *rightMenu;
    QTabWidget *tabWidget;
    QWidget *groups_tab;
    QTreeWidget *groups_treeW;
    QWidget *teachers_tab;
    QTreeWidget *teachers_treeW;
    QWidget *rooms_tab;
    QTreeWidget *rooms_treeW;
    QWidget *bottomMenu;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_10;
    QWidget *generator;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *generate_btn;
    QPushButton *stopGenerate_btn;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout;
    QLabel *generation_field;
    QLabel *fitness_field;
    QLabel *errors_field;
    QPushButton *showGenSettings_btn;
    QWidget *generator_settings_W;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *maxGen_checkB;
    QCheckBox *maxTime_checkB;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *maxGen_lineE;
    QLineEdit *maxTime_lineE;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *applyGenSettings_btn;
    QSpacerItem *horizontalSpacer_2;
    QWidget *info;
    QPlainTextEdit *info_field;
    QWidget *timeTable_widget;
    QTableWidget *timeTable_tableW;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1061, 665);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        rightMenu = new QWidget(centralWidget);
        rightMenu->setObjectName(QStringLiteral("rightMenu"));
        rightMenu->setGeometry(QRect(850, 10, 201, 481));
        tabWidget = new QTabWidget(rightMenu);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 186, 460));
        groups_tab = new QWidget();
        groups_tab->setObjectName(QStringLiteral("groups_tab"));
        groups_treeW = new QTreeWidget(groups_tab);
        groups_treeW->setObjectName(QStringLiteral("groups_treeW"));
        groups_treeW->setGeometry(QRect(10, 10, 161, 411));
        tabWidget->addTab(groups_tab, QString());
        teachers_tab = new QWidget();
        teachers_tab->setObjectName(QStringLiteral("teachers_tab"));
        teachers_treeW = new QTreeWidget(teachers_tab);
        teachers_treeW->setObjectName(QStringLiteral("teachers_treeW"));
        teachers_treeW->setGeometry(QRect(10, 10, 161, 411));
        tabWidget->addTab(teachers_tab, QString());
        rooms_tab = new QWidget();
        rooms_tab->setObjectName(QStringLiteral("rooms_tab"));
        rooms_treeW = new QTreeWidget(rooms_tab);
        rooms_treeW->setObjectName(QStringLiteral("rooms_treeW"));
        rooms_treeW->setGeometry(QRect(10, 10, 161, 411));
        tabWidget->addTab(rooms_tab, QString());
        bottomMenu = new QWidget(centralWidget);
        bottomMenu->setObjectName(QStringLiteral("bottomMenu"));
        bottomMenu->setGeometry(QRect(20, 510, 1031, 101));
        layoutWidget = new QWidget(bottomMenu);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 1021, 92));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        generator = new QWidget(layoutWidget);
        generator->setObjectName(QStringLiteral("generator"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(generator->sizePolicy().hasHeightForWidth());
        generator->setSizePolicy(sizePolicy);
        generator->setMinimumSize(QSize(185, 90));
        layoutWidget1 = new QWidget(generator);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 60, 158, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        generate_btn = new QPushButton(layoutWidget1);
        generate_btn->setObjectName(QStringLiteral("generate_btn"));

        horizontalLayout_2->addWidget(generate_btn);

        stopGenerate_btn = new QPushButton(layoutWidget1);
        stopGenerate_btn->setObjectName(QStringLiteral("stopGenerate_btn"));
        stopGenerate_btn->setEnabled(false);
        stopGenerate_btn->setMouseTracking(false);
        stopGenerate_btn->setCheckable(false);
        stopGenerate_btn->setChecked(false);
        stopGenerate_btn->setAutoDefault(false);
        stopGenerate_btn->setFlat(false);

        horizontalLayout_2->addWidget(stopGenerate_btn);

        layoutWidget2 = new QWidget(generator);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 0, 55, 53));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        label = new QLabel(layoutWidget2);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        layoutWidget3 = new QWidget(generator);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(90, 0, 66, 53));
        verticalLayout = new QVBoxLayout(layoutWidget3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        generation_field = new QLabel(layoutWidget3);
        generation_field->setObjectName(QStringLiteral("generation_field"));

        verticalLayout->addWidget(generation_field);

        fitness_field = new QLabel(layoutWidget3);
        fitness_field->setObjectName(QStringLiteral("fitness_field"));

        verticalLayout->addWidget(fitness_field);

        errors_field = new QLabel(layoutWidget3);
        errors_field->setObjectName(QStringLiteral("errors_field"));

        verticalLayout->addWidget(errors_field);

        showGenSettings_btn = new QPushButton(generator);
        showGenSettings_btn->setObjectName(QStringLiteral("showGenSettings_btn"));
        showGenSettings_btn->setGeometry(QRect(160, 33, 25, 25));
        showGenSettings_btn->setFlat(true);

        horizontalLayout_10->addWidget(generator);

        generator_settings_W = new QWidget(layoutWidget);
        generator_settings_W->setObjectName(QStringLiteral("generator_settings_W"));
        generator_settings_W->setMinimumSize(QSize(220, 90));
        generator_settings_W->setMaximumSize(QSize(220, 16777215));
        layoutWidget4 = new QWidget(generator_settings_W);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(0, 0, 214, 83));
        verticalLayout_5 = new QVBoxLayout(layoutWidget4);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        maxGen_checkB = new QCheckBox(layoutWidget4);
        maxGen_checkB->setObjectName(QStringLiteral("maxGen_checkB"));
        maxGen_checkB->setMinimumSize(QSize(100, 0));
        maxGen_checkB->setMaximumSize(QSize(100, 16777215));

        verticalLayout_4->addWidget(maxGen_checkB);

        maxTime_checkB = new QCheckBox(layoutWidget4);
        maxTime_checkB->setObjectName(QStringLiteral("maxTime_checkB"));
        maxTime_checkB->setMinimumSize(QSize(100, 0));
        maxTime_checkB->setMaximumSize(QSize(100, 16777215));

        verticalLayout_4->addWidget(maxTime_checkB);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        maxGen_lineE = new QLineEdit(layoutWidget4);
        maxGen_lineE->setObjectName(QStringLiteral("maxGen_lineE"));
        maxGen_lineE->setMinimumSize(QSize(100, 0));
        maxGen_lineE->setMaximumSize(QSize(100, 16777215));

        verticalLayout_3->addWidget(maxGen_lineE);

        maxTime_lineE = new QLineEdit(layoutWidget4);
        maxTime_lineE->setObjectName(QStringLiteral("maxTime_lineE"));
        maxTime_lineE->setMinimumSize(QSize(100, 0));
        maxTime_lineE->setMaximumSize(QSize(100, 16777215));

        verticalLayout_3->addWidget(maxTime_lineE);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        applyGenSettings_btn = new QPushButton(layoutWidget4);
        applyGenSettings_btn->setObjectName(QStringLiteral("applyGenSettings_btn"));

        horizontalLayout_3->addWidget(applyGenSettings_btn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_3);


        horizontalLayout_10->addWidget(generator_settings_W);

        info = new QWidget(layoutWidget);
        info->setObjectName(QStringLiteral("info"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(info->sizePolicy().hasHeightForWidth());
        info->setSizePolicy(sizePolicy1);
        info->setMinimumSize(QSize(200, 80));
        info_field = new QPlainTextEdit(info);
        info_field->setObjectName(QStringLiteral("info_field"));
        info_field->setEnabled(true);
        info_field->setGeometry(QRect(0, 0, 331, 81));
        info_field->setReadOnly(true);

        horizontalLayout_10->addWidget(info);

        timeTable_widget = new QWidget(centralWidget);
        timeTable_widget->setObjectName(QStringLiteral("timeTable_widget"));
        timeTable_widget->setGeometry(QRect(10, 10, 831, 491));
        timeTable_tableW = new QTableWidget(timeTable_widget);
        timeTable_tableW->setObjectName(QStringLiteral("timeTable_tableW"));
        timeTable_tableW->setGeometry(QRect(10, 10, 811, 471));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1061, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        stopGenerate_btn->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = groups_treeW->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Name", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(groups_tab), QApplication::translate("MainWindow", "Groups", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem1 = teachers_treeW->headerItem();
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "Name", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(teachers_tab), QApplication::translate("MainWindow", "Teachers", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem2 = rooms_treeW->headerItem();
        ___qtreewidgetitem2->setText(0, QApplication::translate("MainWindow", "Name", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(rooms_tab), QApplication::translate("MainWindow", "Rooms", Q_NULLPTR));
        generate_btn->setText(QApplication::translate("MainWindow", "Generate", Q_NULLPTR));
        stopGenerate_btn->setText(QApplication::translate("MainWindow", "Stop", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Generation", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Fitness", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Errors", Q_NULLPTR));
        generation_field->setText(QApplication::translate("MainWindow", "<html><head/><body><p>----------------</p></body></html>", Q_NULLPTR));
        fitness_field->setText(QApplication::translate("MainWindow", "<html><head/><body><p>----------------</p></body></html>", Q_NULLPTR));
        errors_field->setText(QApplication::translate("MainWindow", "<html><head/><body><p>----------------</p></body></html>", Q_NULLPTR));
        showGenSettings_btn->setText(QString());
        maxGen_checkB->setText(QApplication::translate("MainWindow", "max Generation", Q_NULLPTR));
        maxTime_checkB->setText(QApplication::translate("MainWindow", "max Time[s]", Q_NULLPTR));
        applyGenSettings_btn->setText(QApplication::translate("MainWindow", "Apply", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
