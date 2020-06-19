#include "LabelComponent.hpp"

LabelComponent::LabelComponent(float x, float y, std::string text, std::string font, SDL_Color color) : _position{x, y},
                                                                                                    _text(text),
                                                                                                    _font(font),
                                                                                                    _color(color) {
    setLabelText(text, font);
}

void LabelComponent::setLabelText(std::string text, std::string font) {
    SDL_Surface* surface = TTF_RenderText_Blended(Engine::_asset_manager->getFont(font), text.c_str(), _color);
    if (surface == nullptr) {
        std::cerr << "[ERROR] Unable to render text surface ! SDL_ttf error: " << TTF_GetError() << "\n";
    }
    _texture = SDL_CreateTextureFromSurface(Engine::_renderer, surface);
    if (_texture == nullptr) {
        std::cerr << "[ERROR] Unable to create texture from rendered text! SDL_Error: " << SDL_GetError() << "\n";
    } else {
        _position.w = surface->w;
        _position.h = surface->h;
    }
	SDL_FreeSurface(surface);
}

void LabelComponent::initialize() {}

void LabelComponent::update(float delta_time) {}

void LabelComponent::render() {
	FontManager::draw(_texture, _position);
}