#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <SDL.h>
#include "../../lib/glm/glm.hpp"

class TransformComponent : public Component {
   public:
    // initialize our members
    TransformComponent(float position_x, float position_y, float velocity_x, float velocity_y, float width, float height, float scale) 
    : _position(glm::vec2(position_x, position_y)), _velocity(glm::vec2(velocity_x, velocity_y)), _width(width), _height(height), _scale(scale) {}

    // changes our position relevant to our time and velocity
    void update(float delta_time) override {
        _position.x += _velocity.x * delta_time;
        _position.y += _velocity.y * delta_time;
    }

    glm::vec2 _position;
    glm::vec2 _velocity;
    float _width;
    float _height;
    float _scale;
};

#endif  // !TRANSFORMCOMPONENT_H