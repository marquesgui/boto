#include "Core/Application.h"
#include <memory>

#include "ImGui/ImGuiLayer.h"
#include "ImGui/widgets/MainMenuBar.h"
#include "ImGui/widgets/ContentBrowserPanel.h"
#include "ImGui/widgets/NodeEditorPanel.h"

int main() {

  //Create application
  auto application = std::make_shared<Boto::Application>();

  //Create Widgets
  auto mainMenuWidget = std::make_shared<MainMenuBar>();
  mainMenuWidget->AttachObserver(application);
  auto contentBrowserWidget = std::make_shared<ContentBrowserPanel>();
  auto nodeEditor = std::make_shared<NodeEditorPanel>();

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
