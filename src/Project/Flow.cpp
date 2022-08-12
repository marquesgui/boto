#include "Flow.h"
#include "../Utils/IdGenerator.h"

namespace Boto::Project {

  namespace IdGenerator = Utils::IdGenerator;

  Flow::Flow() {
    m_nodes.push_back(std::make_shared<StringNode>(IdGenerator::GetNextId()));
    m_nodes.push_back(std::make_shared<HttpRequestEventNode>(IdGenerator::GetNextId()));

    for(auto& node : m_nodes) {
      buildNode(node);
    }
  }

  std::list<std::shared_ptr<Node>>& Flow::GetNodes() {
    return m_nodes;
  }

  std::list<std::shared_ptr<Link>>& Flow::GetLinks() {
    return m_links;
  }

  void Flow::buildNode(const std::shared_ptr<Node>& node) {
    std::for_each(node->Inputs.begin(), node->Inputs.end(), [&](const std::shared_ptr<Pin>& pin) -> void {
      pin->Node = node;
    });

    std::for_each(node->Outputs.begin(), node->Outputs.end(), [&](const std::shared_ptr<Pin>& pin) -> void {
      pin->Node = node;
    });
  }
}