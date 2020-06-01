#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

#include "EntityManager.hpp"
#include "Component.hpp"

class EntityManager;
class Component;

class Entity {
   public:
    Entity(EntityManager& manager);
    Entity(EntityManager& manager, std::string entity_name);
    void update(float delta_time);
    void render();
    void destroy();
    bool active() const;

    std::string _entity_name;

   private:
    EntityManager& _manager;
    std::vector<Component*> _components;
    bool _active;
};

#endif  // !ENTITY_H
