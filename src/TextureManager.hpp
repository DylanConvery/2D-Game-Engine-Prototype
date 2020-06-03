#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "./Engine.hpp"
#include <iostream>

class TextureManager {
   public:
    static SDL_Texture* loadTexture(std::string path);
    static void draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect destination, SDL_RendererFlip flip);
};

#endif  // !TEXTUREMANAGER_H