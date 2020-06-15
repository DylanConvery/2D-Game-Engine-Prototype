#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <vector>
#include "Constants.hpp"
#include "Component.hpp"
#include "EntityManager.hpp"

class EntityManager;
class Component;

class Entity {
   public:
    Entity(EntityManager& manager);
    Entity(EntityManager& manager, std::string entity_name, layers layer);
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

    //checks if we have the specified component and returns it if we have it.
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

    //returns true if our entity has a specific component or false otherwise
    template <typename T>
    bool hasComponent() const {
        return _component_type_map.count(&typeid(T));
    }

    std::string _entity_name;
    layers _layer;

   private:
    EntityManager& _manager;
    std::vector<Component*> _components;
    std::map<const std::type_info*, Component*> _component_type_map;
    bool _active;
};

#endif  // !ENTITY_H
