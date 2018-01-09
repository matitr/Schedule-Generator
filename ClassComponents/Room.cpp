#include "Room.h"


void Room::addTag(string tag) {
//	tags.push_back(tag);

	std::transform(tag.begin(), tag.end(), tag.begin(), ::tolower);

	tags.insert(pair<string, int>(tag, 0));
}

Room::Room(int id, string name, int size){
	_id = id;
	_name = name;
	_size = size;
	configLine = "";
}


Room::~Room()
{
}
