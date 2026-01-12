#pragma once
#include "MotionTransform2D.h"
#include "MoveLiner.h"
#include "Rotate.h"

namespace OFX_MOTION_2D {
	class MoveLinerRotate : public MotionTransform2D {
	public:
		void update(const float currentTime) {
			if (!bDoneSetup) {
				moveLiner.setup(pos, posInitial, scale, width, height, widthInitial, heightInitial, degrees);
				rotateTo.setup(pos, posInitial, scale, width, height, widthInitial, heightInitial, degrees);
				bDoneSetup = true;
			}

			moveLiner.update(currentTime);
			rotateTo.update(currentTime);

			if (parameter.state == RUNNING) {
				pos = moveLiner.getPos();
				degrees = rotateTo.getDegrees();

				if (moveLiner.getState() == DONE && rotateTo.getState() == DONE) {
					parameter.state = DONE;
				}
			}
		}

		void startMoveLiner(glm::vec2 distance, float duration, float delay, ofxeasing::function easing) {
			parameter.state = RUNNING;
			moveLiner.startMoveLiner(distance, duration, delay, easing);
		}

		void startRotate(float distance, float anchorPosForRotation, float duration, ofxeasing::function easing) {
			parameter.state = RUNNING;
			rotateTo.startRotate(distance, anchorPosForRotation, duration, easing);
		}

	private:
		OFX_MOTION_2D::MoveLiner moveLiner;
		OFX_MOTION_2D::Rotate rotateTo;
		bool bDoneSetup = false;
	};
}