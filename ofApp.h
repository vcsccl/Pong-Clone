#pragma once
#include "ofMain.h"
#include "Paddle.h"
#include "Ball.h"
#include "Bullet.h"

class ofApp : public ofBaseApp{

	public:
		const int START_SCREEN = 0;
		const int GAME_SCREEN = 1;
		const int GAME_OVER_SCREEN = 2;

		int gameState = START_SCREEN;

		int livesLeft = 2;
		int bulletsLeft = 0;
		int score = 0;

		ofBuffer highScore;
		ofFile highScoreFileIn;
		ofFile highScoreFileOut;
		ofImage bulletIcon;
		ofSoundPlayer bullet;
		ofSoundPlayer bumper;
		ofSoundPlayer bulletTally;
		ofSoundPlayer playerScore;
		ofSoundPlayer enemyScore;

		bool check1 = true;
		bool check2 = true;
		bool checkScore = true;

		ofTrueTypeFont font1;
		ofTrueTypeFont font2;
		ofTrueTypeFont font3;

		Paddle* mainPaddle;
		Paddle* enemyPaddle;
		Ball* mainBall;
		Bullet* mainBullet;

		void setup();
		void update();
		void draw();

		void drawStartScreen();
		void drawGameScreen();
		void drawGameOverScreen();
		void loadFont();
		void loadHighScore();
		void loadSound();
		bool isStartButton(int x, int y);
		bool isPlayButton(int x, int y);
		bool isHit();
		void drawLives();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
