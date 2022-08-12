#include "NodeEditorPanel.h"
#include "Nodes/Draw.h"
#include "../../Utils/IdGenerator.h"

#define IMGUI_DEFINE_MATH_OPERATORS

#include <imgui/imgui_internal.h>

namespace Boto::Gui {
  void NodeEditorPanel::Draw() {
    ne::SetCurrentEditor(m_editor);
    if (ImGui::Begin("Node Editor Panel", nullptr)) {
      ne::Begin("ne", ImVec2(0.0f, 0.0f));
      for (auto& node: m_flow->GetNodes()) {
        Node::DrawNode(node, m_flow->GetLinks());
      }
      for (auto& link: m_flow->GetLinks()) {
        ne::Link(link->Id, link->StartPinId, link->EndPinId, ImVec4(1, 1, 1, 1), 2.0f);
      }

      if (!m_isCreatingNewNode) {
        if (ne::BeginCreate(ImColor(255, 255, 255), 2.0f)) {
          auto showLabel = [](const char* label, ImColor color) {
            ImGui::SetCursorPosY(ImGui::GetCursorPos().y - ImGui::GetTextLineHeight());
            auto size = ImGui::CalcTextSize(label);

            auto padding = ImGui::GetStyle().FramePadding;
            auto spacing = ImGui::GetStyle().ItemSpacing;

            ImGui::SetCursorPos(ImGui::GetCursorPos() + ImVec2(spacing.x, -spacing.y));

            auto rectMin = ImGui::GetCursorScreenPos() - padding;
            auto rectMax = ImGui::GetCursorScreenPos() + size + padding;

            auto drawList = ImGui::GetWindowDrawList();
            drawList->AddRectFilled(rectMin, rectMax, color, size.y * 0.15f);
            ImGui::TextUnformatted(label);
          };

          ne::PinId starPinId = 0, endPinId = 0;
          if (ne::QueryNewLink(&starPinId, &endPinId)) {
            auto startPin = findPin(starPinId);
            auto endPin = findPin(endPinId);

            m_newLinkPin = startPin ? startPin : endPin;

            if (startPin->Kind == Project::PinKind::Input) {
              std::swap(startPin, endPin);
              std::swap(starPinId, endPinId);
            }

            if (startPin && endPin) {
              if (endPin == startPin) {
                ne::RejectNewItem(ImColor(255, 0, 0), 2.0f);
              } else if (endPin->Kind == startPin->Kind) {
                showLabel("Both are output, genius", ImColor(45, 32, 32, 180));
                ne::RejectNewItem(ImColor(255, 0, 0), 2.0f);
              } else if (endPin->Type != startPin->Type) {
                showLabel("Really? Different types? Really?", ImColor(45, 32, 32, 180));
                ne::RejectNewItem(ImColor(255, 128, 128), 2.0f);
              } else {
                showLabel("+ Create Link", ImColor(32, 45, 32, 180));
                if (ne::AcceptNewItem(ImColor(128, 255, 128), 4.0f)) {
                  m_flow->GetLinks().emplace_back(std::make_shared<pj::Link>(Utils::IdGenerator::GetNextId(), startPin->Id, endPin->Id));
                }
              }
            }
          }

          ne::PinId pinId = 0;
          if (ne::QueryNewNode(&pinId)) {
            m_newLinkPin = findPin(pinId);
            if(m_newLinkPin) {
              showLabel("+ Create Node", ImColor(32, 45, 32, 180));
            }

            if(ne::AcceptNewItem()) {
              m_isCreatingNewNode = true;
              m_newNodeLinkPin = findPin(pinId);
              m_newLinkPin = nullptr;
//              ne::Suspend();
//              ImGui::OpenPopup("Create New Node");
//              ne::Resume();
            }
          }

        } else {
          m_newLinkPin = nullptr;
        }

        ne::EndCreate();
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

  bool
  NodeEditorPanel::canCreateLink(const std::shared_ptr<Project::Pin>& pin1, const std::shared_ptr<Project::Pin>& pin2) {
    if (!pin1 || !pin2 || pin1 == pin2 || pin1->Kind == pin2->Kind || pin1->Type != pin2->Type ||
        pin1->Node == pin2->Node) {
      return false;
    }
    return true;
  }

  std::shared_ptr<Project::Pin> NodeEditorPanel::findPin(ne::PinId id) {
    if (!id)
      return nullptr;

    for (auto& node: m_flow->GetNodes()) {
      for (auto& pin: node->Inputs) {
        if (pin->Id == id.Get()) {
          return pin;
        }
      }

      for (auto& pin: node->Outputs) {
        if (pin->Id == id.Get()) {
          return pin;
        }
      }
    }

    return nullptr;
  }
}