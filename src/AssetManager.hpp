#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include "./TextureManager.hpp"
#include "./EntityManager.hpp"

class AssetManager {
   public:
    AssetManager(EntityManager* manager);
    ~AssetManager();
    void clear();
    void addTexture(std::string textureID, std::string path);
    SDL_Texture* getTexture(std::string textureID);
   private:
    EntityManager* _manager;
    std::map<std::string, SDL_Texture*> _textures;
};

#endif  // !ASSETMANAGER_H