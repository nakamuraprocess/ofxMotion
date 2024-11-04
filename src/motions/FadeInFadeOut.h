#pragma once
#include "MotionColorBase.h"

class FadeInFadeOut : public MotionColorBase {
private:
	float durationFadeIn;
	float durationChroma;
	float durationfadeOut;

public:
	
	FadeInFadeOut(string str) {
		name = str;
	}

	void update(const float currentTime) {
		if (parameter.state == RUNNING) {
			float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
				parameter.state = DONE;
			});

			unsigned short a;

			if (time < durationFadeIn) {
				a = ofxeasing::map_clamp(time, 0.0, durationFadeIn, colorStart.a, colorEnd.a, parameter.easing);
			}
			else if (time < durationChroma) {
				a = colorEnd.a;
			}
			else if (time < durationfadeOut) {
				a = ofxeasing::map_clamp(time, durationChroma + durationFadeIn, durationfadeOut, colorEnd.a, colorStart.a, parameter.easing);
			}
			
			color.set(color.r, color.g, color.b, a);
		}
	}

	void start(int alphaStart, int alphaEnd, float durationFadeIn, float durationChroma, float durationfadeOut, ofxeasing::function easing) {
		parameter.durationTime = durationFadeIn + durationChroma + durationfadeOut;
		parameter.startTime = ofGetElapsedTimef();
		parameter.easing = easing;
		parameter.state = RUNNING;
		colorStart.a = alphaStart;
		colorEnd.a = alphaEnd;
		this->durationFadeIn = durationFadeIn;
		this->durationChroma = durationChroma + durationFadeIn;
		this->durationfadeOut = durationfadeOut + durationChroma + durationFadeIn;
	}

	void start(int alphaEnd, float durationfadeOut, ofxeasing::function easing) {
		parameter.durationTime = durationfadeOut;
		parameter.startTime = ofGetElapsedTimef();
		parameter.easing = easing;
		parameter.state = RUNNING;
		colorStart.a = color.a;
		colorEnd.a = alphaEnd;
		this->durationFadeIn = durationfadeOut;
	}
};