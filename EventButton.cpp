#include "EventButton.h"

EventButton::EventButton(int output_id, int value) {
    setType(BUTTON_EVENT);
    this->output_id = output_id;
    this->value = value;
}