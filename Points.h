#include "Object.h"
#include "ViewObject.h"
#include "Event.h"
#include "EventStep.h"

#define POINTS_STRING "Keys"

class Points : public df::ViewObject {

public:
    Points();
    static int key_count;
    int eventHandler(const df::Event* p_e) override;
};