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
    EntityManager();
    void update(float delta_time);
    void render();
    bool empty();
    Entity& addEntity(std::string entity_name, LAYERS layer);
    void listEntities() const;
    COLLISION_TYPE entityCollisions() const;
#ifdef DEBUG
	void showColliders();
	void hideColliders();
#endif  // DEBUG
    std::vector<Entity*> getEntities() const;
    std::vector<Entity*> getEntitiesByLayer(LAYERS layer) const;
    unsigned int size() const;
    void clear();

#ifdef DEBUG
	bool _colliders_visible;
#endif  // DEBUG

   private:
    std::vector<Entity*> _entities;
};

#endif  // !ENTITYMANAGER_H