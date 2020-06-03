#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL.h>

#include "../AssetManager.hpp"
#include "../TextureManager.hpp"

class TransformComponent;

class SpriteComponent : public Component {
   public:
    SpriteComponent(std::string path);
    void setTexture(std::string asset_texture_ID);
    void initialize() override;
    void update(float delta_time) override;
    void render() override;

    SDL_RendererFlip _sprite_flip = SDL_FLIP_NONE;

   private:
    TransformComponent* _transform;
    SDL_Texture* _texture;
    SDL_Rect _source_rectangle;
    SDL_Rect _destination_rect;
};

#endif  // !SPRITECOMPONENT_H