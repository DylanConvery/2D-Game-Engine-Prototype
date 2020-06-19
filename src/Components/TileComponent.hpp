#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include "../EntityManager.hpp"
#include "../TextureManager.hpp"
#include <SDL2/SDL.h>
#include "../../lib/glm/glm.hpp"
#include <string>

class TileComponent : public Component{
	public:
		TileComponent(int source_x, int source_y, float destination_x, float destination_y, int tile_size, int tile_scale, std::string asset_texture_id);
		~TileComponent();

		void update(float delta_time) override;
		void render() override;

#ifdef DEBUG
		void showTileContainer();
		void hideTileContainer();
#endif // DEBUG
		
		SDL_Texture* _texture;
		SDL_Rect _source;
		SDL_FRect _destination;
		glm::vec2 _position;
	private:
	#ifdef DEBUG
		bool _tile_container_visible;
	#endif // DEBUG
};

#endif // !TILECOMPONENT_H