#pragma once
#include "MotionTransformBase.h"
#include "MotionColorBase.h"
#include "Bounce.h"
#include "ColorGradation.h"
#include "FadeInFadeOut.h"
#include "MoveCircle.h"
#include "MoveLiner.h"
#include "MoveCurve.h"
#include "MoveRadial.h"
#include "MoveLinerRotate.h"
#include "MoveLinerRotateScale.h"
#include "DefaultColor.h"
#include "DefaultTransform.h"
#include "SignWaveNoise.h"
#include "Rotate.h"
#include "Scale.h"

static class ofxMotionBackground {
public:
	static void grid(float width, float height, float margin) {
		ofPushStyle();
		ofSetLineWidth(2);
		ofSetColor(150);
		for (int i = 1; i < (1000 / margin); i++) {
			ofLine(0, (height * 0.5) - i * margin, width, (height * 0.5) - i * margin);
			ofLine(0, (height * 0.5) + i * margin, width, (height * 0.5) + i * margin);
			ofLine((width * 0.5) + i * margin, 0, (width * 0.5) + i * margin, height);
			ofLine((width * 0.5) - i * margin, 0, (width * 0.5) - i * margin, height);
		}
		ofSetColor(0);
		ofLine(width * 0.5, 0, width * 0.5, height);
		ofLine(0, height * 0.5, width, height * 0.5);
		ofPopStyle();
	}

	static void greyGradient() {
		ofBackgroundGradient(ofColor(54, 54, 54), ofColor(198, 198, 198), OF_GRADIENT_LINEAR);
	}

	static void blueGradient() {
		ofBackgroundGradient(ofColor(0, 0, 54), ofColor(0, 0, 198), OF_GRADIENT_LINEAR);
	}

}ofxMotionBackground;



class ofxMotion {
public:
	enum DrawMode {
		RECT = 0,
		CIRCLE = 1,
		TRIANGLE = 2,
		IMAGE = 3,
		TEXTURE = 4,
		TEXT = 5,
		FBO = 6,
		NONE = 7
	};

	enum AnchorMode {
		ANCHOR_CENTER = 0,
		ANCHOR_BOTTOM_CENTER = 1,
		ANCHOR_TOP_LEFT = 2,
		ANCHOR_TOP_RIGHT = 3,
		ANCHOR_BOTTOM_LEFT = 4,
		ANCHOR_BOTTOM_RIGHT = 5,
	};

	enum PointLocation {
		POINT_TOP_LEFT = 0,
		POINT_TOP_RIGHT = 1,
		POINT_BOTTOM_RIGHT = 2,
		POINT_BOTTOM_LEFT = 3,
		POINT_MAX_SIZE = 4
	};

	void setMotionTransformPtr(MotionTransformBase* ptr);
	void setMotionColorPtr(MotionColorBase* ptr);

	void setup(DrawMode drawMode, vec2 pos, vec2 scale, float width, float height, float degrees, ofColor color, AnchorMode anchor, int pointsInterpolatedMaxSize = 0, bool bStateDisplay = false);
	void setup(DrawMode drawMode, ofImage* image, vec2 pos, vec2 scale, float width, float height, float degrees, AnchorMode anchor, int pointsInterpolatedMaxSize = 0, bool bStateDisplay = false);
	void setup(DrawMode drawMode, ofTexture* texture, vec2 pos, vec2 scale, float width, float height, float degrees, AnchorMode anchor, int pointsInterpolatedMaxSize = 0, bool bStateDisplay = false);
	void setup(DrawMode drawMode, ofTrueTypeFont* ttf, string strText, vec2 pos, vec2 scale, float degrees, ofColor color, AnchorMode anchor, int pointsInterpolatedMaxSize = 0, bool bStateDisplay = false);
	void setup(vec2 pos, vec2 scale, float width, float height);
	void update(const float currentTime);
	void draw();

	vec2 getPos();
	vec2 getPoint(PointLocation point);
	MotionTransformBase::MotionState getStateMotionTransform();
	MotionColorBase::MotionState getStateMotionColor();
	MotionTransformBase* getMotionTransform();
	MotionColorBase* getMotionColor();
	string getText();
	vector <vec2> getPointsInterpolated();
	
	void setStateMotionTransform(MotionTransformBase::MotionState state);
	void setPos(vec2 pos);
	void setMirrorMode(bool vertical, bool horizon);
	void setAnchorMode(AnchorMode anchor);
	void setImage(ofImage* image);
	void setDrawSubsection(float sx, float sy, float sw, float sh);
	bool insideRect(int x, int y);
	bool insideCircle(int x, int y);
	bool collision(vec2 pos);
	void setStateInside(bool b);
	void setStateDisplay(bool b);
	void setText(string text);
	void setPointsInterpolatedSize(int size);

private:
	MotionTransformBase* motionTransform = nullptr;
	MotionColorBase* motionColor = nullptr;
	bool bStateDisplay = false;
	bool bStateInside = true;
	DrawMode drawMode;
	vec2 pointsRotated[POINT_MAX_SIZE];
	vector <vec2> pointsInterpolated;
	ofPolyline polyline;
	AnchorMode anchor;
	ofImage* image = nullptr;
	ofTexture* texture = nullptr;
	ofTrueTypeFont* ttf = nullptr;
	string strText = "";
	ofFbo* fbo = nullptr;
	vec2 getAnchorPos(float width, float height) const;
	void updateInterpolatedPoints();

	struct DrawSubsection {
		bool bState;
		float x;
		float y;
		float width;
		float height;
	}drawSubsection;

};