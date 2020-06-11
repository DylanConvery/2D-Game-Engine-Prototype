#ifndef MAP_H
#define MAP_H

#include <string>
#include "Engine.hpp"
#include "EntityManager.hpp"

extern EntityManager manager;

class Map{
	public:
		Map(std::string texture_id, int scale, int width, int height);
		~Map();
		void loadMap(std::string file_path, int map_size_x, int map_size_y);
		void addTile(int source_x, int source_y, int x, int y);
	private:
		std::string _texture_id;
		int _scale;
		int _width;
		int _height;
};

#endif // !MAP_H