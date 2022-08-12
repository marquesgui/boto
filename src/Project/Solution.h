#ifndef BOTO_PROJECT_SOLUTION_H
#define BOTO_PROJECT_SOLUTION_H

#include "Flow.h"

#include <list>
#include <memory>

namespace Boto::Project {
  class Solution {
  public:
    Solution();

  private:
    std::list<std::shared_ptr<Flow>> m_flows;
  };
}
#endif //BOTO_PROJECT_SOLUTION_H