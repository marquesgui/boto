#include "NodeEditorPanel.h"

#include "imgui/imgui.h"
namespace Boto::Gui {
  void NodeEditorPanel::Draw() {
    ne::SetCurrentEditor(m_editor);
    if (ImGui::Begin("Node Editor", nullptr)) {
      ne::Begin("NE", ImVec2(0.0f, 0.0f));

      std::for_each(m_flow->GetNodes().begin(), m_flow->GetNodes().end(), [](const std::shared_ptr<Project::Node>& node)->void{

        ne::BeginNode(node->Id);
        ImGui::BeginVertical("node");
        ImGui::BeginHorizontal("header");
        ImGui::Spring(0);
        ne::PushStyleVar(ne::StyleVar_NodePadding, ImVec4(8,4,8,8));
        ImGui::TextUnformatted(node->Name.c_str());
        ImGui::Spring(0);
//        ImGui::PushID(node->Id);
        ImGui::EndHorizontal();
        ImGui::EndVertical();
        ne::EndNode();
      });

      ne::End();
    }
    ImGui::End();
  }

  void NodeEditorPanel::OnAdded() {
    ne::Config config;
    m_editor = ne::CreateEditor(&config);
  }

  void NodeEditorPanel::SetFlow(const std::shared_ptr<Project::Flow>& flow) {
    m_flow = flow;
  }
}