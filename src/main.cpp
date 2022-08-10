#include "Core/Application.h"
#include <memory>

#include "ImGui/ImGuiLayer.h"
#include "ImGui/widgets/MainMenuBar.h"
#include "ImGui/widgets/ContentBrowserPanel.h"
#include "ImGui/widgets/NodeEditorPanel.h"

#include "Project/Flow.h"

int main() {

  //Create application
  auto application = std::make_shared<Boto::Application>();

  //Create Widgets
  auto mainMenuWidget = std::make_shared<Boto::Gui::MainMenuBar>();
  mainMenuWidget->AttachObserver(application);
  auto contentBrowserWidget = std::make_shared<Boto::Gui::ContentBrowserPanel>();
  auto nodeEditor = std::make_shared<Boto::Gui::NodeEditorPanel>();

  //Mock (setup node editor)
  nodeEditor->SetFlow(std::make_shared<Boto::Project::Flow>());

  //Setup ImGui Layer
  auto imguiLayer = std::make_shared<Boto::Gui::ImGuiLayer>();
  imguiLayer->AddWidget(mainMenuWidget);
  imguiLayer->AddWidget(contentBrowserWidget);
  imguiLayer->AddWidget(nodeEditor);

  imguiLayer->AttachObserver(application);

  //Configure application
  application->AddLayer(imguiLayer);

  //Run
  application->Run();
}