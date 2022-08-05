#include "Event.h"

Boto::Event::Event(const std::string& name, Boto::EventType type) {
  Name = name;
  Type = type;
}
