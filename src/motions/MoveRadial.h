#pragma once
#include "MotionTransformBase.h"

class MoveRadial : public MotionTransformBase {
private:
	float radian;
	vec2 radius;
	vec2 radiusStart;
	vec2 radiusEnd;

public:
	void update(const float currentTime) {
		if (parameter.state == RUNNING) {
			float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
				parameter.state = DONE;
				});

			radius.x = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, radiusStart.x, radiusEnd.x, parameter.easing);
			radius.y = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, radiusStart.y, radiusEnd.y, parameter.easing);

			pos.x = cos(radian) * radius.x + posInitial.x;
			pos.y = sin(radian) * radius.y + posInitial.y;
		}
	}

	void startMoveRadial(float radian, vec2 radiusEnd, float duration, float delay, ofxeasing::function easing) {
		this->radian = radian;
		this->radiusStart = this->radius;
		this->radiusEnd =  radiusEnd;
		parameter.startTime = ofGetElapsedTimef() + delay;
		parameter.durationTime = duration;
		parameter.easing = easing;
		parameter.state = RUNNING;;
	}

	void startMoveRadial(float radian, vec2 radiusStart, vec2 radiusEnd, float duration, float delay, ofxeasing::function easing) {
		this->radian = radian;
		this->radiusStart = radiusStart;
		this->radiusEnd = radiusEnd;
		parameter.startTime = ofGetElapsedTimef() + delay;
		parameter.durationTime = duration;
		parameter.easing = easing;
		parameter.state = RUNNING;;
	}
};