#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component {
public:
  // Virtual destructor so that children can eventually delete any allocated resources properly
  virtual ~Component() = default;

  Entity* entity;
};

#endif // COMPONENT_H
