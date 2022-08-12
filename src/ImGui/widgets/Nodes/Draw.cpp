#include "Draw.h"
#include "PinIcon.h"
#include <imgui/imgui.h>
#include <imgui-node-editor/imgui_node_editor.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

namespace ne = ax::NodeEditor;

namespace Boto::Gui::Node {
  namespace {

    const float l_pinIconSize = 20.0f;

    ImColor getPinColor(Project::PinType type) {
      switch (type) {
        default:
        case Project::PinType::Flow:
          return {255, 255, 255};
        case Project::PinType::Bool:
          return {220, 48, 48};
        case Project::PinType::Int:
          return {68, 201, 156};
        case Project::PinType::Float:
          return {147, 226, 74};
        case Project::PinType::String:
          return {125, 21, 153};
        case Project::PinType::Object:
          return {51, 150, 215};
        case Project::PinType::Function:
          return {218, 0, 183};
        case Project::PinType::Delegate:
          return {255, 48, 48};
        case Project::PinType::Event:
          return {240, 43, 89};
      }
    }

    void drawPinIcon(std::shared_ptr<Project::Pin>& pin, bool connected, int alpha) {
      Node::IconType iconType;
      ImColor color = getPinColor(pin->Type);
      color.Value.w = (float) alpha / 255.0f;

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
        case Project::PinType::Event:
        case Project::PinType::Delegate:
          iconType = Node::IconType::Square;
          break;
        default:
          return;
      }

      ImVec2 size = ImVec2(l_pinIconSize, l_pinIconSize);
      if (ImGui::IsRectVisible(size)) {
        auto cursorPos = ImGui::GetCursorScreenPos();
        auto drawList = ImGui::GetWindowDrawList();
        auto cursorEndPos = ImVec2(cursorPos.x + l_pinIconSize, cursorPos.y + l_pinIconSize);
        Gui::Node::PinIcon::Draw(drawList, cursorPos, cursorEndPos, iconType, connected, color,
                                 ImColor(32, 32, 32, alpha));
      }

      ImGui::Dummy(size);
    }

    bool isPinLinked(int id, const std::list<std::shared_ptr<pj::Link>>& links) {
      for (auto& link : links) {
        if(link->StartPinId == id || link->EndPinId == id) {
          return true;
        }
      }
      return false;
    }

    void drawDefaultNode(const std::shared_ptr<pj::Node>& node, const std::list<std::shared_ptr<pj::Link>>& links) {
      ImGui::PushID(&node->Id);

      ne::BeginNode(node->Id);
        ImGui::BeginVertical("node");

          //Header
          ImGui::BeginHorizontal("Header");
            ImGui::Spring(0, 10.0f);
            ImGui::TextUnformatted(node->Name.c_str());
            ImGui::Spring(0);
          ImGui::EndHorizontal();

          //Spacing between header and content
          ImGui::Dummy(ImVec2(0, 28));

          //Content
          ImGui::BeginHorizontal("Content");

            ImGui::BeginVertical("Inputs");
              for (auto& input: node->Inputs) {
                ne::PushStyleVar(ne::StyleVar_PivotAlignment, ImVec2(0, 0.5f));
                ne::BeginPin(input->Id, ne::PinKind::Input);
                  ImGui::BeginHorizontal(&input->Id);
                    drawPinIcon(input, isPinLinked(input->Id, links), 255);
                    ImGui::Spring(0);
                    ImGui::TextUnformatted(input->Name.c_str());
                    ImGui::Spring(0);
                 ImGui::EndHorizontal();
                ne::EndPin();
                ne::PopStyleVar();
              }
            ImGui::EndVertical();

            ImGui::Spring(0);

            ImGui::BeginVertical("Outputs");
              for (auto& output : node->Outputs) {
                ne::BeginPin(output->Id, ne::PinKind::Output);
                  ImGui::BeginHorizontal(&output->Id);
                    ImGui::TextUnformatted(output->Name.c_str());
                    ImGui::Spring(0);
                    drawPinIcon(output, isPinLinked(output->Id, links), 255);
                    ImGui::Spring(0);
                ImGui::EndHorizontal();
                ne::EndPin();
              }
            ImGui::EndVertical();
          ImGui::EndHorizontal();

        ImGui::EndVertical();
      ne::EndNode();

      ImGui::PopID();
    }
  }

  void drawStringNode(const std::shared_ptr<pj::Node>& node, const std::list<std::shared_ptr<pj::Link>>& links) {
    auto stringNode = std::dynamic_pointer_cast<Project::StringNode>(node);
    ImGui::PushID(&node->Id);

      ne::BeginNode(node->Id);
        ImGui::BeginVertical("Node");

          //Header
          ImGui::BeginHorizontal("Header");
            ImGui::Spring(0, 10.0f);
            ImGui::TextUnformatted(node->Name.c_str());
            ImGui::Spring(0, 50.0f);
          ImGui::EndHorizontal();

          //Spacing between header and content
          ImGui::Dummy(ImVec2(0, 28));

          //Content
          ImGui::BeginHorizontal("Content");
            ImGui::Spring(1);
            ImGui::PushItemWidth(100.0f);
            ImGui::InputText("", &stringNode->Value, ImGuiInputTextFlags_AlwaysOverwrite);
            ImGui::PopItemWidth();
            ImGui::Spring(0);
            ne::PushStyleVar(ne::StyleVar_PivotAlignment, ImVec2(1, 0.5f));
            ne::BeginPin(node->Outputs.back()->Id, ne::PinKind::Output);
              ImGui::TextUnformatted(node->Outputs.back()->Name.c_str());
              drawPinIcon(node->Outputs.back(), isPinLinked(node->Outputs.back()->Id, links), 255);
            ne::EndPin();
            ne::PopStyleVar();
          ImGui::EndHorizontal();

        ImGui::EndVertical();
      ne::EndNode();

    ImGui::PopID();
  }

  void DrawNode(const std::shared_ptr<pj::Node>& node, const std::list<std::shared_ptr<pj::Link>>& links) {
    switch (node->GetType()) {
      case Project::NodeType::Default:
        drawDefaultNode(node, links);
        break;
      case Project::NodeType::String:
        drawStringNode(node, links);
        break;
    }
  }
}