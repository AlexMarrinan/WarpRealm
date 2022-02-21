#include "Object.h"
#include "ViewObject.h"
#include "Event.h"
#include "EventStep.h"
#define POINTS_STRING "Points"

class Points : public df::ViewObject {

public:
    Points();
    static int high_score;
    int eventHandler(const df::Event* p_e) override;
};