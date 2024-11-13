#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
    virtual ~Entity() = default;

    virtual void initialize() = 0;
    virtual void update() = 0;
};

#endif // ENTITY_H
