#ifndef LABELCOMPONENT_H
#define LABELCOMPONENT_H

#include "../AssetManager.hpp"
#include "../Engine.hpp"
#include "../EntityManager.hpp"

class LabelComponent : public Component {
   public:
    LabelComponent(int x, int y, std::string text, std::string font, SDL_Color color);
    void initialize() override;
    void update(float delta_time) override;
    void render() override;
    void setLabelText(std::string text, std::string font);

   private:
    SDL_Rect _position;
    std::string _text;
    std::string _font;
    SDL_Color _color;
    SDL_Texture* _texture;
};

#endif  // !LABELCOMPONENT_H