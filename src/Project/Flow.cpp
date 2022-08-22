#include "Flow.h"
#include "../Utils/IdGenerator.h"

namespace Boto::Project {

  namespace IdGenerator = Utils::IdGenerator;

  Flow::Flow() {
    m_nodes.push_back(std::make_shared<StringNode>(IdGenerator::GetNextId()));
    m_nodes.push_back(std::make_shared<HttpRequestEventNode>(IdGenerator::GetNextId()));
    m_nodes.push_back(std::make_shared<HttpControllerNode>(IdGenerator::GetNextId()));
    m_nodes.push_back(std::make_shared<JsonExtractorNode>(IdGenerator::GetNextId()));
  }

  std::list<std::shared_ptr<Node>>& Flow::GetNodes() {
    return m_nodes;
  }

  std::list<std::shared_ptr<Link>>& Flow::GetLinks() {
    return m_links;
  }
}