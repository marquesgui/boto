#ifndef BOTO_GUI_IMGUIWIDGET_H
#define BOTO_GUI_IMGUIWIDGET_H

namespace Boto::Gui {
  class ImGuiWidget {
  public:
    virtual ~ImGuiWidget() = default;

    virtual void Draw() = 0;
    virtual void OnAdded() {};
  };
}
#endif //BOTO_GUI_IMGUIWIDGET_H
