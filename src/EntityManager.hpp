#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <iostream>
#include <vector>

#include "Entity.hpp"
#include "Component.hpp"
#include "Collision.hpp"
#include "Components/ColliderComponent.hpp"

class EntityManager {
   public:
    void update(float delta_time);
    void render();
    bool empty();
    Entity& addEntity(std::string entity_name, layers layer);
    void listEntities() const;
    std::string entityCollisions(Entity& entity) const;
    std::vector<Entity*> getEntities() const;
    std::vector<Entity*> getEntitiesByLayer(layers layer) const;
    unsigned int size() const;
    void clear();

   private:
    std::vector<Entity*> _entities;
	bool _pressed;
};

#endif  // !ENTITYMANAGER_H