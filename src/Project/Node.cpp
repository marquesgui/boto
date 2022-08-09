#include "Node.h"

#include <utility>

namespace Boto::Project {
  Pin::Pin(int id, std::string name, PinType type):
    Id(id), Name(std::move(name)), Type(type){}

  Node::Node(int id, std::string name):
    Id(id), Name(name);

}
