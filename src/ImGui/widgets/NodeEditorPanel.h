#ifndef BOTO_NODEEDITORPANEL_H
#define BOTO_NODEEDITORPANEL_H

#include "ImGuiWidget.h"

#include <imgui-node-editor/imgui_node_editor.h>

namespace ne = ax::NodeEditor;

class NodeEditorPanel: public ImGuiWidget {

public:
  void Draw() override;
  void OnAdded() override;

private:
  ne::EditorContext* m_editor;
};

#endif //BOTO_NODEEDITORPANEL_H
