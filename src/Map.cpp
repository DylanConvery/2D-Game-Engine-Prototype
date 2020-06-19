#include "Map.hpp"
int Map::_tile_count = 0;

Map::Map(std::string texture_id, int scale, int tile_size) : _texture_id(texture_id), _scale(scale), _tile_size(tile_size) {}

Map::~Map() {}

//read our map file and load the appropriate tile from our tilesheet
void Map::loadMap(std::string file_path, int map_size_x, int map_size_y) {
    std::fstream map_file;
    map_file.open(file_path);
    for(int x = 0; x< map_size_y; x++){
        for(int y = 0; y < map_size_x; y++){
            char ch;
            map_file.get(ch);
            int source_y = atoi(&ch) * _tile_size;
            map_file.get(ch);
            int source_x = atoi(&ch) * _tile_size;
            addTile(source_x, source_y, y * (_scale * _tile_size), x * (_scale * _tile_size));
            map_file.ignore();
        }
    }
    map_file.close();
}

//adds new tile to scene
void Map::addTile(int source_x, int source_y, float destination_x, float destination_y) {
    Entity& tile(manager.addEntity("tile_" + std::to_string(_tile_count++), VEGETATION_LAYER));
    tile.addComponent<TileComponent>(source_x, source_y, destination_x, destination_y, _tile_size, _scale, _texture_id);
}