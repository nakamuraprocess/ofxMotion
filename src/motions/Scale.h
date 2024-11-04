#pragma once
#include "MotionTransformBase.h"

class Scale : public MotionTransformBase {
public:

	Scale(string str) {
		name = str;
	}

	void update(const float currentTime) {
		if (parameter.state == RUNNING) {
			float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
				parameter.state = DONE;
			});

			scale.x = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, scaleStart.x, scaleEnd.x, parameter.easing);
			scale.y = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, scaleStart.y, scaleEnd.y, parameter.easing);
		}
	}

	void start(vec2 scaleEnd, float duration, ofxeasing::function easing) {
		this->scaleEnd = scaleEnd;
		parameter.durationTime = duration;
		parameter.startTime = ofGetElapsedTimef();
		parameter.easing = easing;
		parameter.state = RUNNING;
	}

	void start(vec2 scaleStart, vec2 scaleEnd, float duration, ofxeasing::function easing) {
		this->scaleStart = scaleStart;
		this->scaleEnd = scaleEnd;
		parameter.durationTime = duration;
		parameter.startTime = ofGetElapsedTimef();
		parameter.easing = easing;
		parameter.state = RUNNING;
	}
};