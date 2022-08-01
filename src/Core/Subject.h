#ifndef BOTO_SUBJECT_H
#define BOTO_SUBJECT_H

#include "Observer.h"
#include "Event.h"

#include <memory>

class Subject {
public:
  virtual ~Subject() = default;
  virtual void AttachObserver(const std::shared_ptr<Observer>& observer) = 0;
  virtual void DetachObserver(Observer* observer) = 0;
  virtual void NotifyObserver(Boto::Event event) = 0;
};

#endif //BOTO_SUBJECT_H
