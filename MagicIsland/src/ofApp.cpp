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
        img->addEffect(sobel);

        images.push_back(img);
    }
    
    string settingsPath = "settings/settings.xml";
    gui.setup("Gui", settingsPath);
    gui.add(threshMin.set("Threshold Min", 0.5, 0, 1.0));
    gui.add(threshMax.set("Threshold Max", 0.5, 0, 1.0));
    gui.add(blurAmount.set("Blur Amount", 1, 0, 10));
    threshMin.addListener(this, &ofApp::onParamChanged);
    threshMax.addListener(this, &ofApp::onParamChanged);
    blurAmount.addListener(this, &ofApp::onParamChanged);

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
void ofApp::onParamChanged(float & param) {
    for(int i = 0; i < images.size(); i++) {
        images[i]->reset();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    for(int i = 0; i < images.size(); i++) {
        images[i]->reset();
    }
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
