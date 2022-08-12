#include "Node.h"
#include "../Utils/IdGenerator.h"

#include <utility>

namespace IdGenerator = Boto::Utils::IdGenerator;

namespace Boto::Project {
  //Pin
  Pin::Pin(int id, std::string name, PinType type, PinKind kind):
    Id(id), Name(std::move(name)), Type(type), Kind(kind) {}

  //Node
  Node::Node(int id, std::string name):
    Id(id), Name(std::move(name)){}

  NodeType Node::GetType() {
    return NodeType::Default;
  }

  //Link
  Link::Link(int id, int startPinId, int endPinId):
      Id(id), StartPinId(startPinId), EndPinId(endPinId){}

  //StringNode
  StringNode::StringNode(int id) : Node(id, "string") {
    Outputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "value", PinType::String, PinKind::Output));
  }

  NodeType StringNode::GetType() {
    return NodeType::String;
  }

  //HttpRequestEventNode
  HttpRequestEventNode::HttpRequestEventNode(int id) : Node(id, "HttpRequestEvent") {
    Inputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "path", PinType::String, PinKind::Input));
    Outputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "on received", PinType::Event, PinKind::Output));
  }

  NodeType HttpRequestEventNode::GetType() {
    return NodeType::Default;
  }
}
