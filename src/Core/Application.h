#ifndef BOTO_APPLICATION_H
#define BOTO_APPLICATION_H

#include "Subject.h"
#include "Layer.h"
#include "../Project/Solution.h"

#include <list>
#include <stack>

namespace Boto{
  class Application: public Observer{
  public:
    Application();
    Application(const Application& other) = delete;
    ~Application() override = default;
    void AddLayer(const std::shared_ptr<Layer>& layer);
    void onNotify(const Event& event) override;

    void Run();

  public:
    void operator = (const Application& app) = delete;

  private:
    bool m_isRunning;
    std::list<std::shared_ptr<Layer>> m_layers; std::stack<Event> m_events;
    std::shared_ptr<Boto::Project::Solution> m_solution;

  private:
    void handleEvents();
    void loadSolution();
  };

}

#endif //BOTO_APPLICATION_H
