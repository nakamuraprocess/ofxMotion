#pragma once
#include "MotionColor.h"

class ColorGradation : public MotionColor {
public:
	void update(const float currentTime) {
		this->currentTime = currentTime;
		if (parameter.state == RUNNING) {
			float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
				parameter.state = DONE;
				});

			unsigned short r = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, colorStart.r, colorEnd.r, parameter.easing);
			unsigned short g = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, colorStart.g, colorEnd.g, parameter.easing);
			unsigned short b = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, colorStart.b, colorEnd.b, parameter.easing);
			unsigned short a = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, colorStart.a, colorEnd.a, parameter.easing);
			color.set(r, g, b, a);
		}
	}

	void startColorGradation(ofColor colorEnd, float duration, ofxeasing::function easing) {
		this->colorEnd = colorEnd;
		colorStart = color;
		parameter.durationTime = duration;
		parameter.startTime = currentTime;
		parameter.easing = easing;
		parameter.state = RUNNING;
	}


	void startColorGradation(ofColor colorStart, ofColor colorEnd, float duration, ofxeasing::function easing) {
		this->colorStart = colorStart;
		this->colorEnd = colorEnd;
		parameter.durationTime = duration;
		parameter.startTime = currentTime;
		parameter.easing = easing;
		parameter.state = RUNNING;
	}
};