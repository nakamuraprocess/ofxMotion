#pragma once
#include "MotionTransformBase.h"

class RadialNoise : public MotionTransformBase {
private:
	float timeRecently;
	float radius;
	float velocity;
	vec2 posOffset;
	vec2 posNoiseCursor;

public:
	void update(const float currentTime) {
		if (parameter.state == RUNNING) {
			float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
				parameter.state = DONE;
				});

			float timeDestination = currentTime - timeRecently;
			timeDestination = ofClamp(timeDestination, 0.0, 0.1);
			timeRecently = currentTime;

			posNoiseCursor += velocity * timeDestination;
			pos.x = ofSignedNoise(posNoiseCursor.x) * radius + posOffset.x;
			pos.y = ofSignedNoise(posNoiseCursor.y) * radius + posOffset.y;
		}
	}

	void startRadialNoise(float radius, float velociry, vec2 posOffset, float duration) {
		posNoiseCursor = pos;
		this->radius = radius;
		velocity = velociry;
		this->posOffset = posOffset;
		parameter.startTime = ofGetElapsedTimef();
		parameter.durationTime = duration;
		parameter.state = RUNNING;
	}
};