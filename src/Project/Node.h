#ifndef BOTO_NODE_H
#define BOTO_NODE_H

#include <list>
#include <memory>
#include <string>

namespace Boto::Project {

  class Node;

  enum class OutputType {
    Number,
    String
  };

  enum class InputType {
    Number,
    String
  };

  class Output {
    OutputType type;
    Node* node;
  };

  class Input {
    InputType type;
    Node* node;
  };

  enum class NodeType {

  };

  class Node {
  public:
    Node(std::string  Name, NodeType type);
    virtual ~Node() = default;

  public:
    const std::string Name;
    const NodeType Type;

  private:
    std::list<std::shared_ptr<Input>> m_inputs;
    std::list<std::shared_ptr<Output>> m_outputs;
  };
}

#endif //BOTO_NODE_H
