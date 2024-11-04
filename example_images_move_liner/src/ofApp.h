#pragma once

#include "ofMain.h"
#include "ofxMotion.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		static const int fishMaxSize = 15;
		ofImage imageFish[fishMaxSize];
		ofxMotion motion[fishMaxSize];
		vec2 posFish[fishMaxSize];
		
};
