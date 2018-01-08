#include "InOut.h"
#include "MainWindow.h"

void InOut::printMenu() {
	printText("\n[0] Wypisz plan\n");
	printText("[1] Dodaj lekcje\n");
	printText("[2] Usun lekcje\n");
	printText("[3] Usun nauczyciela\n");
	printText("[4] Usun grupe\n");
	printText("[5] Zapisz\n");
	printText("[6] Zapisz i zakoncz\n");
}

string InOut::getWordFile(fstream& file) {
	string x;
	file >> x;
	return x;
}

string InOut::getLineFile(fstream& file) {
	string x;
	getline(file, x);
	return x;
}

void InOut::getLineFile(ifstream& file, string& line) {
	getline(file, line);
}

string InOut::getLineIostream() {
	string line;
	getline(cin, line);
	return line;
}

inline void InOut::printText(string text) {
    window->printInfo(text);
}

InOut::InOut(){
    window = nullptr;
}

InOut::InOut(MainWindow* w){
    window = w;
}

InOut::~InOut()
{
}
