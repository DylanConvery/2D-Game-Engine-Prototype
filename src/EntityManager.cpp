#include "EntityManager.hpp"

//updates all our entities within our application
void EntityManager::update(float delta_time) {
#ifdef DEBUG
    if (Engine::_event.type == SDL_KEYDOWN) {
        if (Engine::_event.key.keysym.sym == SDLK_F1) {
            if (!_pressed) {
                _pressed = true;
                for (auto i : _entities) {
                    if (i->hasComponent<ColliderComponent>()) {
                        ColliderComponent* collider = i->getComponent<ColliderComponent>();
                        if (collider->_visible) {
                            collider->hide();
                        } else {
                            collider->show();
                        }
                    }
                }
            }
        }
    }

    if (Engine::_event.type == SDL_KEYUP) {
        if (Engine::_event.key.keysym.sym == SDLK_F1) {
            _pressed = false;
        }
    }
#endif  // DEBUG

    for (auto& entity : _entities) {
        entity->update(delta_time);
    }
}

//renders all our entities within our application
//TODO: refactor this so it's not so slow. Looping all of our entities
//multiple times a second is slow
void EntityManager::render() {
    for (int layer = 0; layer < NUM_LAYERS; layer++) {
        for (auto& entity : getEntitiesByLayer(static_cast<layers>(layer))) {
            entity->render();
        }
    }
}

//checks to see if we have any entites
bool EntityManager::empty() { return _entities.empty(); }

//creates a new entity
Entity& EntityManager::addEntity(std::string entity_name, layers layer) {
    Entity* entity = new Entity(*this, entity_name, layer);
    _entities.emplace_back(entity);
    return *entity;
}

//returns all our entites
std::vector<Entity*> EntityManager::getEntities() const { return _entities; }

//finds all entities of a particular layer and returns them
std::vector<Entity*> EntityManager::getEntitiesByLayer(layers layer) const {
    std::vector<Entity*> entities;
    for (auto& i : _entities) {
        if (i->_layer == layer) {
            entities.emplace_back(i);
        }
    }
    return entities;
}

//returns how many entities we have
unsigned int EntityManager::size() const { return _entities.size(); }

//destroys all entities
void EntityManager::clear() {
    for (auto& entity : _entities) {
        entity->destroy();
    }
}

//prints all entities we manage
void EntityManager::listEntities() const {
    for (auto& entity : _entities) {
        std::cout << "Entity Name: " << entity->_name << "\n";
        entity->listComponents();
    }
}

std::string EntityManager::entityCollisions(Entity& entity) const {
    ColliderComponent* collider_a = entity.getComponent<ColliderComponent>();
    if (collider_a != nullptr) {
        for (auto i : _entities) {
            if (i->_name.compare(entity._name) != 0 && i->_name.compare("Tile") != 0) {
                if (i->hasComponent<ColliderComponent>()) {
                    ColliderComponent* collider_b = i->getComponent<ColliderComponent>();
                    if (collider_b != nullptr) {
                        if (Collision::checkCollision(collider_a->_collider, collider_b->_collider)) {
                            return collider_b->_collider_tag;
                        }
                    }
                }
            }
        }
    }
    return std::string();
}