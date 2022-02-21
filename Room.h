#pragma once
#include "Wall.h";
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <string>
#include "ObjectList.h"

#define ROOM_HEIGHT 12
#define ROOM_WIDTH 24

#define WALL_TILE 'X'
#define PORTAL_TILE 'P'
#define FLOOR_TILE '_'
#define WATER_TILE 'W'
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
	std::vector<WallContainer> walls;
	ObjectList loaded;
	std::string filename;
	int id;
	void loadWalls(std::string filename);
	Room* left_room = NULL;
	Room* right_room = NULL;
	Room* up_room = NULL;
	Room* down_room = NULL;
public:
	static int next_id;
	Room(std::string);
	void loadRoom();
	void unloadRoom();
	int getId() const;
	void setNextRoom(Room* next_room, RoomDirection direction);
	Room* getNextRoom(RoomDirection direction);
};

