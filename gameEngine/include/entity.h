#ifndef ENTITY_H
#define ENTITY_H

#include <typeindex>
#include <unordered_map>

#include "component/component.h"

class Entity {
public:
  virtual ~Entity() {
    for (auto& pair : components) {
      delete pair.second;
    }
  }

  virtual void initialize() = 0;
  virtual void update() = 0;

  template <typename T, typename... Args>
  T* addComponent(Args&&... args) {
    T* component = new T(std::forward<Args>(args)...);
    components[typeid(T)] = static_cast<Component*>(component);
    return component;
  }

  // TODO: For now only one component of a type
  template <typename T>
  T* getComponent() {
    for (const auto& pair : components) {
      if (auto component = dynamic_cast<T*>(pair.second)) {
        return component;
      }
    }
    return nullptr;
  }

protected:
  std::unordered_map<std::type_index, Component*> components;
};

#endif // ENTITY_H
