#pragma once
#include "MotionTransformBase.h"

class Scale : public MotionTransformBase {
public:
	void update(const float currentTime) {
		this->currentTime = currentTime;
		if (parameter.state == RUNNING) {
			float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
				parameter.state = DONE;
				});

			scale.x = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, scaleStart.x, scaleEnd.x, parameter.easing);
			scale.y = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, scaleStart.y, scaleEnd.y, parameter.easing);

			width = widthInitial * scale.x;
			height = heightInitial * scale.y;
		}
	}

	void startScale(vec2 scaleEnd, float duration, float delay, ofxeasing::function easing) {
		scaleStart = scale;
		this->scaleEnd = scale + scaleEnd;
		parameter.durationTime = duration;
		parameter.startTime = currentTime + delay;
		parameter.easing = easing;
		parameter.state = RUNNING;
	}

	void startScale(vec2 scaleStart, vec2 scaleEnd, float duration, float delay, ofxeasing::function easing) {
		this->scaleStart = scaleStart;
		this->scaleEnd = scaleEnd;
		parameter.durationTime = duration;
		parameter.startTime = currentTime + delay;
		parameter.easing = easing;
		parameter.state = RUNNING;
	}
};