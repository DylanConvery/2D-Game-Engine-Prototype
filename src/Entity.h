#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

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

    std::string entity_name;

   private:
    EntityManager& manager;
    std::vector<Component*> components;
    bool active;
};

#endif  // !ENTITY_H
