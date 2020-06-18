#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "Engine.hpp"

class FontManager {
   public:
    static TTF_Font* loadFont(std::string path, int font_size);
	static void draw(SDL_Texture* texture, SDL_Rect destination);
};

#endif  // !FONTMANAGER_H