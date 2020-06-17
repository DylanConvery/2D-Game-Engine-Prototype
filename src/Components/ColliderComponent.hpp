#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include "../Collision.hpp"
#include "../Engine.hpp"
#include "../EntityManager.hpp"
#include "TransformComponent.hpp"

class ColliderComponent : public Component {
   public:
    ColliderComponent(std::string collider_tag);
    void initialize() override;
    void update(float delta_time) override;
    void render() override;

#ifdef DEBUG
    void show();
    void hide();
    bool _visible;
#endif  // DEBUG

    SDL_Rect _collider;
    std::string _collider_tag;

   private:
    SDL_Rect _source;
    SDL_Rect _destination;
    TransformComponent* _transform;
    SDL_Texture* _texture;

};

#endif