#pragma once
#include "MotionTransformBase.h"

class Rotate : public MotionTransformBase {
public:

	Rotate(string str) {
		name = str;
	}

	void update(const float currentTime) {
		if (parameter.state == RUNNING) {
			float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
				parameter.state = DONE;
			});

			degrees = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, degreesStart, degreesEnd, parameter.easing);
		}
		if (parameter.state == DONE && bLoop) {
			reStart();
		}
	}

	void start(float degreesEnd, float duration, ofxeasing::function easing) {
		this->degreesEnd = degreesEnd;
		parameter.durationTime = duration;
		parameter.startTime = ofGetElapsedTimef();
		parameter.easing = easing;
		parameter.state = RUNNING;
	}

	void start(float degreesStart, float degreesEnd, float duration, ofxeasing::function easing) {
		this->degreesStart = degreesStart;
		this->degreesEnd = degreesEnd;
		parameter.durationTime = duration;
		parameter.startTime = ofGetElapsedTimef();
		parameter.easing = easing;
		parameter.state = RUNNING;
	}

	void reStart() {
		parameter.startTime = ofGetElapsedTimef();
		parameter.state = RUNNING;
	}

private:
	bool bLoop;
};