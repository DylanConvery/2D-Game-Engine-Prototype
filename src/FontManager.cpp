#include "FontManager.hpp"

TTF_Font* FontManager::loadFont(std::string path, int font_size){
	return TTF_OpenFont(path.c_str(), font_size);
}

void FontManager::draw(SDL_Texture* texture, SDL_Rect destination){
	SDL_RenderCopy(Engine::_renderer, texture, nullptr, &destination);
}
