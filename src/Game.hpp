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
    bool play() const;

   private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    bool _play;
};
#endif  // !GAME_H