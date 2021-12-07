#ifndef ANIMATION_CONTROLLER_H
#define ANIMATION_CONTROLLER_H

class AnimationController {

private:
	int w; //interval
	int h;
	int index;
	int rate;
	int n;
	int offset;


public:
	AnimationController();
	void updateFrame();
	void setAnimation(int offset, int n1);

};


#ifndef