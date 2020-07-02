#include "EntityManager.hpp"

EntityManager::EntityManager() {
#ifdef DEBUG
    _colliders_visible = false;
#endif  // DEBUG
}

// updates all our entities within our application
void EntityManager::update(float delta_time) {
    for (auto i = _entities.begin(); i < _entities.end(); i++) {
        (*i)->update(delta_time);
        if (!(*i)->active()) {
            _entities.erase(i);
        }
    }
}

#ifdef DEBUG
void EntityManager::showColliders() {
    _colliders_visible = true;
    for (auto i : _entities) {
        if (i->hasComponent<ColliderComponent>()) {
            ColliderComponent* collider = i->getComponent<ColliderComponent>();
            collider->show();
        }
        if (i->hasComponent<TileComponent>()) {
            TileComponent* tile = i->getComponent<TileComponent>();
            tile->showTileContainer();
        }
    }
}

void EntityManager::hideColliders() {
    _colliders_visible = false;
    for (auto i : _entities) {
        if (i->hasComponent<ColliderComponent>()) {
            ColliderComponent* collider = i->getComponent<ColliderComponent>();
            collider->hide();
        }
        if (i->hasComponent<TileComponent>()) {
            TileComponent* tile = i->getComponent<TileComponent>();
            tile->hideTileContainer();
        }
    }
}
#endif  // DEBUG

// renders all our entities within our application
// TODO: refactor this so it's not so slow. Looping all of our entities
// multiple times a second is slow
void EntityManager::render() {
    for (int layer = 0; layer < NUM_LAYERS; layer++) {
        for (auto& entity : getEntitiesByLayer(static_cast<LAYERS>(layer))) {
            entity->render();
        }
    }
}

// checks to see if we have any entites
bool EntityManager::empty() { return _entities.empty(); }

// creates a new entity
Entity& EntityManager::addEntity(std::string entity_name, LAYERS layer) {
    Entity* entity = new Entity(*this, entity_name, layer);
    _entities.emplace_back(entity);
    return *entity;
}

// returns all our entites
std::vector<Entity*> EntityManager::getEntities() const { return _entities; }

// finds all entities of a particular layer and returns them
std::vector<Entity*> EntityManager::getEntitiesByLayer(LAYERS layer) const {
    std::vector<Entity*> entities;
    for (auto& i : _entities) {
        if (i->_layer == layer) {
            entities.emplace_back(i);
        }
    }
    return entities;
}

Entity* EntityManager::getEntityByName(std::string entity_name) const {
    for (auto& i : _entities) {
        if (i->active()) {
            if (i->_name == entity_name) {
                return i;
            }
        }
    }
}

// returns how many entities we have
unsigned int EntityManager::size() const { return _entities.size(); }

// destroys all entities
void EntityManager::clear() {
    for (auto& entity : _entities) {
        entity->destroy();
    }
}

// prints all entities we manage
void EntityManager::listEntities() const {
    for (auto& entity : _entities) {
        std::cout << "Entity Name: " << entity->_name << "\n";
        entity->listComponents();
    }
}

// tests all entites to see if there are any collisions.
COLLISION_TYPE EntityManager::entityCollisions() const {
    for (auto& entity_a : _entities) {
        if (entity_a->hasComponent<ColliderComponent>()) {
            ColliderComponent* collider_a = entity_a->getComponent<ColliderComponent>();
            for (auto& entity_b : _entities) {
                if (entity_a->_name.compare(entity_b->_name) != 0) {
                    if (entity_b->hasComponent<ColliderComponent>()) {
                        ColliderComponent* collider_b = entity_b->getComponent<ColliderComponent>();
                        if (Collision::checkCollision(collider_a->_collider, collider_b->_collider)) {
                            // player enemy collision
                            if (collider_a->_collider_tag.compare("PLAYER") == 0 && collider_b->_collider_tag.compare("ENEMY") == 0) {
                                return PLAYER_ENEMY_COLLISION;
                            }

                            if (collider_a->_collider_tag.compare("PLAYER") == 0 && collider_b->_collider_tag.compare("PROJECTILE") == 0) {
                                return PLAYER_PROJECTILE_COLLSION;
                            }

                            if (collider_a->_collider_tag.compare("PLAYER") == 0 && collider_b->_collider_tag.compare("VEGETATION") == 0) {
                                return PLAYER_VEGETATION_COLLISION;
                            }

                            if (collider_a->_collider_tag.compare("ENEMY") == 0 && collider_b->_collider_tag.compare("PROJECTILE") == 0) {
                                return ENEMY_PROJECTILE_COLLISION;
                            }

                            if (collider_a->_collider_tag.compare("PLAYER") == 0 && collider_b->_collider_tag.compare("TARGET") == 0) {
                                return TARGET_COLLISION;
                            }
                        }
                    }
                }
            }
        }
    }
    return NO_COLLISION;
}