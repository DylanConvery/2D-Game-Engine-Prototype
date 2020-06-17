#include "ColliderComponent.hpp"

/*
    std::string _collider_tag;
    SDL_Rect _collider;
    SDL_Rect _source;
    SDL_Rect _destination;
    TransformComponent* _transform;
*/

ColliderComponent::ColliderComponent(std::string collider_tag, int x, int y, int width, int height) {
	_collider_tag = collider_tag;
	_collider.x = x;
	_collider.y = y;
	_collider.w = width;
	_collider.h = height;
}

void ColliderComponent::initialize() {}
void ColliderComponent::update(float delta_time) {}
void ColliderComponent::render() {}