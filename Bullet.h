#include "Object.h"
#include "EventCollision.h"

class Bullet : public df::Object {

private:
    void out();
    void hit(const df::EventCollision* p_collision_event);
    bool isBlue;
public:
    Bullet();
    Bullet(df::Vector hero_pos, bool isBlue = true);
    int eventHandler(const df::Event* p_e) override;
};