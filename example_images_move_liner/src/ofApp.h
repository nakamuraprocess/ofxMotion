#pragma once

#include "ofMain.h"
#include "ofxMotion2D.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		enum MoveDirection {
			LEFT = 0,
			RIGHT = 1,
			NONE = 2
		};

		float now, delta, fps;

		static const int fishMaxSize = 15;
		ofImage imageFish[fishMaxSize];
		ofxMotion2D motion[fishMaxSize];
		glm::vec2 posFish[fishMaxSize];
		MoveDirection moveDirection[fishMaxSize];
};
