#include "./TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(std::string path) {
    //load image
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        std::cerr << "[ERROR] Unable to load image " << path << "! SDL_image error: " << IMG_GetError() << "\n";
        return nullptr;
    }

    //create texture from surface pixels
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::_renderer, surface);
    if (texture == nullptr) {
        std::cerr << "[ERROR] Unable to create texture from " << path << "! SDL_Error: " << SDL_GetError() << "\n";
        SDL_FreeSurface(surface);
        return nullptr;
    }

    //free surface after loading it into our texture
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect destination, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Engine::_renderer, texture, &source, &destination, 0, nullptr, flip);
}
