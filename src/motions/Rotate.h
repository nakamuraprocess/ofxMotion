#pragma once
#include "MotionTransformBase.h"

class Rotate : public MotionTransformBase {
public:
	void update(const float currentTime) {
		if (parameter.state == RUNNING) {
			float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
				parameter.state = DONE;
			});

			degrees = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, degreesStart, degreesEnd, parameter.easing);
		}
	}

	void startRotate(float distance, float duration, ofxeasing::function easing) {
		degreesStart = degrees;
		degreesEnd = degrees + distance;
		parameter.durationTime = duration;
		parameter.startTime = ofGetElapsedTimef();
		parameter.easing = easing;
		parameter.state = RUNNING;
	}

	void startRotate(float degreesStart, float degreesEnd, float duration, ofxeasing::function easing) {
		this->degreesStart = degreesStart;
		this->degreesEnd = degreesEnd;
		parameter.durationTime = duration;
		parameter.startTime = ofGetElapsedTimef();
		parameter.easing = easing;
		parameter.state = RUNNING;
	}
};