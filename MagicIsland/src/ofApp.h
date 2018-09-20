#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxNestedFileLoader.h"
#include "ofxGui.h"

using namespace cv;
using namespace ofxCv;

class ofApp : public ofBaseApp{
    
	public:
    
        class ProcessedImage : public ofImage {
            public:
                ofImage processed;
                Mat mat;
            
                void update() {
                    ofImage::update();
                    processed.update();
                }
            
                void load(string imgPath) {
                    ofImage::load(imgPath);
                    processed.allocate(getWidth(), getHeight(), OF_IMAGE_GRAYSCALE);
                    mat = toCv(processed);
                    convertColor(getPixels(), processed, CV_RGB2GRAY);
                    processed.update();
                }
            
                void draw(float x, float y) {
                    ofImage::draw(x, y);
                    processed.draw(x, y+getHeight());
                    drawMat(mat, x, y+getHeight()*2);
                }
        };
    
		void setup();
		void update();
		void draw();

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
    
        vector<ProcessedImage> images;
    
        ofxPanel gui;
        ofParameter<float> cannyThreshMin;
        ofParameter<float> cannyThreshMax;
    
        ofxCv::ContourFinder contourFinder;
};
