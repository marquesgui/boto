#ifndef BOTO_FLOW_H
#define BOTO_FLOW_H

#include "Node.h"

#include <list>

namespace Boto::Project {
  class FLow {

  private:
    std::list<Node> m_nodes;
  };
}

#endif //BOTO_FLOW_H
