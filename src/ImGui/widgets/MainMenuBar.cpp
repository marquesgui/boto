#include "MainMenuBar.h"
#include "../../../vendor/imgui/imgui.h"

void MainMenuBar::AttachObserver(const std::shared_ptr<Observer>& observer) {
  m_observers.push_back(observer);
}

void MainMenuBar::DetachObserver(Observer* observer) {
}

void MainMenuBar::NotifyObserver(Boto::Event event) {
  std::for_each(m_observers.begin(), m_observers.end(), [=](const std::shared_ptr<Observer>& observer){
    observer->onNotify(event);
  });
}

void MainMenuBar::Draw() {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::BeginMenu("New")) {
        if (ImGui::MenuItem("Project")) {}
        ImGui::EndMenu();
      }
      if (ImGui::MenuItem("Open...")) {}
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit")) {
      if (ImGui::MenuItem("Undo")) {}
      ImGui::Separator();
      if (ImGui::MenuItem("Cut")) {}
      if (ImGui::MenuItem("Copy")) {}
      if (ImGui::MenuItem("Paste")) {}
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}
