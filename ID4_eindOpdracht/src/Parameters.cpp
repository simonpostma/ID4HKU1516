#include "Parameters.h"

Parameters::Parameters() {
	
}

void Parameters::setup(float partSpeed, float partLife, float partField, float partFrict)
{
	startingPoint = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
	radius = partField;
	maxSpeed = partSpeed;
	lifeTime = partLife;
	rotate = 90;

	force = 1000;
	spinning = 1000;
	friction = partFrict / 100;
}

void Parameters::update(float partSpeed, float partLife, float partField, float partFrict, ofPoint partXY)
{
	radius = partField;
	maxSpeed = partSpeed;
	lifeTime = partLife ;
	friction = partFrict / 100;
	startingPoint = partXY;
}
