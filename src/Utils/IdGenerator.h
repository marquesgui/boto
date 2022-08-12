#ifndef BOTO_IDGENERATOR_H
#define BOTO_IDGENERATOR_H

namespace Boto::Utils::IdGenerator {
  int GetNextId();
  void SetCurrentId(int currentId);
}
#endif //BOTO_IDGENERATOR_H
