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
}
