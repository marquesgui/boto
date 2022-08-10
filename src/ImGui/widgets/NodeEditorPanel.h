#ifndef BOTO_NODEEDITORPANEL_H
#define BOTO_NODEEDITORPANEL_H

#include "ImGuiWidget.h"
#include "../../Project/Flow.h"

#include <imgui-node-editor/imgui_node_editor.h>

namespace ne = ax::NodeEditor;

namespace Boto::Gui {

  class NodeEditorPanel : public ImGuiWidget {

  public: //Override ImGuiWidget
    void Draw() override;
    void OnAdded() override;

  public:
    void SetFlow(const std::shared_ptr<Project::Flow>& flow);

  private:
    ne::EditorContext* m_editor;
    std::shared_ptr<Project::Flow> m_flow;
    std::shared_ptr<Project::Pin> m_newLinkPin = nullptr;
    static const int m_pinIconSize = 14;

  private:
    static bool canCreateLink(const std::shared_ptr<Project::Pin>& pin1, const std::shared_ptr<Project::Pin>& pin2);
    bool isPinLinked(int id);
    void drawPinIcon(std::shared_ptr<Project::Pin>& pin, bool connected, int alpha);
    ImColor getPinColor(Project::PinType type);
  };

}

#endif //BOTO_NODEEDITORPANEL_H
