#pragma once
#include "Object.h"
#include "Vector.h"
#include "Event.h"
#include "Color.h"

using namespace df;

#define WALL_H1_STR "h_1"
#define WALL_V1_STR "v_1"
#define WALL_N1_STR "n_1"
#define WALL_WATER_STR "water_tile"

#define WALL_H1_STR_P "h_1_p"
#define WALL_V1_STR_P "v_1_p"
#define WALL_N1_STR_P "n_1_p"

enum WallType {
	H_1 = 0,
	V_1 = 1,
	N_1,
	WATER,
};
class Wall : public Object
{
private:
	WallType type;
	bool portals_work;
public:
	//Wall(WallType type);
	Wall(WallType type, Vector pos, bool portals);
	void setWallType(WallType);
	WallType getWallType() const;
	int eventHandler(Event* p_e);
	bool isPortalable() const;
};

class WallContainer {
private:
	WallType type;
	Vector position;
	bool portals_work;
public:
	WallContainer(WallType type, Vector position, bool portals);
	WallType getType() const;
	Vector getPosition() const;
	bool isPoralable() const;
};
