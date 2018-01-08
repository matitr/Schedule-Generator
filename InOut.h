#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

class MainWindow;

class InOut
{
public:
    MainWindow* window;

    void setWindow(MainWindow* w) { window = w; }
	void printMenu();
	string getWordFile(fstream&);
	string getLineFile(fstream&);
	void getLineFile(ifstream&, string&);
	string getLineIostream();
	inline char getChar() { return _getch(); }
	inline void cinSync() { cin.sync(); }
    inline void printText(string text);
	static inline void clearConsole() { system("cls"); }
	static void saveLineFile(ofstream& file, string line) { file << line; }
	InOut();
    InOut(MainWindow*);
	~InOut();
};

