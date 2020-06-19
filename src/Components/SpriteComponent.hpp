#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>

#include "../Animation.hpp"
#include "../Component.hpp"
#include "../TextureManager.hpp"
#include "TransformComponent.hpp"

class SpriteComponent : public Component {
   public:
    SpriteComponent(std::string asset_texture_id);
    SpriteComponent(std::string animation_id, unsigned frames, unsigned speed, bool directed, bool fixed);
    void setTexture(std::string asset_texture_id);
    void play(std::string animation);

    //TODO: bad because if we don't have a TransformComponent attached, we try dereference a null ptr
    void initialize() override;
    void update(float delta_time) override;
    void render() override;

    SDL_RendererFlip _sprite_flip = SDL_FLIP_NONE;

   private:
    TransformComponent* _transform;
    SDL_Texture* _texture;
    SDL_Rect _source_rectangle;
    SDL_FRect _destination_rect;

    std::map<std::string, Animation> _animations;
    std::string _animation;
    unsigned _index;
    bool _animated;
    unsigned _speed;
    unsigned _frames;
    bool _fixed;
};

#endif  // !SPRITECOMPONENT_H