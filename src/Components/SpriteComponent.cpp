#include "./SpriteComponent.hpp"

SpriteComponent::SpriteComponent(std::string path) { setTexture(path); }

void SpriteComponent::setTexture(std::string asset_texture_ID) { _texture = Engine::_asset_manager->getTexture(asset_texture_ID); }

void SpriteComponent::initialize() {
    _transform = _entity->getComponent<TransformComponent>();
    _source_rectangle.x = 0;
    _source_rectangle.y = 0;
    _source_rectangle.w = _transform->_width;
    _source_rectangle.h = _transform->_height;
}

void SpriteComponent::update(float delta_time) {
    _destination_rect.x = _transform->_position.x;
    _destination_rect.y = _transform->_position.y;
    _destination_rect.w = _transform->_width * _transform->_scale;
    _destination_rect.h = _transform->_height * _transform->_scale;
}

void SpriteComponent::render() { TextureManager::draw(_texture, _source_rectangle, _destination_rect, _sprite_flip); }