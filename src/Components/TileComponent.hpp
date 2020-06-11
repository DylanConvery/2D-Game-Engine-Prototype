#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include "../EntityManager.hpp"
#include "../TextureManager.hpp"
#include <SDL2/SDL.h>
#include "../../lib/glm/glm.hpp"
#include <string>

class TileComponent : public Component{
	public:
		TileComponent(int source_x, int source_y, int destination_x, int destination_y, int tile_size, int tile_scale, std::string asset_texture_id);
		~TileComponent();

		void update(float delta_time) override;
		void render() override;

		SDL_Texture* _texture;
		SDL_Rect _source;
		SDL_Rect _destination;
		glm::vec2 _position;
	private:
};

#endif // !TILECOMPONENT_H