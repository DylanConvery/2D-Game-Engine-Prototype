#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(std::string asset_texture_id) : _animated(false), _fixed(false), _index(0) {
    setTexture(asset_texture_id);
}

//creates appropriate animations for the given case
SpriteComponent::SpriteComponent(std::string animation_id, unsigned frames, unsigned speed, bool directed, bool fixed) : _animated(true), _frames(frames), _speed(speed), _fixed(fixed) {
    if (directed) {
        Animation down(0, frames, speed);
        Animation right(1, frames, speed);
        Animation left(2, frames, speed);
        Animation up(3, frames, speed);

        _animations.emplace("down", down);
        _animations.emplace("right", right);
        _animations.emplace("left", left);
        _animations.emplace("up", up);

        _index = 0;
        _animation = "down";
    } else {
        Animation animation(0, frames, speed);
        _animations.emplace("single_frame", animation);
        _index = 0;
        _animation = "single_frame";
    }
    play(_animation);
    setTexture(animation_id);
}

//sets our member variables to the appropriate values for the specified animation
void SpriteComponent::play(std::string animation) {
    _frames = _animations[animation]._frames;
    _index = _animations[animation]._index;
    _speed = _animations[animation]._speed;
    _animation = animation;
}

void SpriteComponent::setTexture(std::string asset_texture_id) {
    _texture = Engine::_asset_manager->getTexture(asset_texture_id);
}

//TODO: bad because if we don't have a TransformComponent attached, we try dereference a null ptr
void SpriteComponent::initialize() {
    _transform = _entity->getComponent<TransformComponent>();
    //make sure we get transform component to work with
    if (_transform != nullptr) {
        _source_rectangle.x = 0;
        _source_rectangle.y = 0;
        _source_rectangle.w = _transform->_width;
        _source_rectangle.h = _transform->_height;
    }
}

void SpriteComponent::update(float delta_time) {
    //make sure we have a transform component to work with
    if (_transform != nullptr) {
        //move our source retangle back and forth horizontally across our sprite sheet every (SDL_ticks / speed) % frames
        if (_animated) {
            _source_rectangle.x = _source_rectangle.w * static_cast<int>((SDL_GetTicks() / _speed) % _frames);
        }
        //move our source rectangle up and down
        _source_rectangle.y = _index * _transform->_height;
        if (_fixed) {
            _destination_rect.x = _transform->_position.x;
            _destination_rect.y = _transform->_position.y;
        } else {
            _destination_rect.x = _transform->_position.x - Engine::_camera.x;
            _destination_rect.y = _transform->_position.y - Engine::_camera.y;
        }
        _destination_rect.w = _transform->_width * _transform->_scale;
        _destination_rect.h =_transform->_height * _transform->_scale;
    }
}

void SpriteComponent::render() {
    TextureManager::draw(_texture, _source_rectangle, _destination_rect, _sprite_flip);
}