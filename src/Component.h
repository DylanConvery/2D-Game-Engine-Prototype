#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component {
   public:
    virtual ~Component() {}
    virtual void initialize() {}
    virtual void update(float delta_time) {}
    virtual void render() {}

    Entity* owner;
};

#endif  // !COMPONENT_H