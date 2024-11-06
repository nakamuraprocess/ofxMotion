#pragma once
#include "MotionColorBase.h"

class FadeInFadeOut : public MotionColorBase {
private:
	float durationFadeIn = 0.0f;
	float durationChroma = 0.0f;
	float durationfadeOut = 0.0f;

public:
	void update(const float currentTime) {
		if (parameter.state == RUNNING) {
			float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
				parameter.state = DONE;
				});

			unsigned short a;

			if (time < durationFadeIn) {
				a = ofxeasing::map_clamp(time, 0.0, durationFadeIn, colorStart.a, colorEnd.a, parameter.easing);
			}
			else if (time < durationFadeIn + durationChroma) {
				a = colorEnd.a;
			}
			else if (time < durationFadeIn + durationChroma + durationfadeOut) {
				a = ofxeasing::map_clamp(time, durationFadeIn + durationChroma, durationFadeIn + durationChroma + durationfadeOut, colorEnd.a, colorStart.a, parameter.easing);
			}
			
			color.set(color.r, color.g, color.b, a);
		}
	}

	void startFadeInFadeOut(int alphaStart, int alphaEnd, float durationFadeIn, float durationChroma, float durationfadeOut, ofxeasing::function easing) {
		parameter.durationTime = durationFadeIn + durationChroma + durationfadeOut;
		parameter.startTime = ofGetElapsedTimef();
		parameter.easing = easing;
		parameter.state = RUNNING;
		colorStart.a = alphaStart;
		colorEnd.a = alphaEnd;
		this->durationFadeIn = durationFadeIn;
		this->durationChroma = durationChroma;
		this->durationfadeOut = durationfadeOut;
	}

	void startFadeOutForce(int alphaEnd, float durationfadeOut, ofxeasing::function easing) {
		parameter.durationTime = durationfadeOut;
		parameter.startTime = ofGetElapsedTimef();
		parameter.easing = easing;
		parameter.state = RUNNING;
		colorStart.a = color.a;
		colorEnd.a = alphaEnd;
		this->durationFadeIn = durationfadeOut;
	}
};