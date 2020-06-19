#ifndef MAP_H
#define MAP_H

#include <string>
#include "Engine.hpp"
#include "EntityManager.hpp"
#include <fstream>
#include "constants.hpp"
#include "Components/TileComponent.hpp"

extern EntityManager manager;

class Map{
	public:
		Map(std::string texture_id, int scale, int tile_size);
		~Map();
		void loadMap(std::string file_path, int map_size_x, int map_size_y);
		void addTile(int source_x, int source_y, float destination_x, float destination_y);
	private:
		static int _tile_count;
		std::string _texture_id;
		int _tile_size;
		int _scale;
};

#endif // !MAP_H