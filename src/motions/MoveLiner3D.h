#pragma once
#include "MotionTransformBase3D.h"

class MoveLiner3D : public MotionTransformBase3D {
public:
	void update(const float currentTime) {
		this->currentTime = currentTime;
		if (parameter.state == RUNNING) {
			float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
				parameter.state = DONE;
				});

			pos.x = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, posStart.x, posEnd.x, parameter.easing);
			pos.y = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, posStart.y, posEnd.y, parameter.easing);
			pos.z = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, posStart.z, posEnd.z, parameter.easing);
		}
	}

	void startMoveLiner(vec3 distance, float duration, float delay, ofxeasing::function easing) {
		posStart = pos;
		posEnd = pos + distance;
		parameter.startTime = currentTime + delay;
		parameter.durationTime = duration;
		parameter.easing = easing;
		parameter.state = RUNNING;
	}

	void startMoveLiner(vec3 posStart, vec3 posEnd, float duration, float delay, ofxeasing::function easing) {
		this->posStart = posStart;
		this->posEnd = posEnd;
		parameter.startTime = currentTime + delay;
		parameter.durationTime = duration;
		parameter.easing = easing;
		parameter.state = RUNNING;
	}
};