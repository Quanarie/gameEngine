#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>

#include "component/component.h"

class Entity {
public:
  virtual ~Entity() = default;

  virtual void initialize() = 0;
  virtual void update() = 0;

  template <typename T, typename... Args> T *addComponent(Args &&...args) {
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    T *componentPtr = component.get();
    components[typeid(T)] = std::move(component);
    return componentPtr;
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
