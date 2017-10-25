#include "Ball.h"
#include "ofMain.h"
#include "ofApp.h"

Ball::Ball() {
	x = ofGetWidth();
	y = ofGetHeight();
	size = 50;
	color = ofColor(255);
}

Ball::Ball(float x, float y, float size, ofColor color, float xVelocity, float yVelocity) {
	this->x = x;
	this->y = y;
	this->size = size;
	this->color = color;
	this->xVelocity = xVelocity;
	this->yVelocity = yVelocity;
}

void Ball::draw() {
	ofSetColor(color);
	ofDrawCircle(x, y, size);
}

void Ball::move() {
	this->x += xVelocity;
	this->y += yVelocity;
}

void Ball::bounce(int enemyPaddleX, int enemyPaddleY, int paddleY, ofSoundPlayer bumper) {
	if (this->isScore(paddleY) == true) {
		this->xVelocity *= -1;
		bumper.play();
	}
	if (enemyBounce(enemyPaddleX, enemyPaddleY) == true) {
		this->xVelocity *= -1.05;
		bumper.play();
	}
	if (this->y <= 25) {
		this->yVelocity *= -1;
	}
	if (this->y >= ofGetScreenHeight() - 25) {
		this->yVelocity *= -1;
	}
}

bool Ball::offScreenLeft() {
	if (this->x < -300) {
		return true;
	}
}

bool Ball::offScreenRight() {
	if (this->x > ofGetWidth() + 25) {
		return true;
	}
}

void Ball::reset() {
	this->x = ofRandom(ofGetWidth() / 2 - 100, ofGetWidth() / 2 + 100);
	this->y = ofRandom(ofGetHeight() / 2 - 200, ofGetHeight() / 2 + 200);
	this->xVelocity = 3;
	this->yVelocity = -3;
}

bool Ball::isScore(int paddleY) {
	if (this->x <= 125 && this->x >= 115 && this->y >= paddleY && this->y <= paddleY + 200) {
		return true;
	}
}

bool Ball::enemyBounce(int enemyPaddleX, int enemyPaddleY) {
	if (this->x >= ofGetWidth() - 150 && this->x <= ofGetWidth() - 135 && this->y > enemyPaddleY && this->y < enemyPaddleY + 200) {
		return true;
	}
}

