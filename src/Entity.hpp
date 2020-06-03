#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <map>
#include <typeinfo>
#include "./EntityManager.hpp"
#include "./Component.hpp"

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
    void listComponents();
    
    //add generic component to our component vector.
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
    T* getComponent(){
        return static_cast<T*>(_component_type_map.find(&typeid(T))->second);
    }

    std::string _entity_name;

   private:
    EntityManager& _manager;
    std::vector<Component*> _components;
    std::map<const std::type_info*, Component*> _component_type_map;
    bool _active;
};

#endif  // !ENTITY_H
