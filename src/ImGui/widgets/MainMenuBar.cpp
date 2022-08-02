#include "MainMenuBar.h"
#include <imgui/imgui.h>
#include <ImGuiFileDialog/ImGuiFileDialog.h>

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
      if (ImGui::MenuItem("Open...")) {
        isDialogFileOpen = true;
      }
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

  if(isDialogFileOpen) {
    ImGuiFileDialogFlags flags = ImGuiFileDialogFlags_Modal;
    ImGuiFileDialog::Instance()->OpenDialog("OpenFileDialog", "Chose a folder", nullptr, ".", 1, nullptr, flags);
    if (ImGuiFileDialog::Instance()->Display("OpenFileDialog")) {
      ImGuiFileDialog::Instance()->Close();
      isDialogFileOpen = false;
    }
  }
}