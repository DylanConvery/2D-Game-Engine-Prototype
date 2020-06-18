#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "EntityManager.hpp"

class EntityManager;

class AssetManager {
   public:
    AssetManager(EntityManager* manager);
    ~AssetManager();
    void clear();
    void addTexture(std::string textureID, std::string path);
	void addFont(std::string fontID, std::string path);
    SDL_Texture* getTexture(std::string textureID);
	TTF_Font* getFont(std::string fontID);
   private:
    EntityManager* _manager;
    std::map<std::string, SDL_Texture*> _textures;
    std::map<std::string, TTF_Font*> _fonts;

};

#endif  // !ASSETMANAGER_H