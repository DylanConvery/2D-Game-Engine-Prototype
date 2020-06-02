#include "Entity.hpp"

Entity::Entity(EntityManager& manager) : _manager(manager), _active(true) {}

Entity::Entity(EntityManager& manager, std::string entity_name) : _manager(manager), _entity_name(entity_name), _active(true) {}

void Entity::update(float delta_time) {
    for (auto& component : _components) {
        component->update(delta_time);
    }
}

void Entity::render() {
    for (auto& component : _components) {
        component->render();
    }
}

void Entity::destroy() { _active = false; }

bool Entity::active() const { return _active; }

void Entity::listComponents() {
    for (auto& component : _components) {
        //TODO: get names of components
        std::cout << "\tComponent<" << "T" << ">\n";
    }
}