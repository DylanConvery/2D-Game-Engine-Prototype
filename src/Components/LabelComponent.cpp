#include "LabelComponent.hpp"

LabelComponent::LabelComponent(int x, int y, std::string text, std::string font, SDL_Color color) : _position{x, y},
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
	SDL_FreeSurface(surface);
	SDL_QueryTexture(_texture, nullptr, nullptr, &_position.w, &_position.h);
}

void LabelComponent::initialize() {}

void LabelComponent::update(float delta_time) {}

void LabelComponent::render() {
	FontManager::draw(_texture, _position);
}