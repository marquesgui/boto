#include "Node.h"

#include <utility>

namespace Boto::Project {
  Node::Node(std::string  name, NodeType type)
    : Name(std::move(name)), Type(type){

  }
}
