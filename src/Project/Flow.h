#ifndef BOTO_FLOW_H
#define BOTO_FLOW_H

#include "Node.h"

#include <list>
#include <memory>

namespace Boto::Project {
  class Flow {

  public:
    Flow();

  private:
    std::list<std::shared_ptr<Node>> m_nodes;
  };
}

#endif //BOTO_FLOW_H