#ifndef BOTO_OBSERVER_H
#define BOTO_OBSERVER_H

#include "Event.h"

class Observer {
public:
  virtual ~Observer() = default;
  virtual void onNotify(const Boto::Event& event) = 0;
};


#endif //BOTO_OBSERVER_H
