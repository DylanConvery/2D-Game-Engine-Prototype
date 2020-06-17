#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include "../Collision.hpp"
#include "../EntityManager.hpp"
#include "TransformComponent.hpp"
#include "../Engine.hpp"

class ColliderComponent : public Component {
   public:
    ColliderComponent(std::string collider_tag,
     int x, int y, int width, int height);
    void initialize() override;
    void update(float delta_time) override;
    void render() override;

   private:
    std::string _collider_tag;
    SDL_Rect _collider;
    SDL_Rect _source;
    SDL_Rect _destination;
    TransformComponent* _transform;
};

#endif