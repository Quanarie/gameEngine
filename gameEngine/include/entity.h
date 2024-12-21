#ifndef ENTITY_H
#define ENTITY_H

#include <typeindex>
#include <unordered_map>

class ColliderComponent;
class Component;

class Entity {
public:
  virtual ~Entity();

  virtual void initialize() = 0;
  virtual void update() = 0;

  virtual void onCollision(ColliderComponent* col) {}

  template <typename T, typename... Args>
  T* addComponent(Args&&... args) {
    T* component = new T(std::forward<Args>(args)...);
    component->entity = this;
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
