#include "NodeEditorPanel.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "nodes/PinIcon.h"

namespace Boto::Gui {
  void NodeEditorPanel::Draw() {
    ne::SetCurrentEditor(m_editor);
    if (ImGui::Begin("Node Editor Panel", nullptr)) {
      ne::Begin("ne", ImVec2(0.0f, 0.0f));
      for (auto& node : m_flow->GetNodes()) {
        //Header
        ne::BeginNode(node->Id);
          ImGui::BeginVertical("node");
            ImGui::BeginHorizontal("header");
              ImGui::Spring(0, 50.0f);
              ImGui::TextUnformatted(node->Name.c_str());
              ImGui::Spring(0, 50.0f);
              ImGui::Dummy(ImVec2(0, 28));
            ImGui::EndHorizontal();
            ImGui::Spring(0, ImGui::GetStyle().ItemSpacing.y * 2.0f);

            ImGui::BeginHorizontal("content");
              //Inputs

              if(!node->Inputs.empty()) {
                for (auto& input: node->Inputs) {
                  auto alpha = ImGui::GetStyle().Alpha;
                  if (m_newLinkPin && !canCreateLink(m_newLinkPin, input) && input != m_newLinkPin) {
                    alpha = alpha * (48.0f / 255.0f);
                  }
                  ImGui::BeginVertical("inputs", ImVec2(0.0f, 0.0f), 0.0f);
                    ne::PushStyleVar(ne::StyleVar_PivotAlignment, ImVec2(0, 0.5f));
                    ne::PushStyleVar(ne::StyleVar_PivotSize, ImVec2(0, 0));
                    ne::BeginPin(input->Id, ne::PinKind::Input);
                      ImGui::BeginHorizontal(&input->Id);
                        drawPinIcon(input, isPinLinked(input->Id), (int) (alpha * 255));
                        ImGui::Spring(0);
                        ImGui::TextUnformatted(input->Name.c_str());
                      ImGui::EndHorizontal();
                    ne::EndPin();
                    ne::PopStyleVar(2);
                  ImGui::EndVertical();
                }
              } else {
                ImGui::Spring(1);
              }

              if(!node->Outputs.empty()) {
                for (auto& output: node->Outputs) {
                  auto alpha = ImGui::GetStyle().Alpha;
                  if (m_newLinkPin && !canCreateLink(m_newLinkPin, output) && output != m_newLinkPin) {
                    alpha = alpha * (48.0f / 255.0f);
                  }
                  ImGui::BeginVertical("outputs", ImVec2(0.0f, 0.0f), 0.0f);
                    ne::PushStyleVar(ne::StyleVar_PivotAlignment, ImVec2(0, 0.5f));
                    ne::PushStyleVar(ne::StyleVar_PivotSize, ImVec2(0,0));
                    ne::BeginPin(output->Id, ne::PinKind::Output);
                      ImGui::BeginHorizontal(&output->Id);
                        ImGui::TextUnformatted(output->Name.c_str());
//                        ImGui::Spring(0);
                        drawPinIcon(output, isPinLinked(output->Id), (int) alpha * 255);
                      ImGui::EndHorizontal();
                    ne::EndPin();
                    ne::PopStyleVar(2);
                  ImGui::EndVertical();
                }
              } else {
                ImGui::Spring(1);
              }
            ImGui::EndHorizontal();
          ImGui::EndVertical();
        ne::EndNode();
      }
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

  bool NodeEditorPanel::canCreateLink(const std::shared_ptr<Project::Pin>& pin1, const std::shared_ptr<Project::Pin>& pin2) {
    if(!pin1 || !pin2 || pin1 == pin2 || pin1->Kind == pin2->Kind || pin1->Type != pin2->Type || pin1->Node == pin2->Node) {
      return false;
    }
    return true;
  }

  bool NodeEditorPanel::isPinLinked(int id) {
    for (auto& link : m_flow->GetLinks()) {
      if(link->StartPinId == id || link->EndPinId == id) {
        return true;
      }
    }
    return false;
  }

  void NodeEditorPanel::drawPinIcon(std::shared_ptr<Project::Pin>& pin, bool connected, int alpha) {
    Node::IconType iconType;
    ImColor color = getPinColor(pin->Type);
    color.Value.w = (float)alpha / 255.0f;

    switch (pin->Type) {
      case Project::PinType::Flow:
        iconType = Node::IconType::Flow;
        break;
      case Project::PinType::Bool:
      case Project::PinType::Int:
      case Project::PinType::Float:
      case Project::PinType::String:
      case Project::PinType::Object:
      case Project::PinType::Function:
        iconType = Node::IconType::Circle;
        break;
      case Project::PinType::Delegate:
        iconType = Node::IconType::Square;
        break;
      default:
        return;
    }

    ImVec2 size = ImVec2(m_pinIconSize, m_pinIconSize);
    if(ImGui::IsRectVisible(size)){
      auto cursorPos = ImGui::GetCursorScreenPos();
      auto drawList = ImGui::GetWindowDrawList();
      auto cursorEndPos = ImVec2(cursorPos.x + m_pinIconSize, cursorPos.y + m_pinIconSize);
      Gui::Node::PinIcon::Draw(drawList, cursorPos, cursorEndPos, iconType, connected, color, ImColor(32, 32, 32, alpha));
    }

    ImGui::Dummy(size);
  }

  ImColor NodeEditorPanel::getPinColor(Project::PinType type) {
    switch (type) {
      default:
      case Project::PinType::Flow: return {255, 255, 255};
      case Project::PinType::Bool: return {220, 48, 48};
      case Project::PinType::Int: return {68, 201, 156};
      case Project::PinType::Float: return {147,226,74};
      case Project::PinType::String: return {125, 21, 153};
      case Project::PinType::Object: return {51, 150, 215};
      case Project::PinType::Function: return {218, 0, 183};
      case Project::PinType::Delegate: return {255, 48, 48};
    }
  }
}