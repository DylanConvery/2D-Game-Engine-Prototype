#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "../lib/glm/glm.hpp"
#include "AssetManager.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/PlayerInputComponent.hpp"
#include "Constants.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

class AssetManager;

class Engine {
   public:
    Engine();
    ~Engine();
    bool init(int width, int height);
    void processInput();
    void update();
    void render();
    void destroy();
    bool loop() const;
    void loadLevel(int level);

    static SDL_Renderer* _renderer;
    static AssetManager* _asset_manager;
    static SDL_Event _event;
    uint32_t ticks_last_frame;

   private:
    SDL_Window* _window;
    bool _loop;
};
#endif  // !ENGINE_H