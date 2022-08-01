#ifndef BOTO_IMGUILAYER_H
#define BOTO_IMGUILAYER_H

#include "../Core/Layer.h"
#include "../Core/Subject.h"

#include <memory>
#include <list>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

namespace Boto::Gui {

  class ImGuiLayer : public Layer, public Subject{
  public:
    ImGuiLayer() = default;
    ~ImGuiLayer() override;

  public: //Subject implementation
    void AttachObserver(const std::shared_ptr<Observer>& observer) override;
    void DetachObserver(Observer* observer) override;
    void NotifyObserver(Boto::Event event) override;

  public: //Layer implementation
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;

  private:
    std::list<std::shared_ptr<Observer>> m_observers;
    std::string m_GLS_Version;
    GLFWwindow* m_Window;
    float m_Clear_Color[4] = {0.45f, 0.55f, 0.60f, 1.00f};

  private:
    void createWindowContext();
    void createDearImGuiContext();
    void begin();
    void end();
  };
}
#endif //BOTO_IMGUILAYER_H