#ifndef ANIMATION_H
#define ANIMATION_H

class Animation{
	public:
		Animation();
		Animation(unsigned index, unsigned frames, unsigned speed);

		unsigned _index;
		unsigned _frames;
		unsigned _speed;
};

#endif