#include "Room.h"
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>`
#include "LogManager.h"
#include "WorldManager.h"
#include "Key.h"
#include "LockedDoor.h"

Room::Room(std::string filename) {
	this->id = 0;//next_id;
	//next_id++;
	this->filename = filename;
	loadWalls(filename);
}
void Room::loadWalls(std::string filename) {
	std::ifstream inputMap(filename);
	//std::string str((std::istreambuf_iterator<char>(inputMap)),
		//std::istreambuf_iterator<char>());
	LM.writeLog("READING ROOM FILE");

	char arr[ROOM_HEIGHT+1][ROOM_WIDTH+1];
	for (int i = 0; i < ROOM_HEIGHT; i++)
	{
		std::string input;
		std::getline(inputMap, input);
		//LM.writeLog("input: %s", input.c_str());
		for (int k = 0; k < input.length(); k++)
		{
			arr[i][k] = input[k];
		}
	}
	int item_id = 0;
	for (int i = 0; i < ROOM_HEIGHT+1; i++)
	{
		for (int k = 0; k < ROOM_WIDTH+1; k++)
		{
			WallType wt;
			char c = arr[i][k];
			if (c == WALL_TILE || c == PORTAL_TILE) {
				if ((arr[i + 1][k] == WALL_TILE || arr[i + 1][k] == PORTAL_TILE) &&
					(arr[i- 1][k] == WALL_TILE || arr[i - 1][k] == PORTAL_TILE)){
					wt = V_1;
				}
				else if ((arr[i][k + 1] == WALL_TILE || arr[i][k+1] == PORTAL_TILE) &&
					(arr[i ][k - 1] == WALL_TILE || arr[i][k - 1] == PORTAL_TILE)) {
					wt = H_1;
				}
				else {
					wt = N_1;
				}
				walls.push_back(new WallContainer(wt, Vector(k*2+4, i*1.95+0.5), (c == PORTAL_TILE)));
			}
			else if (c == WATER_TILE){
				walls.push_back(new WallContainer(WATER, Vector(k *2+4, i*1.95+0.5), false));
			}
			else if (c == KEY_TILE) {
				items.push_back(new ItemContainer(KEY, Vector(k * 2 + 4, i * 1.95 + 0.5), item_id));
				item_id++;
			}
			else if (c == LOCKEDDOOR_TILE) {
				items.push_back(new ItemContainer(LOCKED_DOOR, Vector(k * 2 + 4, i * 1.95 + 0.5), item_id));
				item_id++;
			}
			else if (c == FLOOR_TILE) {
				//Dont make any walls
			}
		}
	}
}
void Room::loadRoom() {
	for (int i = 0; i < walls.size(); i++) {
		//LM.writeLog("In load rooms");
		WallContainer wc = *walls[i];
		Wall* w = new Wall(wc.getType(), wc.getPosition(), wc.isPoralable());
		loaded.insert(w);
	}
	for (int i = 0; i < items.size(); i++) {
		ItemContainer ic = *items[i];
		LM.writeLog("should load: %d", ic.shouldLoad());
		if (ic.shouldLoad()) {
			if (ic.getType() == KEY) {
				Key* key = new Key(ic.getPosition(), ic.getId());
				//LM.writeLog("ic id: %d", ic.getId());
				loaded.insert(key);
			}
			if (ic.getType() == LOCKED_DOOR) {
				LockedDoor* door = new LockedDoor(ic.getPosition(), ic.getId());
				//LM.writeLog("ic id: %d", ic.getId());
				loaded.insert(door);
			}
		}
	}
}
void Room::unloadRoom() {
	WM.markForDelete(loaded);
	loaded.clear();
}
int Room::getId() const {
	return id;
}
void Room::setNextRoom(Room* next_room, RoomDirection direction) {
	switch (direction) {
	case RoomDirection::LEFT:
		left_room = next_room;
		return;
	case RoomDirection::RIGHT:
		right_room = next_room;
		return;
	case RoomDirection::UP:
		up_room = next_room;
		return;
	case RoomDirection::DOWN:
		down_room = next_room;
		return;
	}
}
Room* Room::getNextRoom(RoomDirection direction) {
	switch (direction) {
	case RoomDirection::LEFT:
		return left_room;
	case RoomDirection::RIGHT:
		return right_room;
	case RoomDirection::UP:
		return up_room;
	case RoomDirection::DOWN:
		return down_room;
	}
	return NULL;
}
void Room::removeObject(Object* p_o) {
	loaded.remove(p_o);
}

void Room::markItemUnload(int id) {
	for (int i = 0; i < items.size(); i++) {
		ItemContainer* ic = items[i];
		if (ic->getId() == id) {
			LM.writeLog("found ic %d, marking for unload", ic->getId());
			ic->should_load = false;
			LM.writeLog("ic marked %d", ic->shouldLoad());
			return;
		}
	}
}

