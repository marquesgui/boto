#ifndef BOTO_GUI_MAINMENUBAR_H
#define BOTO_GUI_MAINMENUBAR_H

#include "../../Core/Subject.h"
#include "ImGuiWidget.h"

#include <list>

namespace Boto::Gui {

  class MainMenuBar : public Subject, public Boto::Gui::ImGuiWidget {

  public: //Subject implementation
    void AttachObserver(const std::shared_ptr<Observer>& observer) override;

    void DetachObserver(Observer* observer) override;

    void NotifyObserver(Boto::Event event) override;

  public:
    void Draw() override;

  private:
    std::list<std::shared_ptr<Observer>> m_observers;
    bool isDialogFileOpen = false;
  };
}

#endif //BOTO_GUI_MAINMENUBAR_H
