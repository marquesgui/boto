#include "Application.h"
#include <memory>

Boto::Application::Application() {
  m_isRunning = true;
}

void Boto::Application::Run() {
  while (m_isRunning) {
    std::for_each(m_layers.begin(), m_layers.end(), [](const std::shared_ptr<Layer>& layer) -> void {
      layer->OnUpdate();
    });

    handleEvents();
  }
}

void Boto::Application::AddLayer(const std::shared_ptr<Layer>& layer) {
  m_layers.push_back(layer);
  layer->OnAttach();
}

void Boto::Application::onNotify(const Event& event) {
  m_events.push(event);
}

void Boto::Application::handleEvents() {
  while (!m_events.empty()) {
    Event event = m_events.top();
    m_events.pop();
    switch (event.Type) {
      case EventType::EVENT_TYPE_GUI:
        if(event.Name == "WINDOW_SHOULD_CLOSE") m_isRunning = false;
        break;
    }
  }
}

/**
 * Mocked
 */
void Boto::Application::loadSolution() {
  m_solution = std::make_shared<Project::Solution>();
}
