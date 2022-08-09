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

    Pin(int id, std::string  name, PinType type, );

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
    std::vector<Pin> Inputs;
    std::vector<Pin> Outputs;
    NodeType type;

    Node(int id, std::string name);
  };
}

#endif //BOTO_NODE_H
