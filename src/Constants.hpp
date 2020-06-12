#ifndef CONSTANTS_H
#define CONSTANTS_H

//16:9 ratio
const unsigned WINDOW_WIDTH = 800;
const unsigned WINDOW_HEIGHT = 640;

//16.6 milliseconds
const unsigned FRAME_RATE = 60; 
const unsigned FRAME_TIME = 1000 / FRAME_RATE;

enum layers{
	TILEMAP_LAYER,
	VEGETATION_LAYER,
	ENEMY_LAYER,
	PLAYER_LAYER,
	PROJECTILE_LAYER,
	UI_LAYER
};

const unsigned NUM_LAYERS = 6;

#endif // !CONSTANTS_H#define CONSTANTS_H
