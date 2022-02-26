#include "Monster.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "EventDetect.h"

Monster::Monster(df::Vector position, df::Vector velocity, int id) {
	h = NULL;
	setType("Enemy");
	setSprite("monster");
	setPosition(position);
	setHealth(3);
	setDamage(1);
	setId(id);
	setVelocity(velocity);
	registerInterest(df::COLLISION_EVENT);
	registerInterest(DETECT_EVENT);
	moving = false;
	move_slowdown = 20;
	move_cooldown = move_slowdown;

}
int Monster::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == DETECT_EVENT && !moving) {
		if (move_cooldown > 0) {
			move_cooldown--;
			return 1;
		}
		if (h == NULL) {
			const EventDetect* p_ed = dynamic_cast<const EventDetect*>(p_e);
			h = p_ed->hero;
		}
		int x = getPosition().getX();
		int y = getPosition().getY();
		int h_x = h->getPosition().getX();
		int h_y = h->getPosition().getY();

		if (h_x > x && h_y < y + 2 && h_y > y - 2) {
			setVelocity(Vector(1.5, 0));
		}
		else if (h_x < x && h_y < y + 2 && h_y > y - 2) {
			setVelocity(Vector(-1.5, 0));
		}
		else if (h_y > y && h_x < x + 3 && h_x > x - 3) {
			setVelocity(Vector(0, 0.75));
		}
		else if (h_y < y && h_x < x + 3 && h_x > x - 3) {
			setVelocity(Vector(0, -0.75));
		}
		else {
			return 1;
		}
		moving = true;
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT && moving) {
		//LM.writeLog("Enemy hit");
		const df::EventCollision* ec = dynamic_cast<const df::EventCollision*>(p_e);
		//LM.writeLog("%s", ec->getObject1()->getType().c_str());
		//LM.writeLog("%s", ec->getObject2()->getType().c_str());
		if ((ec->getObject1()->getType() == "Sword" || ec->getObject2()->getType() == "Sword") && damage_cooldown == 0) {
			takeDamage(1);
		}
		else if ((ec->getObject1()->getType() == "Button" || ec->getObject2()->getType() == "Button") ||
				(ec->getObject1()->getType() == "Fizzler" || ec->getObject2()->getType() == "Fizzler")) {
			return 1;
		}
		move_cooldown = move_slowdown;
		moving = false;
		setVelocity(df::Vector(0, 0));
		return 1;
	}
	return Enemy::eventHandler(p_e);
}
