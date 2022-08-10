#include "Flow.h"

namespace Boto::Project {

  Flow::Flow() {
    int sharedId = 0;

    m_nodes.push_back(std::make_shared<Node>(sharedId++, "Http Event", NodeType::Blueprint));
    m_nodes.back()->Outputs.emplace_back(sharedId++, "Receveid", PinType::Flow, PinKind::Output);
    buildNode(m_nodes.back());
  }

  std::list<std::shared_ptr<Node>>& Flow::GetNodes() {
    return m_nodes;
  }

  void Flow::buildNode(const std::shared_ptr<Node>& node) {
    std::for_each(node->Inputs.begin(), node->Inputs.end(), [&](Pin pin) -> void {
      pin.Node = node;
    });

    std::for_each(node->Outputs.begin(), node->Outputs.end(), [&](Pin pin) -> void {
      pin.Node = node;
    });
  }
}