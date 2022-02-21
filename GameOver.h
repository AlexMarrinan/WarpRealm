#include "ViewObject.h"
#include "Object.h"

class GameOver : public df::ViewObject {

private:
    int time_to_live;
    void step();
public:
    GameOver();
    ~GameOver();
    int draw() override;
    int eventHandler(const df::Event* p_e) override;
};