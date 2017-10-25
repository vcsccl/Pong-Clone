#include "Bullet.h"
#include "ofMain.h"

Bullet::Bullet() {
	x = 0;
	y = 0;
	width = 10;
	height = 5;
	color = ofColor(0, 0, 0);
}

Bullet::Bullet(float x, float y, int width, int height, ofColor color) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->color = color;
}

void Bullet::draw() {
	ofDrawRectangle(x, y, width, height);
}

void Bullet::animate() {
	this->x += 10;
}
