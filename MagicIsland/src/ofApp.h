#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxNestedFileLoader.h"
#include "ofxGui.h"
#include "Effect.hpp"
#include "CoastlineImage.hpp"
#include "CoastFrame.hpp"

using namespace cv;
using namespace ofxCv;

class ofApp : public ofBaseApp{
    
	public:
		void setup();
		void update();
		void draw();
        void onParamChanged(float & param);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        vector<CoastlineImage *> images;
        vector<CoastFrame *> coastFrames;
    
        ofxPanel gui;
        ofParameter<float> threshMin, threshMax, blurAmount, trimThreshold;
    
        ofxCv::ContourFinder contourFinder;
};
