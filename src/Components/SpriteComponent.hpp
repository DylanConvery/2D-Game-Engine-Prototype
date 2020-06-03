#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL.h>
#include "../TextureManager.hpp"

class SpriteComponent : public Component {
   public:
    SpriteComponent(std::string path) { 
        setTexture(path); 
    }

    void setTexture(std::string asset_texture_ID) { 
        _texture = Engine::_asset_manager->getTexture(asset_texture_ID);
    }

    //TODO: bad because if we don't have a TransformComponent attached, we try dereference a null ptr
    void initialize() {
        _transform = _entity->getComponent<TransformComponent>();
        _source_rectangle.x = 0;
        _source_rectangle.y = 0;
        _source_rectangle.w = _transform->_width;
        _source_rectangle.h = _transform->_height;
    }

    void update(float delta_time) {
        _destination_rect.x = _transform->_position.x;
        _destination_rect.y = _transform->_position.y;
        _destination_rect.w = _transform->_width * _transform->_scale;
        _destination_rect.h = _transform->_height * _transform->_scale;
    }

    void render() { 
        TextureManager::draw(_texture, _source_rectangle, _destination_rect, _sprite_flip);
    }

    SDL_RendererFlip _sprite_flip = SDL_FLIP_NONE;
   private:
    TransformComponent* _transform;
    SDL_Texture* _texture;
    SDL_Rect _source_rectangle;
    SDL_Rect _destination_rect;
};

#endif  // !SPRITECOMPONENT_H