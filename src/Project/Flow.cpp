#include "Flow.h"

namespace Boto::Project {

  Flow::Flow() {
    auto node1 = std::make_shared<Node>("HTTP Event", NodeType::Event);

    auto output1 = std::make_shared<Output>(OutputType::Trigger, nullptr);
    node1->AddOutput(output1);

    m_nodes.push_back(node1);
  }
}