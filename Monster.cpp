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
	move_slowdown = 20;
	move_cooldown = move_slowdown;

	if (velocity.getX() != 0 && velocity.getY() != 0) {
		moving = true;
	}
	else {
		moving = false;
	}


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
		else if (ec->getObject1()->getType() == "Portal") {
			usePortal(dynamic_cast<Portal*>(ec->getObject1()));
			WM.markForDelete(this);
			return 1;
		} 
		else if (ec->getObject2()->getType() == "Portal") {
			usePortal(dynamic_cast<Portal*>(ec->getObject2()));
			WM.markForDelete(this);
			return 1;
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

void Monster::usePortal(Portal* p)
{
	//LM.writeLog("arrow using portal");
	//if (portal_cooldown <= 0) {
	//	portal_cooldown = portal_slowdown;
	if (p->isBluePortal() && p->getOtherPortal() != NULL) {
		//LM.writeLog("blue");
		//this->setPosition(p->getOtherPortal()->getPosition() + Vector(3, 0));
		PortalDirection pd = p->getOtherPortal()->getDirection();
		Vector offset;
		Vector v;
		if (pd == D) {
			v.setXY(0, -0.75);
			offset.setXY(0, -3);
		}
		else if (pd == U) {
			v.setXY(0, 0.75);
			offset.setXY(0, 3);
		}
		else if (pd == L) {
			v.setXY(-1.5, 0);
			offset.setXY(-5, 0);
		}
		else if (pd == R) {
			v.setXY(1.5, 0);
			offset.setXY(5, 0);
		}
		new Monster(p->getOtherPortal()->getPosition() + offset, v, this->getId());
		p->getOtherPortal()->setSolidness(SOFT);
	}
	else if (!p->isBluePortal() && p->getOtherPortal() != NULL) {
		//this->setPosition(p->getOtherPortal()->getPosition()+Vector(3,0));
		PortalDirection pd = p->getOtherPortal()->getDirection();
		Vector offset;
		Vector v;
		if (pd == D) {
			v.setXY(0, -0.75);
			offset.setXY(0, -3);
		}
		else if (pd == U) {
			v.setXY(0, 0.75);
			offset.setXY(0, 3);
		}
		else if (pd == L) {
			v.setXY(-1.5, 0);
			offset.setXY(-5, 0);
		}
		else if (pd == R) {
			v.setXY(1.5, 0);
			offset.setXY(5, 0);
		}
		new Monster(p->getOtherPortal()->getPosition() + offset, v, this->getId());
		p->getOtherPortal()->setSolidness(SOFT);
	}
}