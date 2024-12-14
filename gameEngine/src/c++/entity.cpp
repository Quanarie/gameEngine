#include "entity.h"
#include "component/component.h"

Entity::~Entity() {
  for (auto& pair : components) {
    delete pair.second;
  }
}
