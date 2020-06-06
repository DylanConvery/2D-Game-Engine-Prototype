#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(std::string asset_texture_id) : _animated(false), _fixed(false) {
    setTexture(asset_texture_id);
}

SpriteComponent::SpriteComponent(std::string animation_id, unsigned frames, unsigned speed, bool directed, bool fixed) : _animated(true), _frames(frames), _speed(speed), _fixed(fixed) {
    if (directed) {
        Animation down(0, frames, speed);
        Animation left(1, frames, speed);
        Animation right(2, frames, speed);
        Animation up(3, frames, speed);

        _animations.emplace("down", down);
        _animations.emplace("left", left);
        _animations.emplace("right", right);
        _animations.emplace("up", up);

        _index = 0;
        _animation = "down";
    } else {
        Animation animation(0, frames, speed);
        _animations.emplace("single_animation", animation);
        _index = 0;
        _animation = "single_animation";
    }
    play(_animation);
    setTexture(animation_id);
}

void SpriteComponent::play(std::string animation){
    unsigned frames = _animations[animation]._frames;
    unsigned index = _animations[animation]._index;
    unsigned speed = _animations[animation]._speed;
    _animation = animation;
}

void SpriteComponent::setTexture(std::string asset_texture_id) {
    _texture = Engine::_asset_manager->getTexture(asset_texture_id);
}

//TODO: bad because if we don't have a TransformComponent attached, we try dereference a null ptr
void SpriteComponent::initialize() {
    _transform = _entity->getComponent<TransformComponent>();
    _source_rectangle.x = 0;
    _source_rectangle.y = 0;
    _source_rectangle.w = static_cast<int>(_transform->_width);
    _source_rectangle.h = static_cast<int>(_transform->_height);
}

void SpriteComponent::update(float delta_time) {
    if(_animated){
        _source_rectangle.x = _source_rectangle.w * static_cast<int>((SDL_GetTicks() / _speed) % _frames);
    }
    _source_rectangle.y = _index * _transform->_height;

    _destination_rect.x = static_cast<int>(_transform->_position.x);
    _destination_rect.y = static_cast<int>(_transform->_position.y);
    _destination_rect.w = static_cast<int>(_transform->_width * _transform->_scale);
    _destination_rect.h = static_cast<int>(_transform->_height * _transform->_scale);
    std::cout << _index << "\n" << _animation << '\n';
}

void SpriteComponent::render() {
    TextureManager::draw(_texture, _source_rectangle, _destination_rect, _sprite_flip);
}