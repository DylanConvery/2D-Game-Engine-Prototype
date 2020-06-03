#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <iostream>
#include <vector>

#include "./Entity.hpp"

class EntityManager {
   public:
    void update(float delta_time);
    void render();
    bool empty();
    Entity& addEntity(std::string entity_name);
    void listEntities() const;
    std::vector<Entity*> getEntities() const;
    unsigned int size() const;
    void clear();

   private:
    std::vector<Entity*> _entities;
};

#endif  // !ENTITYMANAGER_H