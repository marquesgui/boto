#include "IdGenerator.h"

namespace Boto::Utils::IdGenerator {
  namespace {
    int lastUsedId = 0;
  }

  int GetNextId() {
    return ++lastUsedId;
  }

  void SetCurrentId(int id) {
    lastUsedId = id;
  }
}
