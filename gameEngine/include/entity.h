#ifndef ENTITY_H
#define ENTITY_H

#include "component/component.h"
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>

class Entity {
public:
  virtual ~Entity() = default;

  virtual void initialize() = 0;
  virtual void update() = 0;

  template <typename T, typename... Args> T *addComponent(Args &&...args) {
    T *component = new T(std::forward<Args>(args)...);
    components[typeid(T)] = std::unique_ptr<Component>(component);
    return component;
  }

  template <typename T> T *getComponent() {
    auto it = components.find(typeid(T));
    return (it != components.end()) ? dynamic_cast<T *>(it->second.get())
                                    : nullptr;
  }

protected:
  std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};

#endif // ENTITY_H
