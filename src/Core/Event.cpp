//
// Created by Guilherme Marques de Oliveira on 29/07/22.
//

#include "Event.h"

Boto::Event::Event(const std::string& name, Boto::EventType type) {
  Name = name;
  Type = type;
}
