#pragma once

#include "ofMain.h"

class Parameters {
	public:
		Parameters();

		void setup(float partSpeed, float partLife, float partField, float partFrict);
		void update(float partSpeed, float partLife, float partField, float partFrict, ofPoint partXY);

		ofPoint startingPoint;
		float radius;
		float maxSpeed;
		float lifeTime;
		float rotate;

		float force;
		float spinning;
		float friction;
};
