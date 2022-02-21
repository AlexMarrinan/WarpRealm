#include "Object.h"
#include "EventCollision.h"
#include "Saucer.h"

class BigSaucer : public Saucer {
private:
	int health;
	int dmg_slowdown;
	int dmg_countdown;
	void lowerHealth();
	int eventHandler(const df::Event* p_e) override;
public:
	BigSaucer();
	~BigSaucer();
	void hit(const df::EventCollision* p_c);
	void out();
};
