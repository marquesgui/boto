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
  };

}

#endif //BOTO_NODEEDITORPANEL_H
