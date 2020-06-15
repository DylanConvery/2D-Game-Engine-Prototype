#include "ColliderComponent.hpp"

ColliderComponent::ColliderComponent(std::string collider_tag, int x, int y, int width, int height) : _collider_tag(collider_tag), _collider{x, y, width, height} {}

void ColliderComponent::initialize() {
    _transform = _entity->getComponent<TransformComponent>();
    if (_transform != nullptr) {
        _source = {0, 0, _transform->_width, _transform->_height};
        _destination = {_collider.x, _collider.y, _collider.w, _collider.h};
    }
}

void ColliderComponent::update(float delta_time) {
    if (_transform != nullptr) {
        _collider.x = static_cast<int>(_transform->_position.x);
        _collider.y = static_cast<int>(_transform->_position.y);
        _collider.w = static_cast<int>(_transform->_width * _transform->_scale);
        _collider.h = static_cast<int>(_transform->_height * _transform->_scale);

        _destination.x = _collider.x - Engine::_camera.x;
        _destination.y = _collider.y - Engine::_camera.y;
    }
}

void ColliderComponent::render() {}