#ifndef BOTO_PINICON_H
#define BOTO_PINICON_H

#include <imgui/imgui.h>

namespace Boto::Gui::Node {
  enum class IconType {
    Flow,
    Circle,
    Square,
    Grid,
    RoundSquare,
    Diamond
  };

  struct PinIcon {
    static void Draw(ImDrawList* drawList, const ImVec2& cursorStartPos, const ImVec2& cursorEndPos,
                     IconType type, bool filled, ImColor color, ImColor innerColor);
  };
}

#endif //BOTO_PINICON_H
