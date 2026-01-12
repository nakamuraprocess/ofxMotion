#pragma once
#include "MotionTransform2D.h"
#include "MoveLiner.h"
#include "Rotate.h"
#include "Scale.h"

namespace OFX_MOTION_2D {
	class MoveLinerRotateScale : public MotionTransform2D {
	public:
		void update(const float currentTime) {
			if (!bDoneSetup) {
				moveLiner.setup(pos, posInitial, scale, width, height, widthInitial, heightInitial, degrees);
				rotateTo.setup(pos, posInitial, scale, width, height, widthInitial, heightInitial, degrees);
				scaleTo.setup(pos, posInitial, scale, width, height, widthInitial, heightInitial, degrees);
				bDoneSetup = true;
			}
			
			moveLiner.update(currentTime);
			rotateTo.update(currentTime);
			scaleTo.update(currentTime);

			if (parameter.state == RUNNING) {
				pos = moveLiner.getPos();
				degrees = rotateTo.getDegrees();
				width = widthInitial * scaleTo.getScale().x;
				height = heightInitial * scaleTo.getScale().y;

				if (moveLiner.getState() == DONE && rotateTo.getState() == DONE && scaleTo.getState() == DONE) {
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

		void startScale(glm::vec2 scaleEnd, float duration, float delay, ofxeasing::function easing) {
			parameter.state = RUNNING;
			scaleTo.startScale(scaleEnd, duration, delay, easing);
		}

	private:
		OFX_MOTION_2D::MoveLiner moveLiner;
		OFX_MOTION_2D::Rotate rotateTo;
		OFX_MOTION_2D::Scale scaleTo;
		bool bDoneSetup = false;
	};
}