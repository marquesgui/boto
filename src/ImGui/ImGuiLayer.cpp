#include "ImGuiLayer.h"
#include "../../vendor/imgui/backends/imgui_impl_glfw.h"
#include "../../vendor/imgui/backends/imgui_impl_opengl3.h"

#include <cstdio>

namespace Boto::Gui {
  ImGuiLayer::~ImGuiLayer() {
    m_observers.clear();
    m_widgets.clear();
  }

  void ImGuiLayer::AddWidget(const std::shared_ptr<ImGuiWidget>& widget) {
    widget->OnAdded();
    m_widgets.push_back(widget);
  }

  void ImGuiLayer::AttachObserver(const std::shared_ptr<Observer>& observer) {
    m_observers.push_back(observer);
  }

  void ImGuiLayer::DetachObserver(Observer* observer) {

  }

  void ImGuiLayer::NotifyObserver(Boto::Event event) {
    std::for_each(m_observers.begin(), m_observers.end(), [=](const std::shared_ptr<Observer>& observer) {
      observer->onNotify(event);
    });
  }

  void ImGuiLayer::OnAttach() {
    createWindowContext();
    createDearImGuiContext();
  }

  void ImGuiLayer::OnDetach() {
  }

  void ImGuiLayer::OnUpdate() {
    begin();
    drawWidgets();
    end();

    if (glfwWindowShouldClose(m_Window)) {
      NotifyObserver({"WINDOW_SHOULD_CLOSE", EventType::EVENT_TYPE_GUI});
    }
  }

  void ImGuiLayer::createWindowContext() {
    glfwSetErrorCallback([](int error, const char* description) -> void {
      fprintf(stderr, "Glfq Error %d: %s", error, description);
    });
    if (!glfwInit()) {
      EXIT_FAILURE;
    }

#if __APPLE__
    m_GLS_Version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
#endif

    m_Window = glfwCreateWindow(1280, 720, "__Boto__", nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
      fprintf(stderr, "Failed to initialize OpenGL loader\n");
      throw;
    }

    int screeWidth, screenHeight;
    glfwGetFramebufferSize(m_Window, &screeWidth, &screenHeight);
    glViewport(0, 0, screeWidth, screenHeight);
  }

  void ImGuiLayer::createDearImGuiContext() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ::ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;

    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init(m_GLS_Version.c_str());

    ImGui::StyleColorsDark();

//    ne::Config config;
//    m_Editor = ne::CreateEditor(&config)
  }

  void ImGuiLayer::begin() {
#if __APPLE__
    glfwWaitEventsTimeout(0.1);
#else
    glfwPollEvents();
#endif

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
  }

  void ImGuiLayer::end() {
    ImGui::Render();

    int display_w, display_h;
    glfwGetFramebufferSize(m_Window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(m_Clear_Color[0], m_Clear_Color[1], m_Clear_Color[2], m_Clear_Color[3]);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);

    glfwSwapBuffers(m_Window);
  }

  void ImGuiLayer::drawWidgets() {
    std::for_each(m_widgets.begin(), m_widgets.end(), [](const std::shared_ptr<ImGuiWidget>& widget){
      widget->Draw();
    });
  }
}