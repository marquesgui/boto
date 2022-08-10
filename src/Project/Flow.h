#ifndef BOTO_FLOW_H
#define BOTO_FLOW_H

#include "Node.h"

#include <list>
#include <memory>

namespace Boto::Project {
  class Flow {

  public:
    Flow();
    std::list<std::shared_ptr<Node>>& GetNodes();

  private:
    std::list<std::shared_ptr<Node>> m_nodes;

  private:
    static void buildNode(const std::shared_ptr<Node>& node);
  };
}

#endif //BOTO_FLOW_H