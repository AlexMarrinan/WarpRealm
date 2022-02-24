#include "Event.h"

const std::string BUTTON_EVENT = "button";

class EventButton : public df::Event {

public:
    int output_id;
    int value;
    EventButton(int output_id, int value);
};