#include "Game.hpp"

#include <iostream>

#include "Constants.hpp"
#include "glm.hpp"

glm::vec2 projectile_position = glm::vec2(0.0f, 0.0f);
glm::vec2 projectile_velocity = glm::vec2(20.0f, 20.0f);

Game::Game() : _loop(false), _window(nullptr), _renderer(nullptr) {}

Game::~Game() {}

bool Game::init(int width, int height) {
    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "[ERROR] SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    } else {
        std::cout << "[SUCCESS] SDL initialized successfully!\n";
    }

    // create window
    _window = SDL_CreateWindow("Debug", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_BORDERLESS);
    if (!_window) {
        std::cerr << "[ERROR] Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    } else {
        std::cout << "[SUCCESS] SDL Window created successfully!\n";
    }

    // create vsynced renderer for window
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        std::cerr << "[ERROR] Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    } else {
        SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        std::cout << "[SUCCESS] SDL renderer created successfully!\n";
    }

    //game is now running
    _loop = true;
    return _loop;
}
void Game::processInput() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            _loop = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                _loop = false;
                break;
            }
        default:
            break;
    }
}

void Game::update() {
    //delay until we reach our target time in milliseconds
    int cap_time = FRAME_TARGET_TIME - (SDL_GetTicks() - ticks_last_frame);
    //delay if we are too fast to process this frame
    if (cap_time > 0 && cap_time <= FRAME_TARGET_TIME) {
        SDL_Delay(cap_time);
    }

    //delta time = difference in ticks from last frame converted to seconds
    float delta_time = (SDL_GetTicks() - ticks_last_frame) / 1000.0f;
    //clamp deltatime to maximum value
    delta_time = (delta_time > 0.05f) ? 0.05f : delta_time;

    //sets the new ticks for the current frame to be used in the next pass
    ticks_last_frame = SDL_GetTicks();

    projectile_position = glm::vec2(projectile_velocity.x,projectile_velocity.y);
}

void Game::render() {
    //clear screen
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    //create rect to represent projectile, set renderer color and draw it
    SDL_Rect projectile{(int)projectile_position.x, (int)projectile_position.y, 10, 10};
    SDL_SetRenderDrawColor(_renderer, 0x10, 0x10, 0x10, 0xFF);
    SDL_RenderFillRect(_renderer, &projectile);

    //update screen
    SDL_RenderPresent(_renderer);
}

bool Game::loop() const { return _loop; }

void Game::destroy() {
    // destroy renderer
    SDL_DestroyRenderer(_renderer);
    _renderer = nullptr;

    // destroy window
    SDL_DestroyWindow(_window);
    _window = nullptr;

    // quit sdl and subsystems
    SDL_Quit();
}
