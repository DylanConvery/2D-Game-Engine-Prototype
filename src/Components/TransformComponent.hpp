#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <SDL2/SDL.h>
#include "../../lib/glm/glm.hpp"
#include "../Component.hpp"

class TransformComponent : public Component {
   public:
    // initialize our members
    TransformComponent(float position_x, float position_y, float velocity_x, float velocity_y, int width, int height, int scale);

    // changes our position relevant to our time and velocity
    void update(float delta_time) override;

    glm::vec2 _position;
    glm::vec2 _velocity;
    int _width;
    int _height;
    int _scale;
};

#endif  // !TRANSFORMCOMPONENT_H