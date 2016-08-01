#include "Particle.h"

Particle::Particle(Parameters* parameters) {
	isAlive = false;
	param = parameters;
}

void Particle::setup(ofImage img) {
	position = param->startingPoint + randomPointOnCircle(param->radius);
	speed = randomPointOnCircle(param->maxSpeed);
	age = 0;
	maxAge = param->lifeTime;
	isAlive = true;
	imgPart = img;
}

void Particle::update(float elapsedTime) {
	if (!isAlive) return;
	speed.rotate(0, 0, param->rotate * elapsedTime);
	ofVec3f distance = position - param->startingPoint;
	
	if (ofInRange(distance.length(), 0, param->radius)) {
		distance.normalize();
		ofVec3f acceleration;
		acceleration += distance * param->force;
		acceleration.x = -distance.y * param->spinning;
		acceleration.y = distance.x * param->spinning;
		speed += acceleration * elapsedTime;
	}

	speed *= (1 - param->friction);
	position += speed * elapsedTime;
	age += elapsedTime;
	if (age >= maxAge) isAlive = false;
}

void Particle::draw() {
	ofColor color = ofColor::red;
	float hue = ofMap(age, 0, maxAge, 64, 127);
	color.setHue(hue);
	ofSetColor(color);
	float size = ofMap(maxAge - age, 0, maxAge, 3, 1);
	imgPart.draw(position, (size * 15), (size * 15));
}

ofPoint Particle::randomPointOnCircle(float maxRadius) {
	ofPoint point;
	float radius = ofRandom(0, maxRadius);
	float angle = ofRandom(0, M_TWO_PI);
	point.x = cos(angle) * radius;
	point.y = sin(angle) * radius;
	return point;
}
