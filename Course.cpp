#include "Course.h"



Course::Course(int _id, string _name, list<Group*> _groups){
	id = _id;
	name = _name;

	for (list<Group*>::iterator it = _groups.begin(); it != _groups.end(); it++)
		groups.push_back(*it);
}


Course::~Course(){

}
