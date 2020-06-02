#include "TransformComponent.hpp"

TransformComponent::TransformComponent(
    float position_x,
    float position_y,
    float velocity_x,
    float velocity_y,
    float width,
    float height,
    float scale)
    : _position(glm::vec2(position_x, position_y)),
      _velocity(glm::vec2(velocity_x, velocity_y)),
      _width(width),
      _height(height),
      _scale(scale) {}

void TransformComponent::initialize() {}

void TransformComponent::update(float delta_time) {
    _position.x += _velocity.x * delta_time;
    _position.y += _velocity.y * delta_time;
}

void TransformComponent::render() {
    SDL_Rect transform_rectangle{static_cast<int>(_position.x), static_cast<int>(_position.y), _width * _scale, _height * _scale};
    SDL_SetRenderDrawColor(Engine::_renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(Engine::_renderer, &transform_rectangle);
}
