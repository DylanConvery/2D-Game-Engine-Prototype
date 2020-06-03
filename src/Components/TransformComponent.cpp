#include "TransformComponent.hpp"

// initialize our members
TransformComponent::TransformComponent(float position_x, float position_y, float velocity_x, float velocity_y, float width, float height, float scale)
    : _position(glm::vec2(position_x, position_y)), _velocity(glm::vec2(velocity_x, velocity_y)), _width(width), _height(height), _scale(scale) {}

// changes our position relevant to our time and velocity
void TransformComponent::update(float delta_time) {
    _position.x += _velocity.x * delta_time;
    _position.y += _velocity.y * delta_time;
}
