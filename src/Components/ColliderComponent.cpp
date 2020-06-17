#include "ColliderComponent.hpp"

ColliderComponent::ColliderComponent(std::string collider_tag) : _collider_tag(collider_tag) {
#ifdef DEBUG
    _visible = false;
#endif  // DEBUG
}

void ColliderComponent::initialize() {
#ifdef DEBUG
    _texture = Engine::_asset_manager->getTexture("bounding-box");
#endif  // DEBUG
    _transform = _entity->getComponent<TransformComponent>();
    if (_transform != nullptr) {
        _collider.x = static_cast<int>(_transform->_position.x);
        _collider.y = static_cast<int>(_transform->_position.y);
        _collider.w = static_cast<int>(_transform->_width * _transform->_scale);
        _collider.h = static_cast<int>(_transform->_height * _transform->_scale);
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

#ifdef DEBUG
void ColliderComponent::show() {
    _visible = true;
}

void ColliderComponent::hide() {
    _visible = false;
}
#endif  // DEBUG

void ColliderComponent::render() {
#ifdef DEBUG
    if (_transform != nullptr) {
        if (_visible) {
            TextureManager::draw(_texture, _source, _destination, SDL_FLIP_NONE);
        }
    }
#endif  // DEBUG
}