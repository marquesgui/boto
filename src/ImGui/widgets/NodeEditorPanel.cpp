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
      auto cursorTopLeft = ImGui::GetCursorScreenPos();

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
              ne::Suspend();
              ImGui::OpenPopup("Create New Node");
              ne::Resume();
            }
          }

        } else {
          m_newLinkPin = nullptr;
        }

        ne::EndCreate();

        if (ne::BeginDelete()) {
          ne::LinkId linkId = 0;
          while (ne::QueryDeletedLink(&linkId)) {
            if(ne::AcceptDeletedItem()) {
              auto id = std::find_if(m_flow->GetLinks().begin(), m_flow->GetLinks().end(), [linkId](auto& link) -> bool {
                return link->Id == linkId.Get();
              });
              if( id != m_flow->GetLinks().end()) {
                m_flow->GetLinks().erase(id);
              }
            }
          }

          ne::NodeId nodeId = 0;
          while (ne::QueryDeletedNode(&nodeId)) {
            if(ne::AcceptDeletedItem()) {
              auto id = std::find_if(m_flow->GetNodes().begin(), m_flow->GetNodes().end(), [nodeId](auto& node) -> bool {
                return node->Id == nodeId.Get();
              });
              if(id != m_flow->GetNodes().end()) {
                m_flow->GetNodes().erase(id);
              }
            }
          }
        }
        ne::EndDelete();
      }

      ImGui::SetCursorScreenPos(cursorTopLeft);

      //Popup menus
      auto openPopupPosition = ImGui::GetMousePos();

      ne::Suspend();
      static ne::NodeId contextNodeId = 0;
      static ne::PinId contextPinId = 0;
      static ne::LinkId contextLinkId = 0;
      if(ne::ShowNodeContextMenu(&contextNodeId)) {
        ImGui::OpenPopup("Node Context Menu");
      } else if (ne::ShowPinContextMenu(&contextPinId)) {
        ImGui::OpenPopup("Pin Context Menu");
      } else if (ne::ShowLinkContextMenu(&contextLinkId)) {
        ImGui::OpenPopup("Link Context Menu");
      } else if (ne::ShowBackgroundContextMenu()) {
        ImGui::OpenPopup("Create New Node");
        m_newNodeLinkPin = nullptr;
      }
      ne::Resume();

      //Node Context Menu
      ne::Suspend();
      ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8,8));
      if(ImGui::BeginPopup("Node Context Menu")) {
        auto node = findNode(contextNodeId);

        ImGui::TextUnformatted("Node Menu");
        ImGui::Separator();
        if(node) {
          ImGui::Text("ID: %d", node->Id);
          ImGui::Text("Inputs: %d", (int)node->Inputs.size());
          ImGui::Text("Outputs: %d", (int)node->Outputs.size());
        } else {
          ImGui::Text("Unknown node: %p", contextNodeId.AsPointer());
        }
        ImGui::Separator();
        if(ImGui::MenuItem("Delete")) {
          ne::DeleteNode(contextNodeId);
        }
        ImGui::EndPopup();
      }

      //Pin Context Menu
      if(ImGui::BeginPopup("Pin Context Menu")) {
        auto pin = findPin(contextPinId);

        ImGui::TextUnformatted("Pin Menu");
        ImGui::Separator();
        if(pin) {
          ImGui::Text("ID: %d", pin->Id);
          ImGui::Text("Type: %s", Project::PinTypeAsString(pin->Type).c_str());
          if(pin->Node) {
            ImGui::Text("Node: %d", pin->Node->Id);
          } else {
            ImGui::Text("Node: %s", "<none>");
          }
        } else {
          ImGui::Text("Unknown pin: %p", contextPinId.AsPointer());
        }
        ImGui::EndPopup();
      }

      //Link Context Menu
      if (ImGui::BeginPopup("Link Context Menu"))
      {
        auto link = findLink(contextLinkId);

        ImGui::TextUnformatted("Link Menu");
        ImGui::Separator();
        if (link)
        {
          ImGui::Text("ID: %p", &link->Id);
          ImGui::Text("From: %d", link->StartPinId);
          ImGui::Text("To: %d", link->EndPinId);
        }
        else
          ImGui::Text("Unknown link: %p", contextLinkId.AsPointer());
        ImGui::Separator();
        if (ImGui::MenuItem("Delete"))
          ne::DeleteLink(contextLinkId);
        ImGui::EndPopup();
      }

      //Create New Node Context Menu
      if(ImGui::BeginPopup("Create New Node")) {
        auto newNodePosition = openPopupPosition;

        std::shared_ptr<Project::Node> node = nullptr;
        if(ImGui::BeginMenu("Variables")) {
          if(ImGui::MenuItem("String")) {
            node = std::make_shared<Project::StringNode>(Utils::IdGenerator::GetNextId());
          }
          ImGui::EndMenu();
        }
        ImGui::Separator();
        if(ImGui::BeginMenu("Events")) {
          if(ImGui::MenuItem("HttpRequestEvent")) {
            node = std::make_shared<Project::HttpRequestEventNode>(Utils::IdGenerator::GetNextId());
          }
          ImGui::EndMenu();
        }
        ImGui::Separator();
        if(ImGui::BeginMenu("Handlers")) {
          if(ImGui::MenuItem("HttpController")) {
            node = std::make_shared<Project::HttpController>(Utils::IdGenerator::GetNextId());
          }
          ImGui::EndMenu();
        }

        if(node) {
          m_isCreatingNewNode = false;
          m_flow->GetNodes().push_back(node);

          ne::SetNodePosition(node->Id, newNodePosition);
          if(auto startPin = m_newNodeLinkPin) {
            auto& pins = startPin->Kind == Project::PinKind::Input ? node->Outputs : node->Inputs;
            for (auto& pin: pins) {
              if(canCreateLink(startPin, pin)) {
                auto endPin = pin;
                if(startPin->Kind == Project::PinKind::Input) {
                  std::swap(startPin, endPin);
                }

                m_flow->GetLinks().emplace_back(std::make_shared<Project::Link>(Utils::IdGenerator::GetNextId(), startPin->Id, endPin->Id));
                break;
              }
            }
          }
        }

        ImGui::EndPopup();
      } else {
        m_isCreatingNewNode = false;
      }
      ImGui::PopStyleVar();
      ne::Resume();
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

  std::shared_ptr<Project::Node> NodeEditorPanel::findNode(const ne::NodeId& id) {
    for (auto& node : m_flow->GetNodes()) {
      if(node->Id == id.Get()) {
        return node;
      }
    }
    return nullptr;
  }

  std::shared_ptr<Project::Link> NodeEditorPanel::findLink(const ne::LinkId& id) {
    for (auto& link : m_flow->GetLinks()) {
      if(link->Id == id.Get()) {
        return link;
      }
    }
    return nullptr;
  }
}