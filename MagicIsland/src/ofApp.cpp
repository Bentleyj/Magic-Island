#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
    // first thing's first we're going to load all our images.
    ofxNestedFileLoader loader;
    vector<string> imageNames = loader.load("TestImages");
    for(int i = 0; i < imageNames.size(); i++) {
        ProcessedImage* img = new ProcessedImage();
        img->load(imageNames[i]);
        
        Effect negative;
        negative.loadShader("Shaders/negative");
        negative.width = img->getWidth();
        negative.height = img->getHeight();
        
        Effect darken;
        darken.loadShader("Shaders/darken");
        darken.width = img->getWidth();
        darken.height = img->getHeight();
        
        img->addEffect(negative);

        img->addEffect(darken);
        
        images.push_back(img);
    }
    
    string settingsPath = "settings/settings.xml";
    gui.setup("Gui", settingsPath);
    gui.add(cannyThreshMin.set("Canny Thesh Min", 0, 0, 255));
    gui.add(cannyThreshMax.set("Canny Thesh Max", 255, 0, 255));
    gui.loadFromFile(settingsPath);
    
    for(int i = 0; i < images.size(); i++) {
        images[i]->applyEffects();
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    int x = 0;
    for(int i = 0; i < images.size(); i++) {
        float scale = 1.0;
        if(images[i]->getHeight()*3 > ofGetHeight()) {
            scale = ofGetHeight() / (images[i]->getHeight()*3);
        }
        ofPushMatrix();
        ofTranslate(x, 0);
        ofScale(scale, scale);
        images[i]->draw(0, 0);
        ofPopMatrix();
        x += images[i]->getWidth() * scale;
    }
    
    gui.draw();
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
