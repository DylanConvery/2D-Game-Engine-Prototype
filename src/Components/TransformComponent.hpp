#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "EntityManager.hpp"
#include "glm.hpp"
#include <SDL.h>
#include "Game.hpp"

class TransformComponent : public Component {
   public:
	TransformComponent(float position_x, float position_y, float velocity_x, float velocity_y, float width, float height, float scale);
	
	void initialize() override;
	void update(float delta_time) override;
	void render() override;

    glm::vec2 _position;
	glm::vec2 _velocity;
	float _width;
	float _height;
	float _scale;
};

#endif // !TRANSFORMCOMPONENT_H