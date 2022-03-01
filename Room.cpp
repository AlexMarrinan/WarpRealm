#include "Room.h"
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>`
#include "LogManager.h"
#include "WorldManager.h"
#include "Key.h"
#include "LockedDoor.h"
#include "Turret.h"
#include "Button.h"
#include "Door.h"
#include "Cube.h"
#include "Chest.h"
#include "PowerUp.h"
#include "EventButton.h"
#include "Monster.h"

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
				walls.push_back(new WallContainer(wt, Vector(k*2+4, i*1.95+1), (c == PORTAL_TILE)));
			}
			else if (c == WATER_TILE){
				walls.push_back(new WallContainer(WATER, Vector(k *2+4, i*1.95+1), false));
			}
			else if (c == FIZZLER_TILE) {
				walls.push_back(new WallContainer(FIZZLER, Vector(k * 2 + 4, i * 1.95 + 1), false));
			}
			else if (c == KEY_TILE) {
				items.push_back(new ItemContainer(KEY, Vector(k * 2 + 4, i * 1.95 +1), item_id));
				item_id++;
			}
			else if (c == LOCKEDDOOR_TILE_V) {
				items.push_back(new ItemContainer(LOCKED_DOOR_V, Vector(k * 2 + 4, i * 1.95 + 1), item_id));
				item_id++;
			}
			else if (c == LOCKEDDOOR_TILE_H) {
				items.push_back(new ItemContainer(LOCKED_DOOR_H, Vector(k * 2 + 4, i * 1.95 + 1), item_id));
				item_id++;
			}
			else if (c == TURRET_TILE) {
				items.push_back(new ItemContainer(TURRET, Vector(k * 2 + 4, i * 1.95 + 1), item_id));
				item_id++;
			}
			else if (c == BUTTON_TILE) {
				char cn = arr[i][k + 1];
				int n = 'a' - cn;
				if (!(n >= '0' && n <= '9')) {
					int n = 0;
				}
				items.push_back(new ItemContainer(BUTTON, Vector(k * 2 + 4, i * 1.95 + 1), item_id, n));
				item_id++;
			}
			else if (c == DOOR_TILE_V) {
				char cn = arr[i][k + 1];
				int n = 'a' - cn;
				if (!(n >= '0' && n <= '9')) {
					int n = 0;
					k++;
				}
				items.push_back(new ItemContainer(DOOR_V, Vector(k * 2 + 4, i * 1.95 + 1), item_id, n));
				item_id++;
			}
			else if (c == DOOR_TILE_H) {
				char cn = arr[i][k + 1];
				int n = 'a' - cn;
				if (!(n >= '0' && n <= '9')) {
					int n = 0;
					k++;
				}
				items.push_back(new ItemContainer(DOOR_H, Vector(k * 2 + 4, i * 1.95 + 1), item_id, n));
				item_id++;
			}
			else if (c == CUBE_TILE) {
				items.push_back(new ItemContainer(CUBE, Vector(k * 2 + 4, i * 1.95 + 1), item_id));
				item_id++;
			}
			else if (c == CHEST_TILE) {
				items.push_back(new ItemContainer(CHEST, Vector(k * 2 + 4, i * 1.95 + 1), item_id));
				item_id++;
			}
			else if (c == PORTALS_PU_TILE) {
				items.push_back(new ItemContainer(POWERUP, Vector(k * 2 + 4, i * 1.95 + 1), item_id, PORTALS));
				item_id++;
			}
			else if (c == SWORD_PU_TILE) {
				items.push_back(new ItemContainer(POWERUP, Vector(k * 2 + 4, i * 1.95 + 1), item_id, SWORD));
				item_id++;
			}
			else if (c == MONSTER_TILE) {
				items.push_back(new ItemContainer(MONSTER, Vector(k * 2 + 4, i * 1.95 + 1), item_id));
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
			else if (ic.getType() == LOCKED_DOOR_H) {
				LockedDoor* door = new LockedDoor(ic.getPosition(), true, ic.getId());
				//LM.writeLog("ic id: %d", ic.getId());
				loaded.insert(door);
			}
			else if (ic.getType() == LOCKED_DOOR_V) {
				LockedDoor* door = new LockedDoor(ic.getPosition(), false, ic.getId());
				//LM.writeLog("ic id: %d", ic.getId());
				loaded.insert(door);
			}
			else if (ic.getType() == TURRET) {
				Turret* turret = new Turret(ic.getPosition());
				//LM.writeLog("ic id: %d", ic.getId());
				loaded.insert(turret);
			}
			else if (ic.getType() == BUTTON) {
				Button* button = new Button(ic.getPosition(), ic.getId(), ic.getButtonId(), ic.activated);
				//LM.writeLog("ic id: %d", ic.getId());
				loaded.insert(button);
			}
			else if (ic.getType() == DOOR_H) {
				Door* door = new Door(ic.getPosition(), ic.getId(), ic.getButtonId(), HORIZONTAL);
				//LM.writeLog("ic id: %d", ic.getId());
				loaded.insert(door);
			}
			else if (ic.getType() == DOOR_V) {
				Door* door = new Door(ic.getPosition(), ic.getId(), ic.getButtonId(), VERTICAL);
				//LM.writeLog("ic id: %d", ic.getId());
				loaded.insert(door);
			}
			else if (ic.getType() == CUBE) {
				Cube* cube = new Cube(ic.getPosition(), ic.getId());
				//LM.writeLog("ic id: %d", ic.getId());
				loaded.insert(cube);
			}
			else if (ic.getType() == CHEST) {
				Chest* chest = new Chest(ic.getPosition(), ic.getId());
				//LM.writeLog("ic id: %d", ic.getId());
				loaded.insert(chest);
			}
			else if (ic.getType() == POWERUP) {
				PowerUp* pu = new PowerUp(ic.getPosition(), ic.getId(), ic.getPowerUpType());
				//LM.writeLog("ic id: %d", ic.getId());
				loaded.insert(pu);
			}
			else if (ic.getType() == MONSTER) {
				Monster* monster = new Monster(ic.getPosition(), Vector(0,0), ic.getId());
				//LM.writeLog("ic id: %d", ic.getId());
				loaded.insert(monster);
			}
		}
	}
}
void Room::unloadRoom() {
	WM.markForDelete(loaded);
	loaded.clear();
	//KNOWN ISSUE: 
	//When loading into a room with a door with the same id as a button being pressed in the previous room, the new door
	//starts open, avoid this issue by using different button ids on doors with rooms next to each other
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
			if (ic->getType() == BUTTON) {
				ic->activated = true;
			}
			else {
				LM.writeLog("found ic %d, marking for unload", ic->getId());
				ic->should_load = false;
				LM.writeLog("ic marked %d", ic->shouldLoad());
			}
			return;
		}
	}
}

ItemContainer* Room::getItemContainer(int id) {
	for (int i = 0; i < items.size(); i++) {
		if (items[i]->getId() == id) {
			return items[i];
		}
	}
	return NULL;
}

