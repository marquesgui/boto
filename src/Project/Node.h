#ifndef BOTO_NODE_H
#define BOTO_NODE_H


#include <memory>
#include <string>
#include <vector>

namespace Boto::Project {

  enum class PinType {
    Flow,
    Bool,
    Int,
    Float,
    String,
    Object,
    Function,
    Delegate,
  };

  enum class PinKind {
    Output,
    Input
  };

  struct Node;

  struct Pin {
    int Id;
    std::shared_ptr<Node> Node;
    std::string Name;
    PinType Type;
    PinKind Kind;

    Pin(int id, std::string  name, PinType type, PinKind kind);

  };

  enum class NodeType
  {
    Blueprint,
    Simple,
    Tree,
    Comment,
    Houdini
  };

  struct Node {
    int Id;
    std::string Name;
    std::vector<std::shared_ptr<Pin>> Inputs;
    std::vector<std::shared_ptr<Pin>> Outputs;
    NodeType Type;

    Node(int id, std::string name, NodeType type);
  };

  struct Link {
    int Id;
    int StartPinId;
    int EndPinId;

    Link(int id, int startPinId, int endPinId);
  };
}

#endif //BOTO_NODE_H
