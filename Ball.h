#pragma once
#include "ofMain.h"

class Ball {
public:
	float x;
	float y;
	float size;
	ofColor color;
	float xVelocity;
	float yVelocity;
	Ball();
	Ball(float x, float y, float size, ofColor color, float velocity, float yVelocity);
	void draw();
	void move();
	void bounce(int enemyPaddleX, int enemyPaddleY, int paddleY, ofSoundPlayer bumper);
	bool offScreenLeft();
	bool offScreenRight();
	void reset();
	bool isScore(int paddleY);
	bool enemyBounce(int enemyPaddleX, int enemyPaddleY);
};
