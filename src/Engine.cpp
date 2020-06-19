#include "Engine.hpp"

// TODO: bad global variables
EntityManager manager;
AssetManager* Engine::_asset_manager = new AssetManager(&manager);
SDL_Renderer* Engine::_renderer = nullptr;
SDL_Event Engine::_event;
SDL_FRect Engine::_camera{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map;

// initializes our member variables
Engine::Engine() : _loop(false), _window(nullptr), _ticks_last_frame(0) {
#ifdef DEBUG
    _pressed = false;
#endif  // DEBUG
}

Engine::~Engine() {}

bool Engine::init(int width, int height) {
    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "[ERROR] SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    } else {
        std::cout << "[SUCCESS] SDL initialized successfully!\n";
    }

    // set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) {
        std::cout << "[WARNING] Linear texture filtering not enabled!\n";
    } else {
        std::cout << "[SUCCESS] Linear texture filterning enabled!\n";
    }

    // create window
    _window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
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

	// initialize PNG loading
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "[ERROR] SDL_Image could not be initialized! SDL_Image Error: " << IMG_GetError() << "\n";
        return false;
    } else {
        std::cout << "[SUCCESS] SDL_Image initialized successfully!\n";
    }

	if (TTF_Init() < 0) {
        std::cerr << "[ERROR] SDL_ttf could not be initialized! SDL_ttf Error: " << TTF_GetError() << "\n";
        return false;
    } else {
        std::cout << "[SUCCESS] SDL_ttf initialized successfully!\n";
    }

    loadLevel(0);

    // game is now running
    _loop = true;
    return _loop;
}

Entity& player(manager.addEntity("chopper", PLAYER_LAYER));

void Engine::loadLevel(int level) {
    switch (level) {
        case 0: {
            _asset_manager->addTexture("tank-img", "./assets/images/tank-big-right.png");
            _asset_manager->addTexture("chopper-spritesheet", "./assets/images/chopper-spritesheet.png");
            _asset_manager->addTexture("radar-img", "./assets/images/radar.png");
            _asset_manager->addTexture("jungle-tilemap", "./assets/tilemaps/jungle.png");
            _asset_manager->addTexture("helipad-img", "./assets/images/heliport.png");
			_asset_manager->addFont("charriot", "./assets/fonts/charriot.ttf", 16);

#ifdef DEBUG
            _asset_manager->addTexture("bounding-box", "./assets/images/collision-texture.png");
#endif  // DEBUG

            map = new Map("jungle-tilemap", 2, 32);
            map->loadMap("./assets/tilemaps/jungle.map", 25, 20);

            player.addComponent<TransformComponent>(240.0f, 106.0f, 0.0f, 0.0f, 32, 32, 1);
            player.addComponent<SpriteComponent>("chopper-spritesheet", 2, 90, true, false);
            player.addComponent<PlayerInputComponent>(200, "w", "s", "a", "d", "space");
            player.addComponent<ColliderComponent>("PLAYER");

            Entity& tank(manager.addEntity("tank", ENEMY_LAYER));
            tank.addComponent<TransformComponent>(150.0f, 495.0f, 5.0f, 0.0f, 32, 32, 1);
            tank.addComponent<SpriteComponent>("tank-img");
            tank.addComponent<ColliderComponent>("ENEMY");

			Entity& helipad(manager.addEntity("helipad", OBSTACLE_LAYER));
			helipad.addComponent<TransformComponent>(470.0f, 420.0f, 0.0f, 0.0f, 32, 32, 1);
			helipad.addComponent<SpriteComponent>("helipad-img");
			helipad.addComponent<ColliderComponent>("TARGET");

            Entity& radar = manager.addEntity("radar", UI_LAYER);
            radar.addComponent<TransformComponent>(720.0f, 15.0f, 0.0f, 0.0f, 64, 64, 1);
            radar.addComponent<SpriteComponent>("radar-img", 8, 150, false, true);

			Entity& label = manager.addEntity("label_1", UI_LAYER);
			label.addComponent<LabelComponent>(10.0f, 10.0f, "Level 1", "charriot", SDL_Color{255, 255, 255, 255});

            manager.listEntities();
            break;
        }
        default: {
            break;
        }
    }
}

// processes input
void Engine::processInput() {
    SDL_PollEvent(&_event);
    switch (_event.type) {
        case SDL_QUIT:
            _loop = false;
            break;
        case SDL_KEYDOWN:
            if (_event.key.keysym.sym == SDLK_ESCAPE) {
                _loop = false;
                break;
            }
#ifdef DEBUG
            if (_event.key.keysym.sym == SDLK_F1) {
                if (!_pressed) {
                    _pressed = true;
                    if (!manager._colliders_visible) {
                        manager.showColliders();
                    } else {
                        manager.hideColliders();
                    }

                    if (!manager._tile_map_visible) {
                        manager.showTileMap();
                    } else {
                        manager.hideTileMap();
                    }
                }
                break;
            }
        case SDL_KEYUP:
            if (_event.key.keysym.sym == SDLK_F1) {
                _pressed = false;
            }
#endif  // DEBUG
        default:
            break;
    }
}

// updates the state of our application
void Engine::update() {
    // delay until we reach our target time in milliseconds
    uint32_t delay = FRAME_TIME - (SDL_GetTicks() - _ticks_last_frame);

    // if it took 1ms to render the last frame and our target is to render
    // a frame every 16.6ms, 16.6 - 1 = 15.6ms, that means we must wait
    // 15.6ms til we can render the next frame to maintain a 60 frames
    // per second.

    // delay if we are too fast to process this frame to keep within our
    // target frame time
    if (delay > 0 && delay <= FRAME_TIME) {
        SDL_Delay(delay);
    }

    // delta time = difference in ticks from last frame converted to seconds
    // how much time has ellapsed since the last frame.
    float delta_time = (SDL_GetTicks() - _ticks_last_frame) / 1000.0f;

    // clamp deltatime to maximum value. This is so if we are debugging,
    // our delta time can become huge between steps. This can also happen
    // if our CPU suddenly becomes bogged down with some other operation
    delta_time = (delta_time > 0.05f) ? 0.05f : delta_time;

    // sets the new ticks for the current frame to be used in the next pass
    _ticks_last_frame = SDL_GetTicks();

    manager.update(delta_time);

    camera();
    collisions();
}

void Engine::camera() {
    TransformComponent* player_position = player.getComponent<TransformComponent>();

    _camera.x = player_position->_position.x - ((WINDOW_WIDTH / 2) - (player_position->_width / 2));
    _camera.y = player_position->_position.y - ((WINDOW_HEIGHT / 2) - (player_position->_height / 2));

    if (_camera.x < 0) {
        _camera.x = 0;
    }

    if (_camera.y < 0) {
        _camera.y = 0;
    }

    if (_camera.x > _camera.w) {
        _camera.x = _camera.w;
    }

    if (_camera.y > _camera.h) {
        _camera.y = _camera.h;
    }
}

void Engine::collisions() {
    COLLISION_TYPE collision = manager.entityCollisions();
    if (collision == PLAYER_ENEMY_COLLISION) {
		gameOver();
    }
	if(collision == TARGET_COLLISION){
		nextLevel(1);
	}
}

void Engine::nextLevel(int level){
	std::cout << "Loading next level\n";
	_loop = false;
}

void Engine::gameOver(){
	std::cout << "Game Over\n";
	_loop = false;
}

// renders the state of our application, shows our entities
void Engine::render() {
    // set the front buffer to white
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // clear back buffer
    SDL_RenderClear(_renderer);

    // if we have entities to render
    if (!manager.empty()) {
        manager.render();
    }

    // update screen
    SDL_RenderPresent(_renderer);
}

// check to see if the game is active or not
bool Engine::loop() const { return _loop; }

// shuts down sdl and cleans everything up
void Engine::destroy() {
    // destroy renderer
    SDL_DestroyRenderer(_renderer);
    _renderer = nullptr;

    // destroy window
    SDL_DestroyWindow(_window);
    _window = nullptr;

    // quit sdl and subsystems
	IMG_Quit();
	TTF_Quit();
    SDL_Quit();
}
