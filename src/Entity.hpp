#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
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
    void listComponents() const;

    // add generic component to our component vector.
    template <typename T, typename... Targs>
    T& addComponent(Targs&&... args) {
        T* component = new T(std::forward<Targs>(args)...);
        component->_entity = this;
        _components.emplace_back(component);
        _component_type_map[&typeid(*component)] = component;
        component->initialize();
        return *component;
    }

    template <typename T>
    T* getComponent() {
        auto element = _component_type_map.find(&typeid(T));
        if(element == _component_type_map.end()){
            std::cerr << "[ERROR] " << _entity_name << "<" << typeid(T).name() <<"> Component not found\n";
            return nullptr;
        } else {
            return static_cast<T*>(element->second);
        }        
    }

    template <typename T>
    bool hasComponent() const {
        for (auto element : _component_type_map) {
            if (element.first->name() == typeid(T).name()) {
                return true;
            }
        }
        return false;
    }

    std::string _entity_name;

   private:
    EntityManager& _manager;
    std::vector<Component*> _components;
    std::map<const std::type_info*, Component*> _component_type_map;
    bool _active;
};

#endif  // !ENTITY_H
