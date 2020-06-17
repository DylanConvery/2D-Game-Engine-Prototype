#include "TileComponent.hpp"

TileComponent::TileComponent(
    int source_x,
    int source_y,
    int destination_x,
    int destination_y,
    int tile_size,
    int tile_scale,
    std::string asset_texture_id) {
    _texture = Engine::_asset_manager->getTexture(asset_texture_id);

    _source.x = source_x;
    _source.y = source_y;
    _source.w = tile_size;
    _source.h = tile_size;

    _destination.x = destination_x;
    _destination.y = destination_y;
    _destination.w = tile_size * tile_scale;
    _destination.h = tile_size * tile_scale;

    _position.x = destination_x;
    _position.y = destination_y;

#ifdef DEBUG
    _tile_container_visible = false;
#endif  // DEBUG
}

TileComponent::~TileComponent() {
    SDL_DestroyTexture(_texture);
}

void TileComponent::update(float delta_time) {
    _destination.x = _position.x - Engine::_camera.x;
    _destination.y = _position.y - Engine::_camera.y;
}

void TileComponent::render() {
    TextureManager::draw(_texture, _source, _destination, SDL_FLIP_NONE);
#ifdef DEBUG
    if (_tile_container_visible) {
		SDL_SetRenderDrawBlendMode(Engine::_renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(Engine::_renderer, 0, 255, 0, 100);
        SDL_RenderDrawRect(Engine::_renderer, &_destination);
    }
#endif  // DEBUG
}

#ifdef DEBUG
void TileComponent::showTileContainer() {
    _tile_container_visible = true;
}

void TileComponent::hideTileContainer() {
    _tile_container_visible = false;
}
#endif  // DEBUG