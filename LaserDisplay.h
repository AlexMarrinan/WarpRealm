#include "Object.h"
#include "ViewObject.h"
#include "Event.h"
#include "EventStep.h"
#define LASERDISPLAY_STRING "Laser Charge:"

class LaserDisplay : public df::ViewObject {

public:
    LaserDisplay();
    int eventHandler(const df::Event* p_e) override;
};