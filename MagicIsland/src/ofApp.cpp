#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
    // first thing's first we're going to load all our images.
    ofxNestedFileLoader loader;
    vector<string> imageNames = loader.load("TestImages");
    for(int i = 0; i < imageNames.size(); i++) {
        CoastlineImage* img = new CoastlineImage();
        img->load(imageNames[i]);
        
        Effect HSV;
        HSV.loadShader("Shaders/hsv");
        HSV.width = img->getWidth();
        HSV.height = img->getHeight();
        
        Effect BlurHor;
        BlurHor.loadShader("Shaders/BlurHor");
        BlurHor.addUniform("blurAmnt", &blurAmount);
        BlurHor.width = img->getWidth();
        BlurHor.height = img->getHeight();
        
        Effect BlurVert;
        BlurVert.loadShader("Shaders/BlurVert");
        BlurVert.addUniform("blurAmnt", &blurAmount);
        BlurVert.width = img->getWidth();
        BlurVert.height = img->getHeight();
        
        Effect BandW;
        BandW.loadShader("Shaders/BandW");
        BandW.width = img->getWidth();
        BandW.height = img->getHeight();
        
        Effect threshold;
        threshold.loadShader("Shaders/sandwichThreshold");
        threshold.addUniform("threshMin", &threshMin);
        threshold.addUniform("threshMax", &threshMax);
        threshold.width = img->getWidth();
        threshold.height = img->getHeight();
        
        Effect sobel;
        sobel.loadShader("Shaders/sobel");
        sobel.width = img->getWidth();
        sobel.height = img->getHeight();
        
        img->addEffect(BlurHor);
        img->addEffect(BlurVert);

        img->addEffect(HSV);
        img->addEffect(threshold);

        images.push_back(img);
    }
    
    for(int i = 0; i < images.size(); i++) {
        images[i]->reset();
    }
    
    string settingsPath = "settings/settings.xml";
    gui.setup("Gui", settingsPath);
    gui.add(threshMin.set("Threshold Min", 0.5, 0, 1.0));
    gui.add(threshMax.set("Threshold Max", 0.5, 0, 1.0));
    gui.add(blurAmount.set("Blur Amount", 1, 0, 10));
    gui.add(trimThreshold.set("Trim Threshold", 20, 0, 50));
    threshMin.addListener(this, &ofApp::onParamChanged);
    threshMax.addListener(this, &ofApp::onParamChanged);
    blurAmount.addListener(this, &ofApp::onParamChanged);
    trimThreshold.addListener(this, &ofApp::onParamChanged);

    gui.loadFromFile(settingsPath);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofScale(0.5, 0.5);
    float x, y;
    x = y = 0;
    for(int i = 0; i < images.size(); i++) {
        if(i > 0) {
            ofVec2f diff = images[i-1]->p2 - images[i]->p1;
            x += diff.x;
            y += diff.y;
        }
//        x += 100;
        float scale = 1.0;
        ofPushMatrix();
        ofTranslate(x, y);
        images[i]->draw(0, 0);
        ofPopStyle();
        ofPopMatrix();
    }
    ofPopMatrix();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::onParamChanged(float & param) {
    for(int i = 0; i < images.size(); i++) {
        images[i]->setTrimThreshold(trimThreshold);
        images[i]->reset();
        images[i]->findCoastline();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
