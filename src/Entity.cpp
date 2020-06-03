#include "./Entity.hpp"

Entity::Entity(EntityManager& manager) : _manager(manager), _active(true) {}

Entity::Entity(EntityManager& manager, std::string entity_name) : _manager(manager), _entity_name(entity_name), _active(true) {}

//if we have any components, call their update functions
void Entity::update(float delta_time) {
    for (auto& component : _components) {
        component->update(delta_time);
    }
}

//if we have any components, call their render functions
void Entity::render() {
    for (auto& component : _components) {
        component->render();
    }
}

void Entity::destroy() { _active = false; }

//check if we our still active
bool Entity::active() const { return _active; }

//prints out attached components, will only list one component type,
//if you have 2 of the same components, it will only be listed once
void Entity::listComponents() const {
    for (auto element : _component_type_map) {
        std::cout << "\tComponent<" << element.first->name() << ">\n";
    }
}