#include "ProjectileEmitterComponent.hpp"

ProjectileEmitterComponent::ProjectileEmitterComponent(int speed, int range, int angle, bool loop) :
 _speed(speed),
 _range(range),
 _angle_radians(glm::radians(static_cast<float>(angle))),
 _loop(loop) {}

ProjectileEmitterComponent::~ProjectileEmitterComponent() {}

void ProjectileEmitterComponent::initialize() {
	_transform = _entity->getComponent<TransformComponent>();
	_origin = glm::vec2(_transform->_position.x, _transform->_position.y);
	_transform->_velocity = glm::vec2(glm::cos(_angle_radians) * _speed, glm::sin(_angle_radians) * _speed);
}

void ProjectileEmitterComponent::update(float delta_time) {
	if(glm::distance(_transform->_position, _origin) > _range){
		if(_loop){
			_transform->_position.x = _origin.x;
			_transform->_position.y = _origin.y;
		} else{
			_entity->destroy();
		}
	}
}
void ProjectileEmitterComponent::render() {}