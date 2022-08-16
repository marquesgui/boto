#ifndef BOTO_PROJECT_FLOW_H
#define BOTO_PROJECT_FLOW_H

#include "Node.h"

#include <list>
#include <memory>

namespace Boto::Project {
  class Flow {

  public:
    Flow();
    std::list<std::shared_ptr<Node>>& GetNodes();
    std::list<std::shared_ptr<Link>>& GetLinks();

  private:
    std::list<std::shared_ptr<Node>> m_nodes;
    std::list<std::shared_ptr<Link>> m_links;
  };
}

#endif //BOTO_PROJECT_FLOW_H