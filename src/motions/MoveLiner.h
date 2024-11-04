#pragma once
#include "MotionTransformBase.h"

class MoveLiner : public MotionTransformBase {
public:

	MoveLiner(string str) {
		name = str;
	}

	void update(const float currentTime) {
		if (parameter.state == RUNNING) {
			float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
				parameter.state = DONE;
			});

			pos.x = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, posStart.x, posEnd.x, parameter.easing);
			pos.y = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, posStart.y, posEnd.y, parameter.easing);
		}
	}

	void start(vec2 distance, float duration, float delay, ofxeasing::function easing) {
		posStart = pos;
		posEnd = pos + distance;
		parameter.startTime = ofGetElapsedTimef() + delay;
		parameter.durationTime = duration;
		parameter.easing = easing;
		parameter.state = RUNNING;
	}

	void start(vec2 posStart, vec2 posEnd, float duration, float delay, ofxeasing::function easing) {
		posStart = posStart;
		this->posEnd = posEnd;
		parameter.startTime = ofGetElapsedTimef() + delay;
		parameter.durationTime = duration;
		parameter.easing = easing;
		parameter.state = RUNNING;
	}
};