#include "Core/Application.h"
#include <memory>

#include "ImGui/ImGuiLayer.h"

int main() {

  //Create application
  auto application = std::make_shared<Boto::Application>();

  //Setup ImGui Layer
  auto imguiLayer = std::make_shared<Boto::Gui::ImGuiLayer>();
  imguiLayer->AttachObserver(application);
  application->AddLayer(imguiLayer);

  //Run
  application->Run();
}
