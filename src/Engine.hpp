#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

#include "Constants.hpp"
#include "EntityManager.hpp"
#include "glm.hpp"
#include "Components/TransformComponent.hpp"

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
    uint32_t ticks_last_frame;

   private:
    SDL_Window* _window;
    bool _loop;
};
#endif  // !ENGINE_H