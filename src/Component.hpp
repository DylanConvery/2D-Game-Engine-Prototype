#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

//abstract class used to describe what a component must do
class Component {
   public:
    virtual ~Component() {}
    virtual void initialize() {}
    virtual void update(float delta_time) {}
    virtual void render() {}

    Entity* _entity;
};

#endif  // !COMPONENT_H