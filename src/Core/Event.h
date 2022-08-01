#ifndef BOTO_EVENT_H
#define BOTO_EVENT_H

#include <string>

namespace Boto {
  enum class EventType {
    EVENT_TYPE_GUI
  };

  struct Event {
    EventType Type;
    std::string Name;

    Event(const std::string& name, EventType type);
  };
}

#endif //BOTO_EVENT_H
