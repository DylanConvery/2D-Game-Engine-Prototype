#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL.h>

#include "../Component.hpp"
#include "../TextureManager.hpp"
#include "TransformComponent.hpp"

class SpriteComponent : public Component {
   public:
    SpriteComponent(std::string path);

    void setTexture(std::string asset_texture_ID);

    //TODO: bad because if we don't have a TransformComponent attached, we try dereference a null ptr
    void initialize();

    void update(float delta_time);

    void render();

    SDL_RendererFlip _sprite_flip = SDL_FLIP_NONE;

   private:
    TransformComponent* _transform;
    SDL_Texture* _texture;
    SDL_Rect _source_rectangle;
    SDL_Rect _destination_rect;
};

#endif  // !SPRITECOMPONENT_H