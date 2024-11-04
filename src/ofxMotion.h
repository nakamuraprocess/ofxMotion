#pragma once
#include "MotionTransformBase.h"
#include "MotionColorBase.h"
#include "Bounce.h"
#include "ColorGradation.h"
#include "FadeInFadeOut.h"
#include "MoveLiner.h"
#include "MoveCurve.h"
#include "NoColor.h"
#include "NoTransform.h"
#include "RadialNoise.h"
#include "Rotate.h"

class ofxMotion  {
public:
	enum DrawMode {
		RECT = 0,
		CIRCLE = 1,
		TRIANGLE = 2,
		IMAGE = 3,
		TEXT = 4
	};

	enum AnchorMode {
		ANCOR_CENTER = 0,
		ANCOR_BOTTOM_CENTER = 1,
		ANCOR_TOP_LEFT = 2,
		ANCOR_TOP_RIGHT = 3,
		ANCOR_BOTTOM_LEFT = 4,
		ANCOR_BOTTOM_RIGHT = 5,
	};

	enum DirectionMode {
		LEFT = 0,
		RIGHT = 1,
		TOP = 2,
		BOTTOM = 3,
		TOP_LEFT = 4,
		TOP_RIGHT = 5,
		BOTTOM_LEFT = 6,
		BOTTOM_RIGHT = 7,
	};

	void setup(DrawMode drawMode, ofImage* image, vec2 pos, vec2 scale, float width, float height, float degrees, AnchorMode anchor, bool bStateDisplay = false);
	void setup(DrawMode drawMode, vec2 pos, vec2 scale, float width, float height, float degrees, ofColor color, AnchorMode anchor, bool bStateDisplay = false);
	void setup(DrawMode drawMode, ofTrueTypeFont* ttf, string _strText, vec2 pos, vec2 scale, float degrees, ofColor color, AnchorMode anchor, bool bStateDisplay = false);
	void update(const float currentTime);
	void draw();

	vec2 getPos();
	ofRectangle getRectangle();
	DirectionMode getDirectionMode();
	MotionTransformBase::MotionState getStateMotionTransform();
	MotionColorBase::MotionState getStateMotionColor();

	void setMotionTransformPtr(MotionTransformBase* ptr);
	void setMotionColorPtr(MotionColorBase* ptr);
	void setStateStateMotionTransform(MotionTransformBase::MotionState state);
	void setPosMotionTransform(vec2 pos);
	void setDirectionMode(DirectionMode mode);
	void setMirrorMode(bool vertical, bool horizon);
	void setImage(ofImage* image);
	bool inside(int x, int y);
	bool collision(int x, int y);
	void setStateInside(bool b);
	void reset();

	template <class... Args> void startMotion(string str, Args... args) {
		if (motionTransform->getName() == str) {
			motionTransform->start(args...);
		}
	}

	template <class... Args> void startColor(string str, Args... args) {
		if (motionColor->getName() == str) {
			motionColor->start(args...);
		}
	}
	

private:
	MotionTransformBase* motionTransform;
	MotionColorBase* motionColor;
	MotionTransformBase::MotionState stateTransform;
	MotionColorBase::MotionState stateColor;
	bool bStateDisplay = false;
	bool bStateInside = true;
	DrawMode drawMode;
	ofRectangle rectangle;
	AnchorMode anchor;
	DirectionMode directionMode;
	float width;
	float height;
	ofImage* image;
	ofTrueTypeFont* ttf;
	string strText;
	ofTexture textureText;

	vec2 getAnchor(float width, float height);
	void setRect(float x, float y, float width, float height);

};