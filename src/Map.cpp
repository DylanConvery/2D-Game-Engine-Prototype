#include <Map.hpp>

Map::Map(std::string texture_id, int scale, int width, int height) : _texture_id(texture_id), _scale(scale), _width(width), _height(height) {}

Map::~Map() {}

void Map::loadMap(std::string file_path, int map_size_x, int map_size_y) {

}

void Map::addTile(int source_x, int source_y, int x, int y) {
    Entity& tile(manager.addEntity("tile"));
    tile.addComponent<TileComponent>(source_x, source_y, x, y, _width, _height, _scale, _texture_id);
}