#include "./EntityManager.hpp"

//updates all our entities within our application
void EntityManager::update(float delta_time) {
    for (auto& entity : _entities) {
        entity->update(delta_time);
    }
}

//renders all our entities within our application
void EntityManager::render() {
    for (auto& entity : _entities) {
        entity->render();
    }
}

//checks to see if we have any entites
bool EntityManager::empty() { return _entities.empty(); }

//creates a new entity
Entity& EntityManager::addEntity(std::string entity_name) {
    Entity* entity = new Entity(*this, entity_name);
    _entities.emplace_back(entity);
    return *entity;
}

//returns all our entites
std::vector<Entity*> EntityManager::getEntities() const { return _entities; }

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
        std::cout << "Entity Name: " << entity->_entity_name << "\n";
        entity->listComponents();
    }
}