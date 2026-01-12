#pragma once
#include "MotionTransform2D.h"

namespace OFX_MOTION_2D {
	class MoveRadial : public MotionTransform2D {
	private:
		float radian;
		glm::vec2 radius;
		glm::vec2 radiusStart;
		glm::vec2 radiusEnd;

	public:
		void update(const float currentTime) {
			this->currentTime = currentTime;
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

		void startMoveRadial(float radian, glm::vec2 radiusEnd, float duration, float delay, ofxeasing::function easing) {
			this->radian = radian;
			this->radiusStart = this->radius;
			this->radiusEnd = radiusEnd;
			parameter.startTime = currentTime + delay;
			parameter.durationTime = duration;
			parameter.easing = easing;
			parameter.state = RUNNING;;
		}

		void startMoveRadial(float radian, glm::vec2 radiusStart, glm::vec2 radiusEnd, float duration, float delay, ofxeasing::function easing) {
			this->radian = radian;
			this->radiusStart = radiusStart;
			this->radiusEnd = radiusEnd;
			parameter.startTime = currentTime + delay;
			parameter.durationTime = duration;
			parameter.easing = easing;
			parameter.state = RUNNING;;
		}
	};
}