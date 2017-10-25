#pragma once
#include "ofMain.h"

class Bullet {
public:
	float x;
	float y;
	int height;
	int width;
	ofColor color;
	float xVelocity;
	Bullet();
	Bullet(float x, float y, int width, int height, ofColor color);
	void draw();
	void animate();
};