#include "Paddle.h"
#include "ofMain.h"
#include "Ball.h"

Paddle::Paddle() {
	x = 50;
	y = ofGetHeight() / 2;
	width = 50;
	height = 200;
	color = ofColor(255);
}

Paddle::Paddle(float x, float y, float width, float height, ofColor color) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->color = color;
}

void Paddle::draw() {
	ofSetColor(color);
	ofDrawRectangle(x, y, width, height);
}

void Paddle::enemyMove(int ballX, int ballY, bool hit) {
	if (hit == false) {
		if (ballY > this->y + 100) {
			this->y += ballX / 500;
		}
		else if (ballY < this->y + 100) {
			this->y -= ballX / 500;
		}
	}
}