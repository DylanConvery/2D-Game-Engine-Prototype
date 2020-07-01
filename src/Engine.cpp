#include "Engine.hpp"

// TODO: bad global variables
EntityManager manager;
AssetManager* Engine::_asset_manager = new AssetManager(&manager);
SDL_Renderer* Engine::_renderer = nullptr;
SDL_Event Engine::_event;
SDL_FRect Engine::_camera{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map = nullptr;
Entity* player = nullptr;
#ifdef DEBUG
Entity* fps_label = nullptr;
#endif // !DEBUG

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

    loadLevel(1);

    // game is now running
    _loop = true;
    return _loop;
}

void Engine::loadLevel(int level) {
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    std::string scene_name = "scene" + std::to_string(level);
    lua.script_file("./assets/scripts/" + scene_name + ".lua");
    sol::table scene_data = lua[scene_name];

    // loading assets
    sol::table scene_assets = scene_data["assets"];
    int asset_index = 0;
    while (true) {
        sol::optional<sol::table> asset_check = scene_assets[asset_index];
        if (asset_check == sol::nullopt) {
            break;
        } else {
            sol::table scene_asset = scene_assets[asset_index];
            std::string type = scene_asset["type"];
            if (type == "texture") {
                _asset_manager->addTexture(
                    scene_asset["id"],
                    scene_asset["file"]
                );
            }  else if (type == "font") {
                _asset_manager->addFont(
                    scene_asset["id"], 
                    scene_asset["file"],
                    scene_asset["size"]
                );
            }
        }
        ++asset_index;
    }

    //loading map
    sol::table scene_map = scene_data["map"];
    map = new Map(
        scene_map["texture_id"], 
        scene_map["scale"], 
        scene_map["tile_size"]
    );
    map->loadMap(
        scene_map["file"],
        scene_map["width"],
        scene_map["height"]
    );

    //load entities and components
    sol::table scene_entities = scene_data["entities"];
    int entity_index = 0;
    while (true) {
        //check if entity at given index exists
        sol::optional<sol::table> entity_check = scene_entities[entity_index];
        if (entity_check == sol::nullopt) {
            break;
        } else {
            //store entity 
            sol::table scene_entity = scene_entities[entity_index];
            Entity& entity = manager.addEntity(scene_entity["name"], static_cast<LAYERS>(scene_entity["layer"]));

            //check if component exists for entity 

            //transform
            sol::optional<sol::table> entity_transform_check = scene_entity["components"]["transform"];
            if(entity_transform_check != sol::nullopt){
                entity.addComponent<TransformComponent>(
                    scene_entity["components"]["transform"]["x"],
                    scene_entity["components"]["transform"]["y"],
                    scene_entity["components"]["transform"]["velocity_x"],
                    scene_entity["components"]["transform"]["velocity_y"],
                    scene_entity["components"]["transform"]["width"], 
                    scene_entity["components"]["transform"]["height"],
                    scene_entity["components"]["transform"]["scale"]
                );
            }

            //sprite
            sol::optional<sol::table> entity_sprite_check = scene_entity["components"]["sprite"];
            if(entity_sprite_check != sol::nullopt){
                std::string asset_texture_id = scene_entity["components"]["sprite"]["asset_texture_id"];
                bool animated = scene_entity["components"]["sprite"]["animated"];
                if(animated){
                    entity.addComponent<SpriteComponent>(
                        asset_texture_id,
                        scene_entity["components"]["sprite"]["frames"],
                        scene_entity["components"]["sprite"]["speed"],
                        scene_entity["components"]["sprite"]["directed"],
                        scene_entity["components"]["sprite"]["fixed"]
                    );
                } else {
                    entity.addComponent<SpriteComponent>(
                        asset_texture_id
                    );
                }
            }

            //collider
            sol::optional<sol::table> entity_collider_check = scene_entity["components"]["collider"];
            if(entity_collider_check != sol::nullopt){
                std::string collider_tag = scene_entity["components"]["collider"]["tag"];      
                entity.addComponent<ColliderComponent>(
                   collider_tag
                );
            }

            //projectile_emitter
            sol::optional<sol::table> entity_projectile_emitter_check = scene_entity["components"]["projectile_emitter"];
            if(entity_projectile_emitter_check != sol::nullopt && entity_transform_check != sol::nullopt){
                Entity& projectile = manager.addEntity("projectile", PROJECTILE_LAYER);
                
                std::string asset_texture_id = scene_entity["components"]["projectile_emitter"]["asset_texture_id"];
                float parent_entity_x = scene_entity["components"]["transform"]["x"];
                float parent_entity_y = scene_entity["components"]["transform"]["y"];
                int parent_entity_width = scene_entity["components"]["transform"]["width"];
                int parent_entity_height = scene_entity["components"]["transform"]["height"];

                projectile.addComponent<TransformComponent>(
                    parent_entity_x + (parent_entity_width / 2),
                    parent_entity_y + (parent_entity_height / 2),
                    0,
                    0,
                    scene_entity["components"]["projectile_emitter"]["width"],
                    scene_entity["components"]["projectile_emitter"]["height"],
                    1
                );

                projectile.addComponent<SpriteComponent>(
                    asset_texture_id
                );
                
                projectile.addComponent<ProjectileEmitterComponent>(
                   scene_entity["components"]["projectile_emitter"]["speed"],
                   scene_entity["components"]["projectile_emitter"]["range"],
                   scene_entity["components"]["projectile_emitter"]["angle"],
                   scene_entity["components"]["projectile_emitter"]["loop"]
                );

                projectile.addComponent<ColliderComponent>(
                    "PROJECTILE"
                );
            }

            //input
            sol::optional<sol::table> entity_input_check = scene_entity["components"]["input"];
            if(entity_input_check != sol::nullopt){
                entity.addComponent<PlayerInputComponent>(
                    scene_entity["components"]["input"]["speed"],
                    scene_entity["components"]["input"]["keyboard"]["up"],
                    scene_entity["components"]["input"]["keyboard"]["down"],
                    scene_entity["components"]["input"]["keyboard"]["left"],
                    scene_entity["components"]["input"]["keyboard"]["right"],
                    scene_entity["components"]["input"]["keyboard"]["space"]
                );
            }

            //label
            sol::optional<sol::table> entity_label_check = scene_entity["components"]["label"];
            if(entity_label_check != sol::nullopt){
                entity.addComponent<LabelComponent>(
                    scene_entity["components"]["label"]["x"],
                    scene_entity["components"]["label"]["y"],
                    scene_entity["components"]["label"]["text"],
                    scene_entity["components"]["label"]["font"],
                    SDL_Color{
                        scene_entity["components"]["label"]["color"]["r"],
                        scene_entity["components"]["label"]["color"]["g"],
                        scene_entity["components"]["label"]["color"]["b"],
                        scene_entity["components"]["label"]["color"]["a"]
                    }
                );
            }
        }
        ++entity_index;
    }
    player = manager.getEntityByName("player");
    #ifdef DEBUG
    fps_label = manager.getEntityByName("fps_label");
    manager.listEntities(); 
    #endif // DEBUG         
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

#ifdef DEBUG
    LabelComponent* label = fps_label->getComponent<LabelComponent>();
    label->setLabelText(std::to_string(delta_time), "charriot");
#endif  // DEBUG

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
    TransformComponent* player_position = player->getComponent<TransformComponent>();

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
    switch (collision) {
        case TARGET_COLLISION:
            nextLevel(1);
            break;
        case PLAYER_ENEMY_COLLISION:
        case PLAYER_PROJECTILE_COLLSION:
            gameOver();
            break;
        default:
            break;
    }
}

void Engine::nextLevel(int level) {
    std::cout << "Loading next level\n";
    _loop = false;
}

void Engine::gameOver() {
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
