#pragma once

#include "ofMain.h"
#include "ofxMotion.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void startMove(int index, int xDirMin, int xDirMax, int yDirMin, int yDirMax);
		void mouseReleased(int x, int y, int button);
		
		static const int itemMaxSize = 40;
		ofImage imageItems[itemMaxSize];
		ofImage imagePanels[itemMaxSize];
		ofImage imageClose;
		ofxMotion motions[itemMaxSize];
		ofxMotion motionPanel;
		ofxMotion motionModal;
		ofxMotion motionClose;
		glm::vec2 posInit[itemMaxSize];
		float sizeInit[itemMaxSize];

		ofRectangle rectMoveArea;
		float margin;
		float xCanMove;
		float yCanMove;

		bool bStateDisplayPanel = false;

		float now, delta, fps;
};
