#include "Core/Application.h"
#include <memory>

#include "ImGui/ImGuiLayer.h"
#include "ImGui/widgets/MainMenuBar.h"

int main() {

  //Create application
  auto application = std::make_shared<Boto::Application>();

  //Create Widgets
  auto mainMenuWidget = std::make_shared<MainMenuBar>();
  mainMenuWidget->AttachObserver(application);

  //Setup ImGui Layer
  auto imguiLayer = std::make_shared<Boto::Gui::ImGuiLayer>();
  imguiLayer->AddWidget(mainMenuWidget);
  imguiLayer->AttachObserver(application);

  //Configure application
  application->AddLayer(imguiLayer);

  //Run
  application->Run();
}
