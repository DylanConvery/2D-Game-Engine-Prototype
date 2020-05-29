#include "Game.hpp"

#include <iostream>

#include "Constants.hpp"

Game::Game() : _play(false), _window(nullptr), _renderer(nullptr) {}

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
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer) {
        std::cerr << "[ERROR] Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    } else {
        SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        std::cout << "[SUCCESS] SDL renderer created successfully!\n";
    }

    //game is now running
    _play = true;
}
void Game::processInput() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            _play = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                _play = false;
                break;
            }
        default:
            break;
    }
}

void Game::update() {

}

void Game::render() {
	//clear screen
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

	//update screen
    SDL_RenderPresent(_renderer);
}

bool Game::play() const { return _play; }

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
