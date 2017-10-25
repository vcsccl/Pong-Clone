#include "ofApp.h"

void ofApp::setup(){
	ofSetBackgroundColor(0);
	loadFont();
	loadHighScore();
	loadSound();
	mainPaddle = new Paddle(50, ofGetHeight() / 2, 50, 200, ofColor(255));
	enemyPaddle = new Paddle(ofGetWidth() - 150, ofGetHeight() / 2, 50, 200, ofColor(255));
	mainBall = new Ball(ofRandom(ofGetWidth() / 2 - 50, ofGetWidth() / 2), ofRandom(ofGetHeight() / 2 - 50, ofGetHeight() / 2), 50, ofColor(255), 3, 3);
}

void ofApp::update(){
	if (gameState == GAME_SCREEN) {
		mainBall->move();
		mainBall->bounce(enemyPaddle->x, enemyPaddle->y, mainPaddle->y, bumper);
		enemyPaddle->enemyMove(mainBall-> x, mainBall->y, isHit());
		if (mainBall->isScore(mainPaddle->y) == true) {
			score++;
		}
		if (mainBullet != NULL) {
			mainBullet->animate();
			if (mainBullet->x > ofGetWidth() + 1000) {
				free(mainBullet);
				mainBullet = NULL;
			}
		}
		if (score != 0 && score % 10 == 0 && checkScore == true) {
			bulletsLeft++;
			bulletTally.play();
			checkScore = false;
		}
		if (score % 10 != 0) {
			checkScore = true;
		}	
		if (livesLeft < 0) {
			gameState = GAME_OVER_SCREEN;
		}
	}
}

void ofApp::draw(){
	if (gameState == START_SCREEN) {
		drawStartScreen();
	}
	else if (gameState == GAME_SCREEN) {
		drawGameScreen();
	}
	else if (gameState == GAME_OVER_SCREEN) {
		drawGameOverScreen();
	}
}

void ofApp::drawStartScreen() {
	if (check1 == true) {
		highScoreFileIn.open("highScore.txt");
		highScore = highScoreFileIn.readToBuffer();
		highScoreFileIn.close();
		check1 = false;
		check2 = true;
	}

	font1.drawString("Pong's Revenge", 150, 150);
	font2.drawString("START", ofGetWidth() / 2 - 150, ofGetHeight() / 2);
	font3.drawString("High Score: " + ofToString(highScore), ofGetWidth() / 2 - 175, ofGetHeight() - 100);
}

void ofApp::drawGameScreen() {
	ofHideCursor();
	font3.drawString(ofToString(bulletsLeft), 100, 100);
	font3.drawString("SCORE: " + ofToString(score), ofGetWidth() / 2 - 120, 100);

	mainPaddle->draw();
	enemyPaddle->draw();
	mainBall->draw();
	drawLives();
	bulletIcon.draw(50, 50, 5);
	
	if (mainBall->offScreenLeft() == true) {
		mainBall->reset();
		enemyScore.play();
		livesLeft--;
	}
	if (mainBall->offScreenRight() == true) {
		mainBall->reset();
		score += 100;
		playerScore.play();
		if (livesLeft < 4) {
			livesLeft++;
		}
	}

	if (mainBullet != NULL) {
		mainBullet->draw();
	}
}
void ofApp::drawGameOverScreen() {
	ofShowCursor();
	if (check2 == true) {
		if (score != 0 && score > stoi(ofToString(highScore))) {
			remove("highScore.txt");
			highScoreFileOut.open("highScore.txt", ofFile::WriteOnly);
			highScoreFileOut << score << endl;
			highScoreFileOut.close();
		}
		check2 = false;
		check1 = true;
	}
	if (score > stoi(ofToString(highScore))) {
		font2.drawString("NEW HIGH SCORE!", ofGetWidth() / 2 - 450, ofGetHeight() / 2 - 300);
	}
	font2.drawString("GAME OVER", ofGetWidth() / 2 - 300, ofGetHeight() / 2);
	font3.drawString("SCORE: " + ofToString(score), ofGetWidth() / 2 - 120, ofGetHeight() - 100);
	font3.drawString("PLAY AGAIN ", ofGetWidth() / 2 - 150, ofGetHeight() / 2 + 200);
}

void ofApp::loadFont() {
	font1.loadFont("font.ttf", 100);
	font2.loadFont("font.ttf", 50);
	font3.loadFont("font.ttf", 25);
	bulletIcon.loadImage("bulletIcon.png");
}

void ofApp::loadHighScore() {
	if (highScoreFileIn.doesFileExist("highScore.txt") == false) {
		highScoreFileIn.open("highScore.txt", ofFile::WriteOnly);
		highScoreFileIn << 0 << endl;
		highScoreFileIn.close();
	}
}

void ofApp::loadSound() {
	bullet.load("laser.mp3");
	enemyScore.load("enemyScore.mp3");
	bumper.load("bumper.mp3");
	bulletTally.load("enemyStall.mp3");
	playerScore.load("playerScore.mp3");
	bumper.setSpeed(1.5);
	bulletTally.setSpeed(1.5);
	bullet.setSpeed(1.5);
	playerScore.setSpeed(3);
}

bool ofApp::isStartButton(int x, int y) {
	if (x > ofGetWidth() / 2 - 150 && x < ofGetWidth() / 2 + 155 && y > ofGetHeight() / 2 - 50 && y < ofGetHeight() / 2) {
		return true;
	}
}

bool ofApp::isPlayButton(int x, int y) {
	if (x > ofGetWidth() / 2 - 155 && x < ofGetWidth() / 2 + 155 && y > ofGetHeight() / 2 + 155 && y < ofGetHeight() / 2 + 200) {
		return true;
	}
}

bool ofApp::isHit() {
	if (mainBullet != NULL && mainBullet->x > enemyPaddle->x && mainBullet->x < enemyPaddle->x + 50 && mainBullet->y > enemyPaddle->y && mainBullet->y < enemyPaddle->y + 200) {
		ofResetElapsedTimeCounter();
		return true;
	}
	else if (ofGetElapsedTimeMillis() > 1000) {
		return false;
	}
}

void ofApp::drawLives() {
	if (livesLeft == 4) {
		ofDrawCircle(ofGetWidth() - 190, 100, 15);
	}
	if (livesLeft >= 3 && livesLeft <= 4) {
		ofDrawCircle(ofGetWidth() - 160, 100, 15);
	}
	if (livesLeft >= 2 && livesLeft <= 4) {
		ofDrawCircle(ofGetWidth() - 130, 100, 15);
	}
	if (livesLeft >= 1 && livesLeft <= 4) {
		ofDrawCircle(ofGetWidth() - 100, 100, 15);
	}
}


void ofApp::keyPressed(int key){
}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){
		mainPaddle->y = y - 100;
}

void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button){
	if (gameState == START_SCREEN && isStartButton(x, y) == true) {
		gameState = GAME_SCREEN;
	}
	else if (gameState == GAME_OVER_SCREEN && isPlayButton(x, y) == true) {
		gameState = START_SCREEN;
		score = 0;
		bulletsLeft = 0;
		livesLeft = 2;
	}
	else if (gameState == 1) {
		if (bulletsLeft > 0) {
			bulletsLeft--;
			if (mainBullet == NULL) {
				mainBullet = new Bullet(125, ofGetMouseY(), 10, 5, ofColor(0));
				bullet.play();
			}
		}
	}
}

void ofApp::mouseReleased(int x, int y, int button){
}

void ofApp::mouseEntered(int x, int y){

}

void ofApp::mouseExited(int x, int y){

}

void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}