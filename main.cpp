#include "List.h"
#include "SeparateSchedule.h"
#include "MainWindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <QApplication>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();


    /*
    SeparateSchedule* a = new SeparateSchedule;
    a->run();
    delete a;
    system("pause");
    */
//    List a;
app.exec();
    return 0 ;
}
