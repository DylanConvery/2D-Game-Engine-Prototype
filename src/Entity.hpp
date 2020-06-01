#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

#include "Component.hpp"
#include "EntityManager.hpp"

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

    template <typename T, typename... Targs>
    T& addComponent(Targs&&... args) {
        T* component(new T(std::forward<Targs>(args)...));
        component->_entity = this;
        _components.emplace_back(component);
        component->initialize();
        return *component;
    }

    std::string _entity_name;

   private:
    EntityManager& _manager;
    std::vector<Component*> _components;
    bool _active;
};

#endif  // !ENTITY_H
