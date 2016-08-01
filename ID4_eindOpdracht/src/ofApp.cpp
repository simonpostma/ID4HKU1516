#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// General Setup
	ofSetFrameRate(60);

	// Open CV Setup
	haarFinder.setup("haarcascade_frontalface_default.xml");
	grabber.listDevices();
	grabber.setDeviceID(0);
	grabber.setDesiredFrameRate(30);
	grabber.initGrabber(ofGetWidth(), ofGetHeight());

	// GUI Setup
	gui.setup("ParticleUI", "ParticleUI.xml");
	gui.add(partLife.setup("Life", 1, 1, 5));
	gui.add(partFrict.setup("Frict",1, 1, 10));
	gui.add(partSpeed.setup("Max Speed", 10, 10, 500));
	gui.add(partField.setup("Field Size", 1, 1, 100));

	// Parameter Setup
	parameters.setup(partSpeed, partLife, partField, partFrict);

	// Particles Setup
	imgTemp.loadImage("particle.png");
	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F);
	fbo.begin();
	ofBackground(ofColor::black);
	fbo.end();
	time = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
	// Grabber & OpenCV Update
	grabber.update();
	haarFinder.findHaarObjects(grabber.getPixels(), 100, 100);
	for (int i = 0; i < haarFinder.blobs.size(); i++) {
		partXY = ofPoint(haarFinder.blobs[i].centroid.x, haarFinder.blobs[i].centroid.y);
	}	

	// Parameters Update
	parameters.update(partSpeed, partLife, partField, partFrict, partXY);

	// Particles Update
	float currentTime = ofGetElapsedTimef();
	float elapsedTime = ofClamp(currentTime - time, 0, 0.1);
	time = currentTime;
	int i = 0;
	while (i < particles.size()) {
		if (!particles[i].isAlive) {
			particles.erase(particles.begin() + i);
		}
		else {
			i++;
		}
	}
	int newParticles = birthRate * elapsedTime;

	for (int i = 0; i<newParticles; i++) {
		Particle newParticle(&parameters);
		newParticle.setup(imgTemp);
		particles.push_back(newParticle);
	}
	for (int i = 0; i < particles.size(); i++) {
		particles[i].update(elapsedTime);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(ofColor::black);
	fbo.begin();
	
	// OpenCV Draw
	ofSetColor(ofColor::white);
	grabber.draw(0, 0);

	// Particles Draw
	ofEnableAlphaBlending();
	//ofSetColor(ofColor::black, FADE_TRAIL);
	//ofFill();
	//ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	//ofDisableAlphaBlending();
	//ofFill();
	
	for (int i = 0; i < particles.size(); i++) {
		ofEnableAlphaBlending();
		particles[i].draw();
		ofDisableAlphaBlending();
	}

	fbo.end();
	ofSetColor(ofColor::white);
	fbo.draw(0, 0);

	// GUI DRAW ================================================
	gui.draw();
}