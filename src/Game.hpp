#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Game {
   public:
    Game();
    ~Game();

    bool init(int width, int height);

    void processInput();
    void update();
    void render();

    void destroy();

    bool loop() const;

   public:
    uint32_t ticks_last_frame;

   private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    bool _loop;
};
#endif  // !GAME_H