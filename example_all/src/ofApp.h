#pragma once

#include "ofMain.h"
#include "ofxMotion.h"

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


		ofxMotion motionMoveLiner[6];
		ofxMotion motionColor;
		ofxMotion motionRadialNoise[5];
		ofxMotion motionMoveCurve[6];
		ofxMotion motionRotate[3];
	
		float timerLapTime = 0.0;
		float timerSleepTime = 3.0;
};