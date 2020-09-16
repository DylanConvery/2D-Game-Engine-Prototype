#ifndef ENGINE_H
#define ENGINE_H

//BUG:  if an error within AssetManager happens, it's because ColliderComponent 
//      tries to add the bounding box texture, the one used in debugging but 
//      the lua script never actuall adds it as a texture as I felt seeing as 
//      there isn't a way from lua to check whether the engine is in debug 
//      mode, why add a texture that is only used sometimes?

#define DEBUG

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "../lib/glm/glm.hpp"
#include "../lib/lua/sol.hpp"
#include "AssetManager.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/PlayerInputComponent.hpp"
#include "Components/TileComponent.hpp"
#include "Components/LabelComponent.hpp"
#include "Components/ProjectileEmitterComponent.hpp"
#include "Map.hpp"
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
    void camera();
    void collisions();
	void nextLevel(int level);
	void gameOver();

    static SDL_Renderer* _renderer;
    static AssetManager* _asset_manager;
    static SDL_Event _event;
    static SDL_FRect _camera;
    uint32_t _ticks_last_frame;

   private:
    SDL_Window* _window;
    bool _loop;
#ifdef DEBUG
	bool _pressed;
#endif // DEBUG
};
#endif  // !ENGINE_H