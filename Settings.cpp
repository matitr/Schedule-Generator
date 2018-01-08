#include "Settings.h"

Settings Settings::settings;

bool Settings::setStudentBreaksRange(int min, int max) {
	if (min < 0 || max < 0 || min > max)
		return false;

	student_breaks_min = min;
	student_breaks_max = max;

	student_breaks_range = max - min + 1;

	return true;
}

bool Settings::setStudentStartRange(int min, int max) {
	if (min < 0 || max < 0 || min > max)
		return false;

	student_start_min = min;
	student_start_max = max;

	student_start_range = max - min + 1;

	return true;
}

bool Settings::setTeacherBreaksRange(int min, int max) {
	if (min < 0 || max < 0 || min > max)
		return false;

	teachers_breaks_min = min;
	teachers_breaks_max = max;

	return true;
}

bool Settings::setMinClassesPerDay(int min) {
	if (min < 0)
		return false;

	min_number_of_classes = min;
	return true;
}

void Settings::setTimeLineSize(int len) {
	timeLineSize = len;
}

Settings::Settings(){
	student_breaks_min = 0;
	student_breaks_max = 0;
	student_start_min = 0;
	student_start_max = 0;

	timeLineSize = 0;
}


Settings::~Settings(){

}
