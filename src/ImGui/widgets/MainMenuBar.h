#ifndef BOTO_MAINMENUBAR_H
#define BOTO_MAINMENUBAR_H

#include "../../Core/Subject.h"
#include "ImGuiWidget.h"

#include <list>

class MainMenuBar: public Subject, public ImGuiWidget{

public: //Subject implementation
  void AttachObserver(const std::shared_ptr<Observer>& observer) override;
  void DetachObserver(Observer* observer) override;
  void NotifyObserver(Boto::Event event) override;

public:
 void Draw() override;

private:
  std::list<std::shared_ptr<Observer>> m_observers;
};


#endif //BOTO_MAINMENUBAR_H
