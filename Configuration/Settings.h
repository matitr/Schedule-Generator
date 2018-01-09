#pragma once
class Settings
{
	static Settings settings;

	int student_breaks_min;
	int student_breaks_max;
	int student_breaks_range;
	int student_start_min;
	int student_start_max;
	int student_start_range;

	int teachers_breaks_min;
	int teachers_breaks_max;
	int min_number_of_classes;

	int timeLineSize;
	
public:
	inline static Settings& getSettings() { return settings; };
	bool setStudentBreaksRange(int, int);
	bool setStudentStartRange(int, int);
	bool setTeacherBreaksRange(int, int);
//	bool setTeacherStartRange(int, int);
	bool setMinClassesPerDay(int);
	void setTimeLineSize(int len);

	inline int getStudentBreaksMin() { return settings.student_breaks_min; }
	inline int getStudentBreaksMax() { return settings.student_breaks_max; }
	inline int getStudentBreaksRange() { return settings.student_breaks_range; }
	inline int getStudentStartMin() { return settings.student_start_min; }
	inline int getStudentStartMax() { return settings.student_start_max; }
	inline int getStudentStartRange() { return settings.student_start_range; }

	inline int getTeacherBreaksMin() { return settings.teachers_breaks_min; }
	inline int getTeacherBreaksMax() { return settings.teachers_breaks_max; }
	inline int getMinNumberOfClasses() { return settings.min_number_of_classes; }
	static int getTimeLineSize() { return settings.timeLineSize; };
	Settings();
	~Settings();
};

