#ifndef BOTO_FLOW_H
#define BOTO_FLOW_H

#include "Node.h"

#include <list>
#include <memory>

namespace Boto::Project {
  class Flow {

  public:
    Flow();
    const std::list<std::shared_ptr<Node>>& GetNodes();
    const std::list<std::shared_ptr<Link>>& GetLinks();

  private:
    std::list<std::shared_ptr<Node>> m_nodes;
    std::list<std::shared_ptr<Link>> m_links;

  private:
    static void buildNode(const std::shared_ptr<Node>& node);
  };
}

#endif //BOTO_FLOW_H