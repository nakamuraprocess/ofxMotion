#pragma once
#include "MotionTransform2D.h"

namespace OFX_MOTION_2D {
	class Rotate : public MotionTransform2D {
	public:
		void update(const float currentTime) {
			this->currentTime = currentTime;
			if (parameter.state == RUNNING) {
				float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
					parameter.state = DONE;
					});

				degrees = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, degreesStart, degreesEnd, parameter.easing);
			}
		}

		void startRotate(float distance, float anchorPosForRotation, float duration, ofxeasing::function easing) {
			degreesStart = degrees;
			this->anchorPosForRotation = anchorPosForRotation;
			degreesEnd = degrees + distance;
			parameter.durationTime = duration;
			parameter.startTime = currentTime;
			parameter.easing = easing;
			bRotate = true;
			parameter.state = RUNNING;
		}

		void startRotate(float degreesStart, float degreesEnd, float anchorPosForRotation, float duration, ofxeasing::function easing) {
			this->degreesStart = degreesStart;
			this->degreesEnd = degreesEnd;
			this->anchorPosForRotation = anchorPosForRotation;
			parameter.durationTime = duration;
			parameter.startTime = currentTime;
			parameter.easing = easing;
			bRotate = true;
			parameter.state = RUNNING;
		}
	};
}