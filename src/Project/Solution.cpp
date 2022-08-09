#include "Solution.h"

namespace Boto::Project {

  Solution::Solution() {
    m_flows.push_back(std::make_shared<Flow>());
  }
}