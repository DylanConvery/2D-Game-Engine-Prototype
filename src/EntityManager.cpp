#include "EntityManager.hpp"

void EntityManager::update(float delta_time) {
    for (auto& entity : _entities) {
        entity->update(delta_time);
    }
}

void EntityManager::render() {
    for (auto& entity : _entities) {
        entity->render();
    }
}

bool EntityManager::empty() { return _entities.empty(); }

Entity& EntityManager::addEntity(std::string entity_name) {
    Entity* entity = new Entity(*this, entity_name);
    _entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity*> EntityManager::getEntities() const { return _entities; }

unsigned int EntityManager::size() const { return _entities.size(); }

void EntityManager::clear() {
    for (auto& entity : _entities) {
        entity->destroy();
    }
}

void EntityManager::listEntities() {
    for (auto& entity : _entities) {
        std::cout << "Entity Name: " << entity->_entity_name << "\n";
        entity->listComponents();
    }
}