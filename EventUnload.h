#include "Event.h"
#include "Item.h"

const std::string UNLOAD_EVENT = "unload";

class EventUnload : public df::Event {

public:
    Item* item_to_unload;
    EventUnload(Item* item);
};