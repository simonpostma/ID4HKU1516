#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Parameters.h"
#include "Particle.h"
#include "ofxCvHaarFinder.h"

#define MAX_PARTICLES 20
#define FADE_TRAIL 50

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		// GUI stuff
		ofxPanel gui;
		ofxIntSlider partLife;
		ofxIntSlider partFrict;
		ofxIntSlider partSpeed;
		ofxIntSlider partField;

		// Particles stuff
		vector<Particle> particles;
		float time;
		float birthRate = 100;

		ofFbo fbo;
		ofImage imgTemp;

		ofPoint partXY;

		Parameters parameters;

		//Open CV stuff
		ofVideoGrabber grabber;
		ofxCvHaarFinder haarFinder;
};
