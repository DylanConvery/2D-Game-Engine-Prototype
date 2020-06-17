#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>

class Collision{
	public:
		static bool checkCollision(const SDL_Rect& rect_a, const SDL_Rect& rect_b);
};

#endif // !COLLISION_H