#ifndef ANIMATION_CONTROLLER_H
#define ANIMATION_CONTROLLER_H

#include "constants.hpp"
class AnimationController {

private:
	int w; //interval
	int h;
	int index;
	int rate;
	int n;
	int offset;

public:
	AnimationController(int w0, int h0, int rate0, int n0);
	void updateFrame();
	void setAnimation(int offset, int n1);
	int getW();
	int getH();
	int getIndex();
	void setIndex(int i);

};


#endif