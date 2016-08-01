#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Parameters.h"
#include "Particle.h"

#define MAX_PARTICLES 150
#define FADE_TRAIL 10

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

		Parameters parameters;
};
