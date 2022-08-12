#ifndef BOTO_PROJECT_NODE_H
#define BOTO_PROJECT_NODE_H

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
    Event,
  };

  enum class PinKind {
    Input,
    Output
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
    Default,
    String
  };

  struct Node {
  public:
    int Id;
    std::string Name;
    std::vector<std::shared_ptr<Pin>> Inputs;
    std::vector<std::shared_ptr<Pin>> Outputs;

  public:
    Node(int id, std::string name);
    virtual NodeType GetType() = 0;
  };

  struct Link {
    int Id;
    int StartPinId;
    int EndPinId;

    Link(int id, int startPinId, int endPinId);
  };

  //Nodes
  struct StringNode : public Node {
    std::string Value;
    explicit StringNode(int id);
    NodeType GetType() override;
  };

  struct HttpRequestEventNode : public Node {
    explicit HttpRequestEventNode(int id);
    NodeType GetType() override;
  };
}

#endif //BOTO_PROJECT_NODE
