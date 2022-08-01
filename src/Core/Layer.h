//
// Created by Guilherme Marques de Oliveira on 29/07/22.
//

#ifndef BOTO_LAYER_H
#define BOTO_LAYER_H

namespace Boto {
  class Layer {

  public:
    virtual ~Layer() = default;
    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;
    virtual void OnUpdate() = 0;
  };
}

#endif //BOTO_LAYER_H
