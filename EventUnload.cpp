#include "EventUnload.h"

EventUnload::EventUnload(Item* item) {
    setType(UNLOAD_EVENT);
    item_to_unload = item;
};