#include "NodeEditorPanel.h"

#include "imgui/imgui.h"
namespace Boto::Gui {
  void NodeEditorPanel::Draw() {
    ne::SetCurrentEditor(m_editor);
    if (ImGui::Begin("Node Editor", nullptr)) {
      ne::Begin("NE", ImVec2(0.0f, 0.0f));
      ne::End();
    }
    ImGui::End();
  }

  void NodeEditorPanel::OnAdded() {
    ne::Config config;
    m_editor = ne::CreateEditor(&config);
  }
}