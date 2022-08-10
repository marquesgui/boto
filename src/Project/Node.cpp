#include "Node.h"

#include <utility>

namespace Boto::Project {
  Pin::Pin(int id, std::string name, PinType type, PinKind kind):
    Id(id), Name(std::move(name)), Type(type), Kind(kind){}

  Node::Node(int id, std::string name, NodeType type):
    Id(id), Name(std::move(name)), Type(type){}

  Link::Link(int id, int startPinId, int endPinId):
    Id(id), StartPinId(startPinId), EndPinId(endPinId){}

}
