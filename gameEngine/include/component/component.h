#ifndef COMPONENT_H
#define COMPONENT_H

#include "initializable.h"

class Entity;

class Component : public Initializable {
public:
  void initialize() override {}
  // Virtual destructor so that children can eventually delete any allocated resources properly
  virtual ~Component() = default;

  Entity* entity;
};

#endif // COMPONENT_H
