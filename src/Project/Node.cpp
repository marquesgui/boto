#include "Node.h"
#include "../Utils/IdGenerator.h"

#include <utility>

namespace IdGenerator = Boto::Utils::IdGenerator;

namespace Boto::Project {
  //Pin
  Pin::Pin(int id, std::string name, PinType type, PinKind kind):
    Id(id), Name(std::move(name)), Type(type), Kind(kind) {}

  Pin::~Pin() {
    Node = nullptr;
  }

  std::string PinTypeAsString(PinType& type) {
    switch (type) {
      case PinType::Flow:
        return "Flow";
      case PinType::Bool:
        return "Bool";
      case PinType::Int:
        return "Int";
      case PinType::Float:
        return "Float";
      case PinType::String:
        return "String";
      case PinType::Object:
        return "Object";
      case PinType::Function:
        return "Function";
      case PinType::Delegate:
        return "Delegate";
      case PinType::Event:
        return "Event";
      case PinType::Json:
        return "Json";
    }
  }

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
    Outputs.back()->Node = this;
    this->Value = "/api/test";
  }

  NodeType StringNode::GetType() {
    return NodeType::String;
  }

  //HttpRequestEventNode
  HttpRequestEventNode::HttpRequestEventNode(int id) : Node(id, "HttpRequestEvent") {
    Inputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "path", PinType::String, PinKind::Input));
    Inputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "schema", PinType::Json, PinKind::Input));
    for (auto& input : Inputs) {
      input->Node = this;
    }

    Outputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "received", PinType::Flow, PinKind::Output));
    Outputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "parameters", PinType::Json, PinKind::Output));
    Outputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "body", PinType::Json, PinKind::Output));
    for (auto& output : Outputs) {
      output->Node = this;
    }
  }

  NodeType HttpRequestEventNode::GetType() {
    return NodeType::Default;
  }

  //HttpController
  HttpControllerNode::HttpControllerNode(int id) : Node(id, "HttpController") {
    Inputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "", PinType::Flow, PinKind::Input));
    for(auto& input : Inputs) {
      input->Node = this;
    }

    Outputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "get", PinType::Flow, PinKind::Output));
    Outputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "post", PinType::Flow, PinKind::Output));
    Outputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "put", PinType::Flow, PinKind::Output));
    Outputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "patch", PinType::Flow, PinKind::Output));
    for(auto& output : Outputs){
      output->Node = this;
    }
  }

  //JsonExtractorNode
  JsonExtractorNode::JsonExtractorNode(int id) : Node(id, "JsonExtractor"){
    Inputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "", PinType::Flow, PinKind::Input));
    Inputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "json", PinType::Json, PinKind::Input));
    Inputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "json path", PinType::String, PinKind::Input));
    for(auto& input : Inputs) {
      input->Node = this;
    }

    Outputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "", PinType::Flow, PinKind::Output));
    Outputs.push_back(std::make_shared<Pin>(IdGenerator::GetNextId(), "value", PinType::String, PinKind::Output));
    for(auto& output : Outputs) {
      output->Node = this;
    }
  }
}
