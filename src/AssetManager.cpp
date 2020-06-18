#include "AssetManager.hpp"

AssetManager::AssetManager(EntityManager* manager) : _manager(manager) {}

AssetManager::~AssetManager() {}

//clears our asset manager
void AssetManager::clear() {
    _textures.clear();
	_fonts.clear();
}

//inserts a texture into asset manager
void AssetManager::addTexture(std::string textureID, std::string path) {
    _textures.emplace(textureID, TextureManager::loadTexture(path));
}

void AssetManager::addFont(std::string fontID, std::string path, int font_size) {
	_fonts.emplace(fontID, FontManager::loadFont(path, font_size));
}

//returns a pointer to a texture with matching textureID
SDL_Texture* AssetManager::getTexture(std::string textureID) {
    auto element = _textures.find(textureID);
    if(element == _textures.end()){
        std::cerr << "[ERROR] Texure not found\n";
        return nullptr;
    } else {
        return element->second;
    }
}

//returns a pointer to a font with matching fontID
TTF_Font* AssetManager::getFont(std::string fontID){
	auto element = _fonts.find(fontID);
	if(element == _fonts.end()){
		std::cerr << "[ERROR] Font not found\n";
		return nullptr;
	} else {
		return element->second;
	}
}