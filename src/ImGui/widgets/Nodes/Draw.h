#ifndef BOTO_GUI_DRAW_H
#define BOTO_GUI_DRAW_H

#include "../../../Project/Node.h"

#include <memory>
#include <list>

namespace pj = Boto::Project;

namespace Boto::Gui::Node {
  void DrawNode(const std::shared_ptr<pj::Node>& node, const std::list<std::shared_ptr<pj::Link>>& links);
}

#endif //BOTO_GUI_DRAW_H
