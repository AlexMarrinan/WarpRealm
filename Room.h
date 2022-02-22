#pragma once
#include "Wall.h";
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <string>
#include "ObjectList.h"
#include "Color.h"
#include "Portal.h"
#include "Item.h"

#define ROOM_HEIGHT 13
#define ROOM_WIDTH 36

#define WALL_TILE 'X'
#define PORTAL_TILE 'P'
#define FLOOR_TILE '_'
#define WATER_TILE 'W'
#define KEY_TILE 'K'
#define LOCKEDDOOR_TILE 'L'

#define W_WALL_COLOR GREEN
#define W_PORTAL_COLOR WHITE

enum RoomDirection {
	LEFT = 0,
	RIGHT,
	UP,
	DOWN
};

class Room
{
private:
	std::vector<WallContainer*> walls;
	std::vector<ItemContainer*> items;
	ObjectList loaded;
	std::string filename;
	int id;
	void loadWalls(std::string filename);
	Room* left_room = NULL;
	Room* right_room = NULL;
	Room* up_room = NULL;
	Room* down_room = NULL;
public:
	bool load_key = false;
	static int next_id;
	Room(std::string);
	void loadRoom();
	void unloadRoom();
	int getId() const;
	void setNextRoom(Room* next_room, RoomDirection direction);
	Room* getNextRoom(RoomDirection direction);
	void removeObject(Object* p_o);
	void markItemUnload(int id);
};
