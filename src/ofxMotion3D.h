#pragma once
#include "base/MotionTransform3D.h"
#include "base/MotionColor.h"

#include "color/DefaultColor.h"
#include "color/ColorGradation.h"
#include "color/FadeInFadeOut.h"

#include "3d/DefaultTransform.h"
#include "3d/MoveLiner.h"

class ofxMotion3D {
public:
	void setMotionTransformPtr(MotionTransform3D* ptr);
	void setMotionColorPtr(MotionColor* ptr);

	void setup(glm::vec3 pos, glm::vec3 scale, float width, float height);
	void update(const float currentTime);

	glm::vec3 getPos();
	MotionTransform3D::MotionState getStateMotionTransform();
	MotionColor::MotionState getStateMotionColor();
	MotionTransform3D* getMotionTransform();
	MotionColor* getMotionColor();
	
	void setStateMotionTransform(MotionTransform3D::MotionState state);
	void setPos(glm::vec3 pos);

private:
	MotionTransform3D* motionTransform = nullptr;
	MotionColor* motionColor = nullptr;
	MotionTransform3D::MotionState stateTransform;
	MotionColor::MotionState stateColor;
};