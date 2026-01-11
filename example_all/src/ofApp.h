#pragma once

#include "ofMain.h"
#include "ofxMotion2D.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void timer(float now);

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

		ofImage image;
		ofTrueTypeFont font;
		
		ofxMotion2D motionMoveLiner[6];
		ofxMotion2D motionMoveCurve[6];
		ofxMotion2D motionColor;
		ofxMotion2D motionSignedNoise[5];
		ofxMotion2D motionRotate[5];
		ofxMotion2D motionScale[3];
		ofxMotion2D motionMoveRadial[10];
		ofxMotion2D motionImage;
		ofxMotion2D motionText[10];
	
		float now, delta, fps;
		float timerLapTime = 0.0;
		float timerSleepTime = 3.0;
};
